#include <stdint.h>
#include "pci.h"
#include "ports.h"
#include "../kernel/print.h"
#include "../kernel/mem.h"
#include "../kernel/util.h"


// Function to read a 32-bit value from a PCI configuration register
// uint32_t pci_read_config(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
//     uint32_t address;

//     // Construct the configuration address
//     address = (0x80000000) |          // Set bit 31 to 1 to indicate configuration access
//               (bus << 16) |          // Bus number (8 bits)
//               (slot << 11) |        // Slot number (5 bits)
//               (function << 8) |     // Function number (3 bits)
//               (offset & 0xFC);      // Register offset (select 8-bit aligned registers)

//     // Write the address to the PCI configuration address port (0xCF8)
//     port_byte_out(PCI_CONFIG_ADDRESS, address & 0xFF);
//     port_byte_out(PCI_CONFIG_ADDRESS, (address >> 8) & 0xFF);
//     port_byte_out(PCI_CONFIG_ADDRESS, (address >> 16) & 0xFF);
//     port_byte_out(PCI_CONFIG_ADDRESS, (address >> 24) & 0xFF);

//     // Read the 32-bit data from the PCI configuration data port (0xCFC)
//     uint32_t data = 0;
//     data |= (uint32_t)port_byte_in(PCI_CONFIG_DATA) << 0;
//     data |= (uint32_t)port_byte_in(PCI_CONFIG_DATA) << 8;
//     data |= (uint32_t)port_byte_in(PCI_CONFIG_DATA) << 16;
//     data |= (uint32_t)port_byte_in(PCI_CONFIG_DATA) << 24;

//     return data;
// }

#define VIRTIO_VENDOR_ID  0x1AF4
#define VIRTIO_NET_DEVICE_ID  0x1000  // Virtio Network Device ID
#define VIRTIO_BLOCK_DEVICE_ID  0x1001  // Virtio Block Device ID

#define PCI_ADDRESS(bus, slot, function, offset)  \
    (0x80000000 | ((bus) << 16) | ((slot) << 11) | ((function) << 8) | ((offset) & 0xFC))


uint32_t pci_read_config(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
    uint32_t address = PCI_ADDRESS(bus, slot, function, offset);

    // Write the address to the PCI Configuration Address port
    port_byte_out(PCI_CONFIG_ADDRESS, address);

    // Read the data from the PCI Configuration Data port
    return port_byte_in(PCI_CONFIG_DATA);
}

// Function to check if the device is a Virtio device
bool is_virtio_device(uint8_t bus, uint8_t slot, uint8_t function) {
    uint32_t vendor_id = pci_read_config(bus, slot, function, 0);  // Vendor ID is at offset 0
    uint32_t device_id = pci_read_config(bus, slot, function, 2);  // Device ID is at offset 2

    // Check if the vendor ID is Virtio (0x1AF4) and device ID is either Virtio Network or Block device
    if ((vendor_id & 0xFFFF) == VIRTIO_VENDOR_ID) {
            printf("Found Virtio Device at bus %d, slot %d, function %d\n", bus, slot, function);
        if ((device_id & 0xFFFF) == VIRTIO_NET_DEVICE_ID) {
            printf("Found Virtio Network Device at bus %d, slot %d, function %d\n", bus, slot, function);
            return true;
        }
        else if ((device_id & 0xFFFF) == VIRTIO_BLOCK_DEVICE_ID) {
            printf("Found Virtio Block Device at bus %d, slot %d, function %d\n", bus, slot, function);
            return true;
        }
    }

    return false;  // Not a Virtio device
}

bool pci_device_present(uint8_t bus, uint8_t slot, uint8_t function) {
    uint32_t vendor_id = pci_read_config(bus, slot, function, 0);  // Vendor ID is at offset 0
    return vendor_id != 0xFFFFFFFF;  // 0xFFFFFFFF means no device
}

uint32_t *pci_map_bar(uint8_t bus, uint8_t slot, uint8_t bar_index, uint32_t size_of_mmio_region) {
    uint32_t bar_address = pci_read_config(bus, slot, 0, 0x10 + (bar_index * 4));

    if (bar_address & 0x1) {
        printf("BAR%d: I/O-mapped at 0x%x\n", bar_index, bar_address);
        return (uint32_t *)bar_address;
    } else {
        bar_address &= ~0xF;

        uint32_t *mapped_address = (uint32_t *)malloc(size_of_mmio_region);

        if (mapped_address == NULL) {
            return NULL;
        }

        return mapped_address;
    }
}

// Function to send the EOI (End of Interrupt) signal to the PIC
void pic_acknowledge_irq(uint8_t irq) {
    if (irq >= 8) {
        // The interrupt was from the slave PIC (IRQ 8 to 15)
        port_byte_out(PIC_SLAVE_CMD, PIC_EOI);  // Acknowledge the slave PIC
    }

    // Acknowledge the master PIC in all cases
    port_byte_out(PIC_MASTER_CMD, PIC_EOI);  // Acknowledge the master PIC
}

void check_virtio_device(uint8_t bus, uint8_t slot, uint8_t function) {
    uint32_t vendor_id = pci_read_config(bus, slot, function, 0);
    uint32_t device_id = pci_read_config(bus, slot, function, 2);
    uint32_t class_code = pci_read_config(bus, slot, function, 0x08);

    uint8_t base_class = (class_code >> 24) & 0xFF;
    uint8_t sub_class  = (class_code >> 16) & 0xFF;
    uint8_t prog_intf  = (class_code >> 8) & 0xFF;

    // Print the device details
    printf("PCI Device found at bus %d, slot %d, function %d\n", bus, slot, function);
    printf("Vendor ID: 0x%04x, Device ID: 0x%04x\n", vendor_id & 0xFFFF, device_id & 0xFFFF);
    printf("Class Code: 0x%06x\n", class_code);
    printf("Base Class: 0x%02x, Sub Class: 0x%02x, Programming Interface: 0x%02x\n", base_class, sub_class, prog_intf);

    // Check for Virtio Vendor ID (0x1AF4)
    if ((vendor_id & 0xFFFF) == 0x1AF4) {
        printf("Virtio device found!\n");
    } else {
        printf("Not a Virtio device.\n");
    }
}

// Function to find and print all PCI devices (scans all bus, slots, and functions)
void pci_scan() {
    for (uint8_t bus = 0; bus < 256; bus++) {
        for (uint8_t slot = 0; slot < 32; slot++) {
            for (uint8_t function = 0; function < 8; function++) {
                if (pci_device_present(bus, slot, function)) {
                    uint32_t vendor_id = pci_read_config(bus, slot, function, 0);
                    uint32_t device_id = pci_read_config(bus, slot, function, 2);
                    printf("PCI Device found at bus %d, slot %d, function %d\n", bus, slot, function);
                    printf("Vendor ID: 0x%04x, Device ID: 0x%04x\n", vendor_id & 0xFFFF, device_id & 0xFFFF);
                }
                if (bus == 255 && slot == 31 && function == 7) {
                    return;
                }
            }
        }
    }
}
