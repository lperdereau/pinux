#include <stdint.h>
#include "timer.h"
#include "../drivers/display.h"
#include "../drivers/ports.h"
#include "isr.h"

uint32_t tick = 0;

void sleep_ms(unsigned long milliseconds) {
    unsigned long start_time = clock();  // Capture the current time
    unsigned long end_time = start_time + milliseconds;  // Calculate the target time

    // Wait until the specified amount of time has passed
    while (clock() < end_time) {
        // You could add a small 'yield' or 'nop' here to reduce CPU usage if needed
    }
}

uint32_t clock() {
    return tick;
};

static void timer_callback(registers_t *regs) {
    tick++;
}

void init_timer(uint32_t freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
