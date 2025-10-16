#include <stdio.h>
#include "dll.c"


int main() {
    DLL dll;

    dll_initialize(&dll);

    DLL_Iterator* iter = dll_iter_create(&dll);
    for (int i = 0; i < 100; i += 1) {
        int* temp = malloc(sizeof(int));
        *temp = i;
        dll_addLast(&dll, temp);
    }
    
    dll_iter_set(iter, &dll);
    for (iter; dll_iter_hasNext(iter); dll_iter_next(iter)) {
        int n = *(int*)dll_iter_data(iter);
        printf("%i\n", n);
    }

    dll_iter_end(iter);
    
    dll_end(&dll);

    return 0;
}