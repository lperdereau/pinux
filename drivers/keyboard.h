#pragma once

#define SC_MAX 57

// Constants for scancodes of Shift keys
#define CAPS_LOCK 0x3A
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define SHIFT_RELEASE 0xAA // Release code for left shift
#define SHIFT_RIGHT_RELEASE 0xB6 // Release code for right shift
#define BACKSPACE 0x0E
#define ENTER 0x1C

#define KEY_REPEAT_DELAY 200

static char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

static char* sc_shifted_ascii[] = {"?", "?", "1", "2", "3", "4", "5", "6",
                                "7", "8", "9", "0", "?", "_", "?", "?", "A", "Z", "E", "R", "T", "Y",
                                "U", "I", "O", "P", "?", "*", "?", "?", "Q", "S", "D", "F", "G",
                                "H", "J", "K", "L", "M", "%", (char[]){0xE3, '\0'}, "?", ">", "W", "X", "C", "V",
                                "B", "N", "\?", ".", "/", "+", "?", "?", "?", " "};

static char* sc_ascii[] = {"?", "?", "&", (char[]){0x82, '\0'}, "\"", "\"", "(", (char[]){0xA7, '\0'},
                         (char[]){0xE8, '\0'}, "!", "c", (char[]){0xE0, '\0'}, ")", "-", "?", "?", "a", "z", "e", "r", "t", "y",
                         "u", "i", "o", "p", "^", "$", "?", "?", "q", "s", "d", "f", "g",
                         "h", "j", "k", "l", "m", "u", "`", "?", "<", "w", "x", "c", "v",
                         "b", "n", ",", ";", ":", "=", "?", "?", "?", " "};

static const uint8_t ignored_scancodes[] = {LEFT_SHIFT, RIGHT_SHIFT};


static char key_buffer[256];
void init_keyboard();
