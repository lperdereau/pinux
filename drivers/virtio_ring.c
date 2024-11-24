#include "virtio_ring.h"
#include "../kernel/mem.h"
#include "../kernel/print.h"


void virtio_alloc_desc_ring(virtio_desc_ring_t *ring, uint16_t size) {
    ring->size = size;
    ring->desc = malloc(size * sizeof(virtio_desc_t));   // Allocate memory for descriptors
    ring->avail = malloc(size * sizeof(uint16_t));       // Allocate memory for availability ring
    ring->used = malloc(size * sizeof(uint16_t));        // Allocate memory for used ring

    // Initialize indices
    ring->avail_idx = 0;
    ring->used_idx = 0;
}
