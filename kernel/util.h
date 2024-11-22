#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

int string_length(char s[]);
void append(char s[], char n);
void append_str(char s[], char n[]);
int strcmp(char s1[], char s2[]);
int strncmp(char s1[], char s2[], int n);
void int_to_string(int n, char str[]);