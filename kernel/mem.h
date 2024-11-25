#pragma once

#include <stdint.h>
#include <stddef.h>

#define NULL_POINTER ((void*)0)

void memcpy(uint8_t *source, uint8_t *dest, uint32_t nbytes);

void init_dynamic_mem();

void print_dynamic_node_size();

void print_dynamic_mem();

void *malloc(size_t size);

void free(void *p);
