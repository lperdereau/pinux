#include "virtio_ring.h"
#include "ports.h"
#include "pci.h"
#include "virtio_net.h"
#include "../cpu/isr.h"
#include "../kernel/print.h"

static virtio_desc_ring_t rx_ring;
static virtio_desc_ring_t tx_ring;

void virtio_net_receive_packet() {
    // Check if there is an available buffer in the receive ring
    uint16_t index = rx_ring.avail[0] % rx_ring.size;
    virtio_desc_t *desc = &rx_ring.desc[index];

    if (desc->len > 0) {
        // Process the received packet
        uintptr_t addr = (uintptr_t) desc->addr;
        uint8_t *data = (uint8_t *) addr;
        printf((char *) data);  // Example: Print the received packet

        // Mark the descriptor as used (acknowledge receipt of packet)
        rx_ring.used[rx_ring.avail[0] % rx_ring.size] = 1;  // Simplified, you'll want to increment the index
    }
}

// Function to process transmitted packets
void virtio_net_send_packet() {
    // Check if the transmit ring is ready for a new packet
    uint16_t index = tx_ring.avail[0] % tx_ring.size;
    virtio_desc_t *desc = &tx_ring.desc[index];

    if (desc->len > 0) {
        // Process the packet and send it out (this is just a placeholder, you'll need to fill the buffer)
        // Send packet via device (e.g., using DMA)

        // Mark the descriptor as used (packet sent)
        tx_ring.used[tx_ring.avail[0] % tx_ring.size] = 1;  // Simplified, increment the index
    }
}

static void virtio_net_interrupt_handler(registers_t *regs) {
    // First, check the device's status to make sure the interrupt is valid
    if (*virtio_dev->status & 0x01) {  // Check if the device is ready
        // Process receive queue (poll the used ring for available packets)
        virtio_net_receive_packet();

        // Process transmit queue (check if there are any completed packets)
        virtio_net_send_packet();
    }
}

void init_virtio_net() {
    uint8_t bus = 0;   // Example bus number
    uint8_t slot = 3;  // Example slot number
    uint8_t function = 0;  // Example function number

    check_virtio_device(bus, slot, function);
    // Scan PCI bus and initialize the Virtio device
    // virtio_initialize_device(bus, slot, virtio_dev);  // Assuming you have the correct PCI bus/slot

    // // Initialize descriptor rings for receive and transmit
    // virtio_alloc_desc_ring(&rx_ring, 128);
    // virtio_alloc_desc_ring(&tx_ring, 128);

    // // Register the Virtio-net interrupt handler for IRQ9
    // register_interrupt_handler(IRQ9, virtio_net_interrupt_handler);
    // pic_acknowledge_irq(IRQ9);
}
