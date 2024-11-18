#include "../drivers/display.h"

void main() {
    clear_screen();
    char* line = "Hello World!\n";
    print_string(line);
}
