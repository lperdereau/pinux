#include <stdint.h>

#define DESC_RING_SIZE 256  // Example size for the descriptor ring

typedef struct {
    uint64_t addr;
    uint32_t len;
    uint32_t flags;
    uint32_t next;
} virtio_desc_t;

typedef struct {
    virtio_desc_t *desc;    // Array of descriptors
    uint16_t *avail;        // Availability ring (indices of available descriptors)
    uint16_t *used;         // Used ring (indices of used descriptors)
    uint16_t avail_idx;     // Index of the next available descriptor
    uint16_t used_idx;      // Index of the next used descriptor
    uint16_t size;          // Size of the descriptor ring
} virtio_desc_ring_t;

void virtio_alloc_desc_ring(virtio_desc_ring_t *ring, uint16_t size);
