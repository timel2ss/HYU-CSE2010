#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue* Queue;
struct _Queue {
    int* key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

typedef struct _Graph* Graph;
struct _Graph {
    int* node;
    int size;
    int** matrix;
};

typedef struct _Array* Array;
struct _Array {
    int* key;
    int size;
    int max_size;
};

Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b);
void TopSort(Graph G);
Queue MakeNewQueue(int X);
void Enqueue(Queue Q, int X);
int Dequeue(Queue Q);

Array makeArray(int size);
void append(Array A, int X);
void sort(Array A);
int findIndex(Graph G, int X);
void deleteQueue(Queue Q);
void deleteGraph(Graph G);
void deleteArray(Array A);

FILE* input;
FILE* output;

int main(int argc, char* argv[]) {
    if(argc <= 2) {
        printf("Not enough Arguments.\n");
        return 1;
    }
    input = fopen(argv[1], "r");
    if(input == NULL) {
        printf("File cannot be found.\n");
        return 2;
    }
    output = fopen(argv[2], "wt");

    char line[1024] = { 0, };
    char* ptr = line;
    fgets(line, 1023, input);

    int temp[512] = { 0, }, num, read, index = 0;
    while(sscanf(ptr, "%d%n", &num, &read) == 1) {
        temp[index++] = num;
        ptr += read;
    }
    
    Graph graph = CreateGraph(temp); 
    
    char tmp;
    int first, last;
    while(fscanf(input, "%d%c%d", &first, &tmp, &last) != EOF) {
        InsertEdge(graph, first, last);
    }
    
    int i, j;
    fprintf(output, "  ");
    for(i = 0; i < graph->size; i++) {
        fprintf(output, "%d ", graph->node[i]);
    }
    fprintf(output, "\n");
    
    for(i = 0; i < graph->size; i++) {
        fprintf(output, "%d ", graph->node[i]);
        for(j = 0; j < graph->size; j++) {
            fprintf(output, "%d ", graph->matrix[i][j]);
        }
        fprintf(output, "\n");
    }
   
    fprintf(output, "\n");
    
    TopSort(graph);

    fclose(input);
    fclose(output);
    deleteGraph(graph);
    return 0;
}

Graph CreateGraph(int* nodes) {
    int i, j;
    for(i = 0; i < 512; i++) {
        if(nodes[i] == 0)
            break;
    }

    Graph temp = (Graph)malloc(sizeof(struct _Graph));
    temp->size = i;
    temp->node = (int*)malloc(temp->size * sizeof(int));
    for(i = 0; i < temp->size; i++) {
        temp->node[i] = nodes[i];
    }
    temp->matrix = (int**)malloc((temp->size + 5) * sizeof(int));
    for(i = 0; i < temp->size; i++) {
        temp->matrix[i] = (int*)malloc((temp->size + 5) * sizeof(int));
    }
    for(i = 0; i < temp->size; i++) {
        temp->matrix[i] = (int*)malloc(temp->size * sizeof(int));
        for(j = 0; j < temp->size; j++) {
            temp->matrix[i][j] = 0;
        }
    }
    return temp;
}

void InsertEdge(Graph G, int a, int b) {
    int first = findIndex(G, a);
    int last = findIndex(G, b);
    G->matrix[first][last] = 1;
}

void TopSort(Graph G) {
    int i, j, count, deq, index, adjacent;
    Queue queue = MakeNewQueue(G->size);
    int* inDegrees = (int*)malloc(G->size * sizeof(int));
    Array array = makeArray(G->size);

    for(i = 0; i < G->size; i++){
        inDegrees[i] = 0;
    }

    for(j = 0; j < G->size; j++) {
        count = 0;
        for(i = 0; i < G->size; i++) {
            if(G->matrix[i][j] == 1)
                count += 1;
        }
        inDegrees[j] = count;
        if(inDegrees[j] == 0) {
            append(array, G->node[j]);
        }
    }

    sort(array);

    for(i = 0; i < array->size; i++) {
        Enqueue(queue, array->key[i]);
    }
    array->size = 0;

    while(queue->qsize > 0){
        deq = Dequeue(queue);
        fprintf(output, "%d ", deq);
        index = findIndex(G, deq);

        for(i = 0; i < G->size; i++) {
            if(G->matrix[index][i] == 1) {
                if(--inDegrees[i] == 0) {
                    append(array, G->node[i]);
                }
            }
        }
        sort(array);
        for(i = 0; i < array->size; i++) {
            Enqueue(queue, array->key[i]);
        }
        array->size = 0;
    }
    
    fprintf(output, "\n");
    deleteQueue(queue);
    deleteArray(array);
}

Queue MakeNewQueue(int X) {
    Queue temp = (Queue)malloc(sizeof(struct _Queue));
    temp->max_queue_size = X;
    temp->key = (int*)malloc(temp->max_queue_size * sizeof(int));
    temp->first = 0;
    temp->rear = -1;
    temp->qsize = 0;
    return temp;
}

void Enqueue(Queue Q, int X) {
    if(Q->qsize < Q->max_queue_size) {
        Q->key[++Q->rear] = X;
        Q->qsize += 1;
    }
}

int Dequeue(Queue Q) {
    if(Q->qsize > 0) {
        Q->qsize -= 1;
        return Q->key[Q->first++];
    }
}

Array makeArray(int size) {
    int i;
    Array temp = (Array)malloc(sizeof(struct _Array));
    temp->max_size = size;
    temp->size = 0;
    temp->key = (int*)malloc(sizeof(int) * size);
    return temp;
}

void append(Array A, int X) {
    A->key[A->size++] = X;
}

void sort(Array A) {
    int i, j, min, temp;
    for(i = 0; i < A->size - 1; i++) {
        min = i;
        for(j = i + 1; j < A->size; j++) {
            if(A->key[j] < A->key[min]) {
                min = j;
            }
        }
        temp = A->key[i];
        A->key[i] = A->key[min];
        A->key[min] = temp;
    }
}

int findIndex(Graph G, int X) {
    int i;
    for(i = 0; i < G->size; i++) {
        if(G->node[i] == X)
            return i;
    }
    return -1;
}

void deleteQueue(Queue Q) {
    free(Q->key);
    free(Q);
}

void deleteGraph(Graph G) {
    int i;
    free(G->node);
    for(i = 0; i < G->size; i++) {
        free(G->matrix[i]);
    }
    free(G->matrix);
    free(G);
}

void deleteArray(Array A) {
    free(A->key);
    free(A);
}
