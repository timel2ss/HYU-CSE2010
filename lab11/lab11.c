#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;

struct ListNode {
    int Element;
};

struct HashTbl {
    int TableSize;
    List* TheLists;
};

void Insert(HashTable H, int value, int solution);
void Delete(HashTable H, int value, int solution);
int Find(HashTable H, int value, int solution);
void printTable(HashTable H);
int Hash(int value, int Size, int i, int solution);

HashTable makeTable(int size);

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

    int size, sol, val, res;
    char solution[11], command;
    fscanf(input, "%10s", solution);
    
    if(strcmp(solution, "Linear") == 0)
        sol = 1;
    else
        sol = 2;
    
    fscanf(input, "%d", &size);

    HashTable hashTable = makeTable(size);
    
    while(fscanf(input, "%c", &command) != EOF) {
        switch(command) {
            case 'i':
                fscanf(input, "%d", &val);
                Insert(hashTable, val, sol);
                break;
            case 'd':
                fscanf(input, "%d", &val);
                Delete(hashTable, val, sol);
                break;
            case 'f':
                fscanf(input, "%d", &val);
                res = Find(hashTable, val, sol);
                if(res == -1)
                    fprintf(output, "Not found\n");
                else
                    fprintf(output, "Find %d\n", val);
                break;
            case 'p':
                printTable(hashTable);
                break;
        }
    }

    int i;
    for(i = 0; i < hashTable->TableSize; i++) {
        free(hashTable->TheLists[i]);
    }
    free(hashTable->TheLists);
    free(hashTable);

    fclose(input);
    fclose(output);
    return 0;
}

void Insert(HashTable H, int value, int solution) {
    if(Find(H, value, solution) != -1) {
        fprintf(output, "Already exists\n");
    }
    else {
        int i;
        for(i = 0; i < H->TableSize; i++) {
            int hash = Hash(value, H->TableSize, i, solution);
            if(H->TheLists[hash]->Element == 0) {
                H->TheLists[hash]->Element = value;
                fprintf(output, "Inserted %d\n", value);
                break;
            }
        }
    }
}

void Delete(HashTable H, int value, int solution) {
    int index = Find(H, value, solution);
    if(index != -1) {
        H->TheLists[index]->Element = 0;
        fprintf(output, "Deleted %d\n", value);
    }
    else
        fprintf(output, "%d not exists\n", value);
}

int Find(HashTable H, int value, int solution) {
    int i;
    for(i = 0; i < H->TableSize; i++) {
        if(H->TheLists[i]->Element == value)
            return i;
    }
    return -1;
}

void printTable(HashTable H) {
    int i;
    for(i = 0; i < H->TableSize; i++) {
        fprintf(output, "%d ", H->TheLists[i]->Element);
    }
    fprintf(output, "\n");
}

int Hash(int value, int Size, int i, int solution) {
    if(solution == 1) {
        return (value + i) % Size;
    }
    return (value + i * i) % Size;
}

HashTable makeTable(int size) {
    int i;
    HashTable temp = (HashTable)malloc(sizeof(struct HashTbl));
    temp->TableSize = size;
    temp->TheLists = (List*)malloc(sizeof(Position) * size);
    for(i = 0; i < size; i++) {
        temp->TheLists[i] = (Position)malloc(sizeof(struct ListNode));
        temp->TheLists[i]->Element = 0;
    }
    return temp;
}
