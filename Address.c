#include <stdio.h>
#include <stdlib.h>

int main() {
    int *heap_dummy = malloc(sizeof(int));
    int stack_dummy;
    printf("Heap Address: %p  Stack Address: %p\n", &heap_dummy, &stack_dummy);
    free(heap_dummy);
}
