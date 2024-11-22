#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../shell/shell.h"

#include "util.h"
#include "mem.h"

void main() {
    clear_screen();
    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing timer (IRQ 0).\n");
    uint32_t timer_frequency = 1000;
    init_timer(timer_frequency);


    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

    print_string("Initializing dynamic memory.\n");
    init_dynamic_mem();

    print_string("Initializing shell.\n");
    init_shell();

    clear_screen();
    print_string("Welcome to Pinux!\n");
    print_string("> ");
}
