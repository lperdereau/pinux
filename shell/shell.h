#include <stddef.h>

typedef void (*shell_function_t)(char *command);

typedef struct {
    char *message;
    int code;
} command_result_t;

extern shell_function_t c_shell;

void init_shell();
void execute_shell(char *command);
