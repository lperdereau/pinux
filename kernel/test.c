#include "mem.h"
#include "../drivers/display.h"

void test_mem() {
    print_string("init_dynamic_mem()\n");
    print_dynamic_node_size();
    print_dynamic_mem();
    print_nl();

    int *ptr1 = mem_alloc(5);
    print_string("int *ptr1 = mem_alloc(5)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr2 = mem_alloc(10);
    print_string("int *ptr2 = mem_alloc(10)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr1);
    print_string("mem_free(ptr1)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr3 = mem_alloc(2);
    print_string("int *ptr3 = mem_alloc(2)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr2);
    print_string("mem_free(ptr2)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr3);
    print_string("mem_free(ptr3)\n");
    print_dynamic_mem();
    print_nl();
}
