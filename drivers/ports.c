#include <stdint.h>

/**
 * Read a byte from the specified port
 */
unsigned char port_byte_in(uint16_t port) {
    unsigned char result;
    /* Inline assembler syntax
     * !! Notice how the source and destination registers are switched from NASM !!
     *
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     *
     * Inputs and outputs are separated by colons
     */
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(uint16_t port, uint8_t data) {
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

// Function to write a value to an I/O port (32-bit using outl)
void outb(uint16_t port, uint32_t value) {
    // Write 32-bit value to the specified port using the `outl` instruction
    asm (
        "outl %%eax, %%dx"   // outl instruction: write the value in EAX to the port in DX
        :                     // No output operands
        : "a" (value),        // Input operand: value to be written (in EAX register)
          "d" (port)          // Input operand: port address (in DX register)
    );
}

// Function to read a value from an I/O port (32-bit using inl)
uint32_t inb(uint16_t port) {
    uint32_t result;
    // Read 32-bit value from the specified port using the `inl` instruction
    asm (
        "inl %%dx, %%eax"    // inl instruction: read a 32-bit value from the port into EAX
        : "=a" (result)          // Output operand: result of the read operation (in EAX)
        : "d" (port)          // Input operand: port address (in DX register)
    );
    return result;
}
