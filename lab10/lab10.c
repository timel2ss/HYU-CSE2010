#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int vertex;
    int dist;
    int prev;
}Node;

typedef struct Graph {
    int size;
    int** vertices;
    Node* nodes;
}Graph;

typedef struct Heap {
    int Capacity;
    int Size;
    Node* Element;
}Heap;

Graph* CreateGraph(int size);
void printShortestPath(Graph* g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);

Node CreateNode(int vertex, int dist, int prev);
int findIndex(Graph* G, int X);
int findHeapIndex(Heap* H, int X);
void rearrange(Heap* heap, int vertex, int distance);
void showPrev(Graph* G, int idx);

FILE* input;
FILE* output;

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

    int size;
    fscanf(input, "%d\n", &size);

    Graph* graph = CreateGraph(size + 1);
    int node1, node2, weight;

    while(fscanf(input, "%d-%d-%d", &node1, &node2, &weight) != EOF) {
        graph->vertices[node1][node2] = weight;
    }
    
    printShortestPath(graph);

    int i;
    free(graph->nodes);
    for(i = 0; i < graph->size; i++) {
        free(graph->vertices[i]);
    }
    free(graph->vertices);
    free(graph);
    return 0;
}

Graph* CreateGraph(int size) {
    int i, j;
    Graph* temp = (Graph*)malloc(sizeof(Graph));
    temp->size = size;
    temp->vertices = (int**)malloc(sizeof(int*) * size);
    temp->nodes = (Node*)malloc(sizeof(Node) * size);
    
    for(i = 0; i < size; i++) {
        temp->vertices[i] = (int*)malloc(sizeof(int) * size);
        temp->nodes[i].vertex = i;
        for(j = 0; j < size; j++) {
            temp->vertices[i][j] = 0;
        }
    }
    return temp;
}

void printShortestPath(Graph* g) {
    int i, j;
    Heap* heap = createMinHeap(g->size);

    for(i = 1; i < g->size; i++) {
        g->nodes[i].dist = INT_MAX;
        g->nodes[i].prev = -1;
    }
    g->nodes[1].dist = 0;
    for(i = 1; i < g->size; i++) {
        if(g->vertices[1][i] > 0) {
            g->nodes[i].dist = g->vertices[1][i];
            g->nodes[i].prev = 1;
            insertToMinHeap(heap, g->nodes[i].vertex, g->nodes[i].dist);
        }

    }
     
    Node u;
    int u_idx;
    while(heap->Size > 0) {
        u = deleteMin(heap);
        u_idx = findIndex(g, u.vertex);
        for(i = 1; i < g->size; i++) {
            if(g->vertices[u_idx][i] != 0) {
                if(u.dist + g->vertices[u_idx][i] < g->nodes[i].dist) {
                    g->nodes[i].dist = u.dist + g->vertices[u_idx][i];
                    g->nodes[i].prev = u.vertex;
                    rearrange(heap, g->nodes[i].vertex, g->nodes[i].dist);
                }
            }
        }
    }
    
    for(i = 2; i < g->size; i++) {
        if(g->nodes[i].prev == -1) {
            fprintf(output, "Cannot reach to node %d.\n", i);
            continue;
        }
        showPrev(g, i);
        fprintf(output, "%d (cost: %d)\n", g->nodes[i].vertex, g->nodes[i].dist);
    }
}

Heap* createMinHeap(int heapSize) {
    Heap* temp = (Heap*)malloc(sizeof(Heap));
    temp->Capacity = heapSize;
    temp->Size = 0;
    temp->Element = (Node*)malloc(sizeof(Node) * heapSize);
    return temp;
}

void insertToMinHeap(Heap* minHeap, int vertex, int distance) {
    int i;
    Node temp = CreateNode(vertex, distance, 0);
    if(minHeap->Size < minHeap->Capacity) {
        for(i = ++minHeap->Size; i != 1 && minHeap->Element[i / 2].dist > distance; i /= 2) {
            minHeap->Element[i] = minHeap->Element[i / 2];
        }
        minHeap->Element[i] = temp;
    }
}

Node deleteMin(Heap* minHeap) {
    int i, child;
    Node min, last;

    min = minHeap->Element[1];
    last = minHeap->Element[minHeap->Size--];

    for(i = 1; i * 2 <= minHeap->Size; i = child) {
        child = i * 2;
        if(child + 1 <= minHeap->Size && minHeap->Element[child + 1].dist < minHeap->Element[child].dist) {
            child += 1;
        }
        if(last.dist > minHeap->Element[child].dist) {
            minHeap->Element[i] = minHeap->Element[child];
        }
        else
            break;
    }
    minHeap->Element[i] = last;
    return min;
}

Node CreateNode(int vertex, int dist, int prev) {
    Node temp;
    temp.vertex = vertex;
    temp.dist = dist;
    temp.prev = prev;
    return temp;
}

int findIndex(Graph* G, int X) {
    int i;
    for(i = 1; i < G->size; i++) {
        if(G->nodes[i].vertex == X)
            return i;
    }
    return -1;
}

int findHeapIndex(Heap* H, int X) {
    int i;
    for(i = 1; i < H->Size; i++) {
        if(H->Element[i].vertex == X)
            return i;
    }
    return -1;
}

void rearrange(Heap* heap, int vertex, int distance) {
    int child, i;
    int idx = findHeapIndex(heap, vertex);
    heap->Element[idx].dist = distance;

    for(i = 1; i != 1 && i * 2 <= heap->Size; i = child) {
        child = i * 2;
        if(child + 1 <= heap->Size && heap->Element[child + 1].dist < heap->Element[child].dist) {
            child += 1;
        }
        if(heap->Element[child].dist < heap->Element[i].dist) {
            Node temp = heap->Element[i];
            heap->Element[i] = heap->Element[child];
            heap->Element[child] = temp;
        }
    }
}

void showPrev(Graph* G, int idx) {
    if(G->nodes[idx].prev != 1) {
        showPrev(G, G->nodes[idx].prev);
    }
    fprintf(output, "%d->", G->nodes[idx].prev);
}
