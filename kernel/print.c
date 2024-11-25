#include "print.h"
#include "../drivers/display.h"


// Helper function to convert integer to string and store in buffer
int int_to_buffer(char *buf, int num) {
    int i = 0;
    if (num == 0) {
        buf[i++] = '0';
        return 1;
    }

    // Handle negative numbers
    if (num < 0) {
        buf[i++] = '-';
        num = -num;
    }

    // Convert number to string in reverse order
    int n = num;
    int length = 0;
    while (n > 0) {
        length++;
        n /= 10;
    }

    // Convert number to buffer
    for (int j = length - 1; j >= 0; j--) {
        buf[i + j] = (num % 10) + '0';
        num /= 10;
    }

    return i + length;
}

// Helper function to convert hexadecimal to string and store in buffer
int hex_to_buffer(char *buf, int num) {
    int i = 0;
    const char *hex_digits = "0123456789ABCDEF";

    if (num == 0) {
        buf[i++] = '0';
        return 1;
    }

    // Convert number to hex string in reverse order
    int n = num;
    int length = 0;
    while (n > 0) {
        length++;
        n /= 16;
    }

    // Convert hex to buffer
    for (int j = length - 1; j >= 0; j--) {
        buf[i + j] = hex_digits[num % 16];
        num /= 16;
    }

    return i + length;
}

// vsprintf function - formats the string into the buffer using variable arguments
int vsprintf(char *buf, const char *format, va_list args) {
    char *str;
    int i = 0;

    while (*format != '\0') {
        if (*format == '%') {
            format++; // Skip the '%' character

            // Handle different format specifiers
            if (*format == 's') {
                // Print a string
                str = va_arg(args, char*);
                while (*str) {
                    buf[i++] = *str++;
                }
            } else if (*format == 'd') {
                // Print a signed integer
                int num = va_arg(args, int);
                i += int_to_buffer(buf + i, num); // Helper to convert int to buffer
            } else if (*format == 'x') {
                // Print a hexadecimal number
                int num = va_arg(args, int);
                i += hex_to_buffer(buf + i, num); // Helper to convert hex to buffer
            } else if (*format == '%') {
                // Print the '%' character itself
                buf[i++] = '%';
            } else {
                // Handle unknown format specifiers
                buf[i++] = '?';
            }
        } else {
            // Just copy the character to the buffer
            buf[i++] = *format;
        }

        format++;
    }

    buf[i] = '\0'; // Null-terminate the string
    return i; // Return the length of the formatted string
}

// sprintf function - formats the string and returns the formatted result
int sprintf(char *buf, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsprintf(buf, format, args);
    va_end(args);
    return len; // Return the length of the formatted string
}

// printf function - prepares the arguments and calls vprintf to print the formatted string
void printf(const char *format, ...) {
    char buffer[256]; // Buffer to hold the formatted string
    va_list args;

    // Start processing variable arguments
    va_start(args, format);

    // Use sprintf to format the string into the buffer
    int len = vsprintf(buffer, format, args);

    // End processing variable arguments
    va_end(args);

    // Print the formatted string to the screen
    print_string(buffer);
}
