#include <stdint.h>
#include "pci.h"
#include "ports.h"
#include "../kernel/print.h"
#include "../kernel/mem.h"
#include "../kernel/util.h"


#define VIRTIO_VENDOR_ID  0x1AF4
#define VIRTIO_NET_DEVICE_ID  0x1000  // Virtio Network Device ID
#define VIRTIO_BLOCK_DEVICE_ID  0x1001  // Virtio Block Device ID

#define PCI_ADDRESS(bus, slot, function, offset)  \
    (0x80000000 | ((bus) << 16) | ((slot) << 11) | ((function) << 8) | ((offset) & 0xFC))


uint32_t pci_read_config(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
    uint32_t address = PCI_ADDRESS(bus, slot, function, offset);

    // Write the address to the PCI Configuration Address port
    outb(PCI_CONFIG_ADDRESS, address);

    // Read the data from the PCI Configuration Data port
    return inb(PCI_CONFIG_DATA);
}

bool pci_device_present(uint8_t bus, uint8_t slot, uint8_t function) {
    uint32_t vendor_id = pci_read_config(bus, slot, function, 0);  // Vendor ID is at offset 0
    return vendor_id != 0xFFFFFFFF;  // 0xFFFFFFFF means no device
}

uint32_t* pci_map_bar(uint8_t bus, uint8_t slot, uint8_t function, uint8_t bar_index, uint32_t size_of_mmio_region) {
    // BAR0 is at offset 0x10, BAR1 is at 0x14, etc.
    uint32_t bar_address = pci_read_config(bus, slot, function, 0x10 + (bar_index * 4));

    // Check if the BAR is an I/O port or memory-mapped
    if (bar_address & 0x1) {
        // If the least significant bit is 1, it's an I/O-mapped BAR
        printf("BAR%d: I/O-mapped at 0x%x\n", bar_index, bar_address);
        return (uint32_t *)bar_address;  // Return the I/O address as a pointer
    } else {
        // If the least significant bit is 0, it's memory-mapped
        bar_address &= ~0xF;  // Clear the lower 4 bits (to align the address)

        // Allocate memory for the MMIO region
        uint32_t *mapped_address = (uint32_t *)malloc(size_of_mmio_region);
        if (mapped_address == NULL) {
            printf("Error: Failed to allocate memory for MMIO region.\n");
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
    uint32_t id = pci_read_config(bus, slot, function, 0);
    uint32_t vendor_id = id & 0xffff;
    uint32_t device_id = (id>>16) & 0xffff;

    // printf("Vendor ID: 0x%04x, Device ID: 0x%04x\n", vendor_id, device_id);
    // Check for Virtio Vendor ID (0x1AF4)
    if (vendor_id == VIRTIO_VENDOR_ID) {
        // Print the device details
        printf("PCI Device found at bus %d, slot %d, function %d\n", bus, slot, function);
        printf("Vendor ID: 0x%04x, Device ID: 0x%04x\n", vendor_id, device_id);
        printf("Virtio device found!\n");
    }
}

// Function to find and print all PCI devices (scans all bus, slots, and functions)
void pci_scan() {
    for (uint8_t bus = 0; bus < 256; bus++) {
        for (uint8_t slot = 0; slot < 32; slot++) {
            for (uint8_t function = 0; function < 8; function++) {
                check_virtio_device(bus, slot, function);
                if (bus == 255 && slot == 31 && function == 7) {
                    return;
                }
            }
        }
    }
}
