#include "shell.h"
#include "../drivers/display.h"
#include "../kernel/test.h"
#include "../kernel/util.h"
#include "../kernel/vars.h"

shell_function_t c_shell = NULL;

command_result_t last_result;

void execute_command(char *command, command_result_t *result) {
    if (strcmp(command, "exit") == 0) {
        result->message = "Stopping the CPU. Bye!\n";
        result->code = 0;
        print_string(result->message);
        asm volatile("hlt");
    }
    else if (strncmp(command, "echo ", 5) == 0) {
        // Remove the "echo " prefix
        char *args = command + 5;  // Skip the "echo " part
        result->message = args;
        result->code = 0;
        print_string(args);
    }
    else if (strcmp(command, "") == 0) {
        result->code = 0;
    }
    else if (strchr(command, '=') != NULL) {
        // Command has an '=' character, it could be a variable assignment
        char *equal_sign = strchr(command, '=');
        *equal_sign = '\0';  // Split the string at '='

        // Now command is the variable name and equal_sign+1 is the value
        char *var_name = command;
        char *var_value = equal_sign + 1;

        set_variable(var_name, var_value);
        result->message = "Variable assigned successfully.";
        result->code = 0;
    }
    else if (strncmp(command, "del ", 4) == 0) {
        // Handle the "del" command to delete a variable
        char *var_name = command + 4;  // Skip the "del " part
        del_variable(var_name);
        result->code = 0;
    }
    else if (strcmp(command, "test") == 0) {
        test_mem();
        result->code = 0;
    }
    else {
        result->message = "Unknown command: ";
        result->code = 1;
        print_string(result->message);
        print_string(command);
    }
}

void execute_shell(char *command) {
    char* output = (char*){'\0'};

    command_result_t result = {NULL, 1};  // Default to failure with no message

    execute_command(command, &result);
    last_result = result;
    print_string("\n> ");
}

void init_shell() {
    c_shell = execute_shell;
}
