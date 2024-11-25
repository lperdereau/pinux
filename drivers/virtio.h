#include <stdint.h>

#define VIRTIO_NET_PCI_DEVICE_ID            0x1000        // Device ID of the Virtio network device (Vendor-specific)
#define VIRTIO_NET_FEATURES_OFFSET          0x00          // Offset where features (supported capabilities) are stored
#define VIRTIO_NET_STATUS_OFFSET            0x04          // Offset where status of the device is stored
#define VIRTIO_NET_MAC_ADDR_OFFSET          0x08          // Offset where the MAC address is stored (6 bytes)
#define VIRTIO_NET_QUEUE_SIZE_OFFSET        0x10          // Offset for queue size (number of entries in RX/TX queues)
#define VIRTIO_NET_QUEUE_NOTIFY_OFFSET      0x14          // Offset where we notify the device about new queue entries

typedef struct __attribute__((packed)) {
    volatile uint32_t *status;
    volatile uint32_t *features;
    volatile uint32_t *queue_notify;
    volatile uint32_t *queue_size;
    volatile uint8_t *mac_addr;
} virtio_net_device_t;

// Function to initialize the Virtio-net device
int virtio_initialize_device(uint8_t bus, uint8_t slot, uint8_t function, uint8_t device_id, virtio_net_device_t *dev);
void virtio_read_mac(virtio_net_device_t *dev, uint8_t *mac);
