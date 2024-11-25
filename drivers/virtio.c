#include <stddef.h>
#include "virtio.h"
#include "pci.h"
#include "../kernel/print.h"

// Assuming we already have PCI memory-mapped I/O functions like pci_map_bar()
int virtio_initialize_device(uint8_t bus, uint8_t slot, uint8_t function, uint8_t device_id, virtio_net_device_t *dev) {
    // Try to find the Virtio device's BAR (usually BAR 0 for MMIO)
    uint32_t *bar = pci_map_bar(bus, slot, function, 1, device_id); // Map 4KB or more as needed (check your MMIO region size)

    if (bar == NULL) {
        printf("Error: Failed to map BAR0 for Virtio device.\n");
        return -1;  // Return an error if BAR mapping fails
    }

    // Initialize the Virtio-net device structure
    dev = (virtio_net_device_t *)bar;

    // Set up the MMIO mappings for the Virtio registers
    // dev->features = (volatile uint32_t *)(bar + VIRTIO_NET_FEATURES_OFFSET);  // Assume the features register starts at 0x00
    // dev->status = (volatile uint32_t *)(bar + VIRTIO_NET_STATUS_OFFSET);    // Assume the status register is at 0x04
    // dev->mac_addr = (volatile uint8_t *)(bar + VIRTIO_NET_MAC_ADDR_OFFSET); // MAC address at a specific offset
    // dev->queue_size = (volatile uint32_t *)(bar + VIRTIO_NET_QUEUE_SIZE_OFFSET); // Queue size (replace with the correct offset)
    // dev->queue_notify = (volatile uint32_t *)(bar + VIRTIO_NET_QUEUE_NOTIFY_OFFSET); // Queue notify (replace with the correct offset)

    // Check if the device is ready by reading the status register
    uint32_t status = *dev->status;
    if (status == 0) {
        printf("Virtio device is not ready.\n");
        return -1;
    }

    // Optional: You can read and print the features register to check the device's capabilities
    uint32_t features = *dev->features;
    printf("Virtio Device Features: 0x%08x\n", features);

    // Enable the device (assuming the status register requires a write to enable the device)
    // Typically, you write a value like 1 to the status register to activate the device
    *dev->status = 1; // Set the status to indicate the device is now enabled

    // Optionally, print the MAC address to verify
    uint8_t mac[6];
    for (int i = 0; i < 6; i++) {
        mac[i] = dev->mac_addr[i];
    }
    printf("Virtio Device MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return 0; // Success
}

void virtio_read_mac(virtio_net_device_t *dev, uint8_t *mac) {
    for (int i = 0; i < 6; i++) {
        mac[i] = dev->mac_addr[i];
    }
}
