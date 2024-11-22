#include "../kernel/util.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../shell/shell.h"
#include "keyboard.h"
#include "ports.h"
#include "display.h"


bool is_ignored_scancode(uint8_t scancode) {
    size_t ignored_count = sizeof(ignored_scancodes) / sizeof(ignored_scancodes[0]);
    for (size_t i = 0; i < ignored_count; ++i) {
        if (scancode == ignored_scancodes[i]) {
            return true;
        }
    }
    return false;
}

uint8_t last_scancode = 0xFF;
unsigned long last_keypress_time = 0;

bool is_repeated(uint8_t scancode) {
    unsigned long current_time = clock();
    bool ret;

    if (scancode == last_scancode && (current_time - last_keypress_time) < KEY_REPEAT_DELAY) {
        ret = true;
    } else {
        ret = false;
    }
    last_keypress_time = current_time;
    last_scancode = scancode;
    return ret;
}

bool shift_pressed = false;

void check_shift(uint8_t scancode) {
    if (scancode & 0x80) {
        if (scancode == (LEFT_SHIFT | 0x80) || scancode == (RIGHT_SHIFT | 0x80)) {
            shift_pressed = false;
        }
    }
    if (scancode == LEFT_SHIFT || scancode == RIGHT_SHIFT) {
        shift_pressed = true;
    }
}

bool caps_lock = false;

void check_caps_lock(uint8_t scancode) {
    if (scancode == CAPS_LOCK) {
        caps_lock = !caps_lock;
    }
}

void check_control_keys(uint8_t scancode) {
    check_shift(scancode);
    check_caps_lock(scancode);
}

char get_letter(uint8_t scancode) {
    if (shift_pressed || caps_lock) {
        return sc_shifted_ascii[scancode];
    } else {
        return sc_ascii[scancode];
    }
}

bool skip_print(uint8_t scancode) {
    if (is_ignored_scancode(scancode)) return true;
    if (is_repeated(scancode)) return true;
    if (scancode > SC_MAX && scancode != 130) return true; // Release event
    return false;
}

bool backspace(char s[]) {
    int len = string_length(s);
    if (len > 0) {
        s[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    char letter = get_letter(scancode);

    check_control_keys(scancode);

    if (skip_print(scancode)) return;

    if (scancode == BACKSPACE) {
        if (backspace(key_buffer)) {
            print_backspace();
        }
    } else if (scancode == ENTER) {
        print_nl();
        c_shell(key_buffer);
        key_buffer[0] = '\0';
    } else {
        append(key_buffer, letter);
        print_string((char[]){letter, '\0'});
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}
