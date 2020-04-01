#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node
{
    ElementType element;
    Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);

void Insert(ElementType X, List L, Position P);
void PrintList(List L);
void Delete(ElementType X, List L);
Position Find(ElementType X, List L);

FILE *output;

int main(int argc, char *argv[]){
    char command;
    int key1, key2;
    FILE *input;
    Position header;
    Position tmp;
    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("File cannot be found\n");
        return 1;
    }
    if(argc <= 2){
        printf("Please type output file's name\n");
        return 2;
    }
    output = fopen(argv[2], "wt");
    header = MakeEmpty(header);
    while(1){
        command = fgetc(input);
        if(feof(input)) break;
        switch(command){
            case 'i':
                fscanf(input, "%d %d", &key1, &key2);
                if(key2 == -1)
                    Insert(key1, header, header);
                else {
                    tmp = Find(key2, header);
                    if(!IsLast(tmp, header))
                        Insert(key1, header, tmp->next);
                    else
                        fprintf(output, "Insertion(%d) Failed: cannot find the location to be inserted\n", key1);
                }
                break;
            case 'd':
                fscanf(input, "%d", &key1);
                tmp = Find(key1, header);
                if(!IsLast(tmp, header)){
                    Delete(key1, tmp);
                }
                else
                    fprintf(output, "Deletion(%d) Failed: Element %d is not in the list\n", key1, key1);

                break;
            case 'f':
                fscanf(input, "%d", &key1);
                tmp = Find(key1, header);
                if(IsLast(tmp, header))
                    fprintf(output, "Finding(%d) Failed: Element %d is not in the list\n", key1, key1);
                else {
                    if(tmp->element > 0)
                        fprintf(output, "Key of the previous node of %d is %d\n", key1, tmp->element);
                    else
                        fprintf(output, "Key of the previous node of %d is head.\n", key1);
                }
                break;
            case 'p':
                PrintList(header);
                break;
            default:
                break;
        }
    }
    
    DeleteList(header);
    fclose(input);
    fclose(output);
    return 0;
}

List MakeEmpty(List L) {
    L = (List)malloc(sizeof(struct Node));
    L->element = 0;
    L->next = NULL;
    return L;
}

int IsEmpty(List L) {
    return (L->next == NULL);
}

int IsLast(Position P, List L) {
    return (P->next == NULL);
}

void DeleteList(List L) {
    Position freeNode = L;
    Position tmp = L->next;
    while(freeNode != NULL) {
        free(freeNode);
        freeNode = tmp;
        if(tmp != NULL)
            tmp = tmp->next;
    }
    
}

void Insert(ElementType X, List L, Position P) {
    Position newNode = (Position)malloc(sizeof(struct Node));
    newNode->element = X;
    newNode->next = P->next;
    P->next = newNode;
}

void PrintList(List L) {
    while(L->next != NULL) {
        L = L->next;
        fprintf(output, "key: %d  ", L->element);
    }
    fprintf(output, "\n");
}

void Delete(ElementType X, List L) {
    Position tmp = L->next;
    L->next = tmp->next;
    free(tmp);
}

Position Find(ElementType X, List L) {
    Position finder = L;
    while(finder->next != NULL && finder->next->element != X){
        finder = finder->next;
    }
    return finder;
}

