#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet {
    int size_maze;
    int *ptr_arr;
}DisjointSets;

void init(DisjointSets *sets, DisjointSets* maze_print, int num);
void union_(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *sets, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);

int allUnion(DisjointSets *sets);

FILE *input;
FILE *output;

int main(int argc, char* argv[]){
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
    fscanf(input, "%d", &size);
    srand((unsigned int)time(NULL));

    DisjointSets *sets = (DisjointSets*)malloc(sizeof(DisjointSets));
    DisjointSets *maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));
    init(sets, maze_print, size);
    
    createMaze(sets, maze_print, size);
    printMaze(maze_print, size);
    
    fclose(input);
    fclose(output);
    freeMaze(sets, maze_print);
    return 0;
}

void init(DisjointSets *sets, DisjointSets* maze_print, int num) {
    int i;
    
    sets->size_maze = num * num + 1;
    sets->ptr_arr = (int*)malloc(sizeof(int) * sets->size_maze);
    maze_print->size_maze = (num - 1) * num * 2;
    maze_print->ptr_arr = (int*)malloc(sizeof(int) * (maze_print->size_maze));
    
    for(i = 0; i < sets->size_maze; i++) {
        sets->ptr_arr[i] = 0;
    }
    for(i = 0; i < maze_print->size_maze; i++) {
        maze_print->ptr_arr[i] = -1;
    }
}

void union_(DisjointSets *sets, int i, int j) {
    if(sets->ptr_arr[i] < sets->ptr_arr[j])
        sets->ptr_arr[j] = i;
    else {
        if(sets->ptr_arr[i] == sets->ptr_arr[j])
            sets->ptr_arr[i]--;
        sets->ptr_arr[j] = i;           
    }
}

int find(DisjointSets *sets, int i) {
    while(sets->ptr_arr[i] > 0) {
        i = sets->ptr_arr[i];
    }
    return i;
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num) {
    int edge, index;
    int find1, find2;
    while(!allUnion(sets)) {
        edge = rand() % maze_print->size_maze;
        if(maze_print->ptr_arr[edge] == 0)
            continue;
        if(edge % (2 * num - 1) < (2 * num - 1) / 2) {
            index = num * (edge / (2 * num - 1)) + (edge % (2 * num - 1)) + 1;
            find1 = find(sets, index);
            find2 = find(sets, index + 1);
            if(find1 != find2) {
                union_(sets, find1, find2);
                maze_print->ptr_arr[edge] = 0;
            }
        }
        else {
            index = num * (edge / (2 * num - 1)) + (edge % (2 * num - 1) - (2 * num - 1) / 2) + 1;
            find1 = find(sets, index);
            find2 = find(sets, index + num);
            if(find1 != find2) {
                union_(sets, find1, find2);
                maze_print->ptr_arr[edge] = 0;
            }
        }
    }
}

void printMaze(DisjointSets *sets, int num) {
    int i, j;

    fprintf(output, "+");
    for(i = 0; i < num; i++) {
        fprintf(output, "-+");
    }
    fprintf(output, "\n");

    for(i = 0; i < num; i++) {
        if(i == 0)
            fprintf(output, " ");
        else
            fprintf(output, "|");
        
        for(j = 0; j < num - 1; j++) {
            if(sets->ptr_arr[i * (2 * num - 1) + j] == -1)
                fprintf(output, " |");
            else
                fprintf(output, "  "); 
        }
        if(i == num - 1)
            fprintf(output, "  \n");
        else    
            fprintf(output, " |\n");

        for(j = num - 1; j < 2 * num - 1; j++) {
            if((i * (2 * num - 1) + j) < sets->size_maze) {
                if(sets->ptr_arr[i * (2 * num - 1) + j] == -1)
                    fprintf(output, "+-");
                else
                    fprintf(output, "+ ");
            }
        } 
        if(i != num - 1)
            fprintf(output, "+\n");
    }

    fprintf(output, "+");
    for(i = 0; i < num; i++) {
        fprintf(output, "-+");
    }
    fprintf(output, "\n");
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print) {
    free(sets->ptr_arr);
    free(sets);
    free(maze_print->ptr_arr);
    free(maze_print);
}

int allUnion(DisjointSets *sets) {
    int first, last;
    first = find(sets, 1);
    last = find(sets, sets->size_maze - 1);
    if(first != last)
        return 0;
    return 1;
}
