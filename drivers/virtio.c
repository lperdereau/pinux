#include <stddef.h>
#include "virtio.h"
#include "pci.h"
#include "../kernel/print.h"

// Assuming we already have PCI memory-mapped I/O functions like pci_map_bar()
void virtio_initialize_device(uint8_t bus, uint8_t slot, virtio_net_device_t *dev) {
    uint32_t *bar1 = pci_map_bar(bus, slot, 1, VIRTIO_NET_PCI_DEVICE_ID);  // Map the MMIO region (BAR 1)

    if (bar1 == NULL) {
        printf("Error: Failed to map BAR 1\n");
        return;  // Handle error gracefully
    }

    // Initialize the Virtio-net device structure
    dev = (virtio_net_device_t *) bar1;

    // Initialize the Virtio-net device structure
    dev->features = (volatile uint32_t *) (bar1 + VIRTIO_NET_DEVICE_FEATURES_OFFSET);
    dev->status = (volatile uint32_t *) (bar1 + VIRTIO_NET_STATUS_OFFSET);
    dev->mac_addr = (volatile uint8_t *) (bar1 + VIRTIO_NET_MAC_ADDR_OFFSET);
    dev->queue_size = (volatile uint32_t *) (bar1 + VIRTIO_NET_QUEUE_SIZE_OFFSET);
    dev->queue_notify = (volatile uint32_t *) (bar1 + VIRTIO_NET_QUEUE_NOTIFY_OFFSET);

    // Read the MAC address from the device
    uint8_t mac[6];
    virtio_read_mac(dev, mac);

    // Print the MAC address
    printf("Virtio-net MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // Print the other device info
    printf("features: %u\n", *dev->features);
    printf("status: %u\n", *dev->status);
    printf("queue_size: %u\n", *dev->queue_size);
    printf("queue_notify: %u\n", *dev->queue_notify);

    // Enable the device by writing to the status register (e.g., 1 to activate)
    *dev->status = 1;
}

void virtio_read_mac(virtio_net_device_t *dev, uint8_t *mac) {
    for (int i = 0; i < 6; i++) {
        mac[i] = dev->mac_addr[i];
    }
}
