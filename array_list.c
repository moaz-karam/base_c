#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void** items;
    int size;
    int length;
} ArrayList;

void AL_initialize(ArrayList* al);
void AL_addLast(ArrayList* al, void* item);
void AL_resize(ArrayList* al);
void AL_removeLast(ArrayList* al);
void AL_end(ArrayList* al);

int main() {

    ArrayList al;

    AL_initialize(&al);

    for (int i = 0; i < 10; i += 1) {
        ArrayList* tempAL1 = malloc(sizeof(ArrayList));
        AL_initialize(tempAL1);
        for (int t = 0; t < 10; t += 1) {
            ArrayList* tempAL2 = malloc(sizeof(ArrayList));
            AL_initialize(tempAL2);
            for (int j = 0; j < 10; j += 1) {
                int* temp = malloc(sizeof(int));
                *temp = j;
                AL_addLast(tempAL2, temp);
            }
            AL_addLast(tempAL1, tempAL2);
        }
        AL_addLast(&al, tempAL1);
    }

    for (int i = 0; i < 10; i += 1) {
        ArrayList* tempAL1 = (ArrayList*)al.items[i];

        for (int t = 0; t < 10; t += 1) {
            ArrayList* tempAL2 = (ArrayList*)tempAL1->items[t];

            for (int j = 0; j < 10; j += 1) {
                int tempN = *(int*)(tempAL2->items[j]);
                printf("%i\t%i\t%i\n", i, t, tempN);
            }

            AL_end(tempAL2);
        }


        AL_end(tempAL1);
    }


    AL_end(&al);

    return 0;
}

void AL_initialize(ArrayList* al) {
    al->length = 4;
    al->size = 0;
    al->items = malloc(sizeof(void*) * al->length);
}

void AL_addLast(ArrayList* al, void* item) {
    AL_resize(al);
    al->items[al->size] = item;
    al->size += 1;
}

void AL_resize(ArrayList* al) {
    if ((float)al->size / (float)al->length < 1) {
        return;
    }
    al->length *= 2;
    al->items = realloc(al->items, sizeof(void*) * al->length);
}

void AL_removeLast(ArrayList* al) {
    void* temp = al->items[al->size - 1];
    free(temp);
    al->size -= 1;
}

void AL_end(ArrayList* al) {
    for (int i = 0; i < al->size; i += 1) {
        if (al->items[i] == NULL) {
            continue;
        }
        void* temp = al->items[i];
        al->items[i] = NULL;
        free(temp);
    }
    free(al->items);
}