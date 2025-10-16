#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* sentinel;
    int size;
} DLL;

typedef struct {
    Node* node;
    DLL* dll;
} DLL_Iterator;

void dll_initialize(DLL* dll);
void dll_addLast(DLL* dll, void* data);
void dll_addFirst(DLL* dll, void* data);
void* dll_getLast(DLL* dll);
void* dll_getFirst(DLL* dll);
void* dll_get(DLL* dll, int i);
void dll_removeLast(DLL* dll);
void dll_removeFirst(DLL* dll);
void dll_remove(DLL* dll, void* data);
void dll_end(DLL* dll);

DLL_Iterator* dll_iter_create(DLL* dll);
void dll_iter_set(DLL_Iterator* iter, DLL* dll);
int dll_iter_hasNext(DLL_Iterator* iter);
void dll_iter_next(DLL_Iterator* iter);
void* dll_iter_data(DLL_Iterator* iter);
void dll_iter_remove(DLL_Iterator* iter);
void dll_iter_end(DLL_Iterator* iter);


void dll_initialize(DLL* dll) {
    dll->sentinel = malloc(sizeof(Node));
    
    dll->sentinel->next = dll->sentinel;
    dll->sentinel->prev = dll->sentinel;
    
    dll->size = 0;
}

void dll_addLast(DLL* dll, void* data) {
    Node* node = malloc(sizeof(Node));

    node->data = data;
    
    node->next = dll->sentinel;
    node->prev = dll->sentinel->prev;

    dll->sentinel->prev = node;
    node->prev->next = node;

    dll->size += 1;
}

void dll_addFirst(DLL* dll, void* data) {
    Node* node = malloc(sizeof(Node));

    node->data = data;

    node->prev = dll->sentinel;
    node->next = dll->sentinel->next;

    dll->sentinel->next = node;
    node->next->prev = node;

    dll->size += 1;
}

void* dll_getLast(DLL* dll) {
    return dll->sentinel->prev->data;
}

void* dll_getFirst(DLL* dll) {
    return dll->sentinel->next->data;
}

void* dll_get(DLL* dll, int i) {

    if (i >= dll->size) {
        printf("Index %i is not in the dll\n", i);
        abort();
    }

    DLL_Iterator* iter = dll_iter_create(dll);

    int index = 0;
    void* temp;
    for (iter; dll_iter_hasNext(iter); dll_iter_next(iter)) {
        if (index == i) {
            temp = dll_iter_data(iter);
            break;
        }
        index += 1;
    }

    dll_iter_end(iter);
    return temp;
}

void dll_removeLast(DLL* dll) {
    if (dll->size <= 0) {
        return;
    }

    Node* node = dll->sentinel->prev;

    node->prev->next = dll->sentinel;
    dll->sentinel->prev = node->prev;

    free(node->data);
    free(node);

    dll->size -= 1;
}

void dll_removeFirst(DLL* dll) {

    if (dll->size <= 0) {
        return;
    }

    Node* node = dll->sentinel->next;
    node->next->prev = dll->sentinel;
    dll->sentinel->next = node->next;

    free(node->data);
    free(node);

    dll->size -= 1;
}

void dll_remove(DLL* dll, void* data) {
    DLL_Iterator* iter = dll_iter_create(dll);
    for (iter; dll_iter_hasNext(iter); dll_iter_next(iter)) {
        if (data == dll_iter_data(iter)) {
            dll_iter_remove(iter);
        }
    }
}

void dll_end(DLL* dll) {
    DLL_Iterator* removeIter = dll_iter_create(dll);

    while (dll->size > 0) {
        dll_iter_remove(removeIter);
    }

    dll_iter_end(removeIter);
    free(dll->sentinel);
}


DLL_Iterator* dll_iter_create(DLL* dll) {
    DLL_Iterator* iter = malloc(sizeof(DLL_Iterator));
    iter->node = dll->sentinel->next;
    iter->dll = dll;
    return iter;
}

void dll_iter_set(DLL_Iterator* iter, DLL* dll) {
    iter->node = dll->sentinel->next;
    iter->dll = dll;
}

int dll_iter_hasNext(DLL_Iterator* iter) {
    return iter->node != iter->dll->sentinel;
}

void dll_iter_next(DLL_Iterator* iter) {
    iter->node = iter->node->next;
}

void* dll_iter_data(DLL_Iterator* iter) {
    return iter->node->data;
}

void dll_iter_remove(DLL_Iterator* iter) {

    if (iter->dll->size <= 0) {
        return;
    }

    Node* node = iter->node;
    iter->node = node->next;

    node->next->prev = node->prev;
    node->prev->next = node->next;

    free(node->data);
    free(node);

    iter->dll->size -= 1;
}

void dll_iter_end(DLL_Iterator* iter) {
    free(iter);
}
