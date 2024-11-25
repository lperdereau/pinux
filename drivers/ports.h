#pragma once

#include <stdint.h>

unsigned char port_byte_in(uint16_t port);

void port_byte_out(uint16_t port, uint8_t data);
void outb(uint16_t port, uint32_t value);
uint32_t inb(uint16_t port);
