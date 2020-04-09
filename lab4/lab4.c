#include <stdio.h>
#include <stdlib.h>

struct CompleteTree {
    int Size;
    int nodeNum;
    int* Element;
};

typedef struct CompleteTree* Tree;

void Insert(Tree tree, int value);
void printPreorder(Tree tree, int index);
void printInorder(Tree tree, int index);
void printPostorder(Tree tree, int index);
void FreeTree(Tree tree);

Tree CreateTree(int max);

FILE *input;
FILE *output;

int count = 0;

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Not enough arguments.\n");
        return 1;
    }
    input = fopen(argv[1], "r");
    if(input == NULL) {
        printf("File cannot be found.\n");
        return 2;
    }
    output = fopen(argv[2], "wt");
    
    Tree tree;
    int max, val, i;
    
    fscanf(input, "%d", &max);
    tree = CreateTree(max);
    
    while(EOF != fscanf(input, "%d", &val))
        Insert(tree, val);

    fprintf(output, "Preorder: ");
    printPreorder(tree, 1);
    fprintf(output, "\n");
    
    fprintf(output, "Inorder: ");
    printInorder(tree, 1);
    fprintf(output, "\n");
    
    fprintf(output, "Postorder: ");
    printPostorder(tree, 1);
    fprintf(output, "\n");
    
    fclose(input);
    fclose(output);
    FreeTree(tree);
    return 0;
}

void Insert(Tree tree, int value) {
    if(tree->nodeNum <= tree->Size) {
        tree->Element[tree->nodeNum++] = value;
        count++;
    }
    else
        fprintf(output, "Error! Tree is FULL.\n");
}

void printPreorder(Tree tree, int index) {
    if(tree && index <= count) {
        fprintf(output, "%d ", tree->Element[index]);
        printPreorder(tree, 2 * index);
        printPreorder(tree, 2 * index + 1);
    }
}
void printInorder(Tree tree, int index) {
    if(tree && index <= count) {
        printInorder(tree, 2 * index);
        fprintf(output, "%d ", tree->Element[index]);
        printInorder(tree, 2 * index + 1);
    }
}
void printPostorder(Tree tree, int index) {
    if(tree && index <= count) {
        printPostorder(tree, 2 * index);
        printPostorder(tree, 2 * index + 1);
        fprintf(output, "%d ", tree->Element[index]);
    }
}
void FreeTree(Tree tree) {
    free(tree->Element);
    free(tree);
}

Tree CreateTree(int max) {
    Tree tree = (Tree)malloc(sizeof(struct CompleteTree));
    tree->Element = (int*)malloc(sizeof(int) * (max + 1));
    tree->Size = max;
    tree->nodeNum = 1;
    return tree;
}
