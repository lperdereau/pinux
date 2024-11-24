#include "mem.h"
#include "print.h"
// #include "../drivers/pci.h"

void test_mem() {
    printf("init_dynamic_mem()\n");
    print_dynamic_node_size();
    print_dynamic_mem();
    printf("\n");

    int *ptr1 = malloc(5);
    printf("int *ptr1 = malloc(5)\n");
    print_dynamic_mem();
    printf("\n");

    int *ptr2 = malloc(10);
    printf("int *ptr2 = malloc(10)\n");
    print_dynamic_mem();
    printf("\n");

    free(ptr1);
    printf("free(ptr1)\n");
    print_dynamic_mem();
    printf("\n");

    int *ptr3 = malloc(2);
    printf("int *ptr3 = malloc(2)\n");
    print_dynamic_mem();
    printf("\n");

    free(ptr2);
    printf("free(ptr2)\n");
    print_dynamic_mem();
    printf("\n");

    free(ptr3);
    printf("free(ptr3)\n");
    print_dynamic_mem();
    printf("\n");
}
