#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"

void main() {
    clear_screen();
    char* line = "Hello World!\n";
    print_string(line);
    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
}
