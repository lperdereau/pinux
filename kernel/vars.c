#include "mem.h"
#include "print.h"
#include "util.h"

// Node structure for storing variables dynamically
typedef struct variable {
    char *name;
    char *value;
    struct variable *next;
} variable_t;

variable_t *variables = NULL;  // Head of the linked list of variables

// Function to store a variable and its value in dynamic memory
void set_variable(char *name, char *value) {
    // Create a new variable node
    variable_t *var = malloc(sizeof(variable_t));
    if (!var) {
        printf("Memory allocation failed!\n");
        return;
    }

    var->name = strdup(name);    // Duplicate the name string
    var->value = strdup(value);  // Duplicate the value string
    var->next = variables;       // Link to the existing list
    variables = var;             // Update the head of the list
}

// Function to get the value of a variable by its name
char *get_variable(char *name) {
    variable_t *current = variables;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;  // Return NULL if variable not found
}

void del_variable(char *name) {
    variable_t *current = variables;
    variable_t *previous = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                variables = current->next;
            }

            // Free the memory used by the variable
            free(current->name);
            free(current->value);
            free(current);

            printf("Variable deleted successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Variable not found.\n");
}
