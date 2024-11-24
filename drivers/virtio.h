#include <stdint.h>

#define VIRTIO_NET_PCI_DEVICE_ID 0x1000
#define VIRTIO_NET_DEVICE_FEATURES_OFFSET 0x00
#define VIRTIO_NET_STATUS_OFFSET 0x12
#define VIRTIO_NET_MAC_ADDR_OFFSET 0x14
#define VIRTIO_NET_QUEUE_SIZE_OFFSET 0x18
#define VIRTIO_NET_QUEUE_NOTIFY_OFFSET 0x20

typedef struct {
    volatile uint32_t *status;  // Device status register
    volatile uint32_t *features;  // Feature set supported by the device
    volatile uint32_t *queue_notify;  // Notify register for queues
    volatile uint32_t *queue_size;  // Queue size register
    volatile uint8_t *mac_addr;  // MAC address register
} virtio_net_device_t;

// Function to initialize the Virtio-net device
void virtio_initialize_device(uint8_t bus, uint8_t slot, virtio_net_device_t *dev);
void virtio_read_mac(virtio_net_device_t *dev, uint8_t *mac);
