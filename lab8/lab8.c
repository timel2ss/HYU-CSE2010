#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct {
    int Capacity;
    int Size;
    int *Element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int DeleteMax(Heap *heap);
void PrintHeap(Heap *heap);

FILE *input;
FILE *output;

int main(int argc, char* argv[]) {
    if(argc <= 2) {
        printf("Not enough arguments.\n");
        return 1;
    }
    input = fopen(argv[1], "r");
    if(input == NULL) {
        printf("File cannot be found.\n");
        return 2;
    }
    output = fopen(argv[2], "wt");
    
    char command;
    int val, res;
    Heap* heap;
    
    while(EOF != fscanf(input, "%c", &command)) {
        switch(command) {
            case 'n':
                fscanf(input, "%d", &val);
                heap = CreateHeap(val);
                break;
            case 'i':
                fscanf(input, "%d", &val);
                Insert(heap, val);
                break;
            case 'f':
                fscanf(input, "%d", &val);
                res = Find(heap, val);
                if(res)
                    fprintf(output, "%d is in the heap.\n", val);
                else
                    fprintf(output, "%d is not in the heap.\n", val);

                break;
            case 'd':
                DeleteMax(heap);
                break;
            case 'p':
                PrintHeap(heap);
                break;
        }
    }

    fclose(input);
    fclose(output);

    free(heap->Element);
    free(heap);
    return 0;

}

Heap* CreateHeap(int heapSize) {
    Heap* temp = (Heap*)malloc(sizeof(Heap));
    temp->Capacity = heapSize;
    temp->Size = 0;
    temp->Element = (int*)malloc(sizeof(int) * temp->Capacity + 1);
    
    int i;
    for(i = 0; i < temp->Capacity; i++) {
        temp->Element[i] = 0;
    }
    return temp;
}

void Insert(Heap *heap, int value) {
    if(heap->Size >= heap->Capacity)
        fprintf(output, "Insert Error : heap is full.\n");
    else {
        if(Find(heap, value) == 1)
            fprintf(output, "%d is already in the heap.\n", value);
        else {
            int i;
            for(i = ++heap->Size; i != 1 && heap->Element[i / 2] < value; i /= 2) {
                heap->Element[i] = heap->Element[i / 2];
            }
            heap->Element[i] = value;
            fprintf(output, "insert %d\n", value);
        }
    }
}

int Find(Heap *heap, int value) {
    int i;
    for(i = 1; i <= heap->Size; i++) {
        if(heap->Element[i] == value)
            return 1;
    }
    return 0;
}

int DeleteMax(Heap *heap) {
    if(heap->Size == 0) {
        fprintf(output, "Delete Error : heap is empty.\n");
        return -1;
    }
    else {
        int i, child;
        int maxElement, lastElement;

        maxElement = heap->Element[1];
        lastElement = heap->Element[heap->Size--];

        for(i = 1; i * 2 <= heap->Size; i = child) {
            child = i * 2;
            if(child < heap->Size && heap->Element[child + 1] > heap->Element[child])
                child++;
            if(lastElement < heap->Element[child])
                heap->Element[i] = heap->Element[child];
            else
                break;
        }
        heap->Element[i] = lastElement;

        fprintf(output, "Max Element: %d deleted.\n", maxElement);
        return maxElement;
    }
}

void PrintHeap(Heap *heap) {
    if(heap->Size == 0)
        fprintf(output, "Print Error : heap is empty.\n");
    else {
        int i;
        for(i = 1; i <= heap->Size; i++) {
            fprintf(output, "%d ", heap->Element[i]);
        }
        fprintf(output, "\n");
    }
}
