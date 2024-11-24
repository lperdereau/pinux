#pragma once
#include <stdint.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC
#define PIC_MASTER_CMD   0x20  // Master PIC command port
#define PIC_MASTER_DATA  0x21  // Master PIC data port
#define PIC_SLAVE_CMD    0xA0  // Slave PIC command port
#define PIC_SLAVE_DATA   0xA1  // Slave PIC data port

#define PIC_EOI          0x20  // End of Interrupt command

// void get_mac_address();
uint32_t *pci_map_bar(uint8_t bus, uint8_t slot, uint8_t bar_index, uint32_t size_of_mmio_region);
void pic_acknowledge_irq(uint8_t irq);
void pci_scan();
void check_virtio_device(uint8_t bus, uint8_t slot, uint8_t function);
