#include "mem.h"
#include "../drivers/display.h"

void test_mem() {
    print_string("init_dynamic_mem()\n");
    print_dynamic_node_size();
    print_dynamic_mem();
    print_nl();

    int *ptr1 = malloc(5);
    print_string("int *ptr1 = malloc(5)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr2 = malloc(10);
    print_string("int *ptr2 = malloc(10)\n");
    print_dynamic_mem();
    print_nl();

    free(ptr1);
    print_string("free(ptr1)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr3 = malloc(2);
    print_string("int *ptr3 = malloc(2)\n");
    print_dynamic_mem();
    print_nl();

    free(ptr2);
    print_string("free(ptr2)\n");
    print_dynamic_mem();
    print_nl();

    free(ptr3);
    print_string("free(ptr3)\n");
    print_dynamic_mem();
    print_nl();
}
