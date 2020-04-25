#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;
struct AVLNode {
    ElementType Element;
    AVLTree left;
    AVLTree right;
    int Height;
};

AVLTree Insert(ElementType X, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
void printInorder(AVLTree T);
void deleteTree(AVLTree T);

int height(Position P);
int max(int val1, int val2);

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
    
    AVLTree tree;
    int val;

    while(EOF != fscanf(input, "%d", &val)) {
        tree = Insert(val, tree);
        printInorder(tree);
        fprintf(output, "\n");
    }
    
    fclose(input);
    fclose(output);
    deleteTree(tree);
    return 0;
}

AVLTree Insert(ElementType X, AVLTree T) {
    if(T == NULL) {
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Element = X;
        T->Height = 0;
        T->left = NULL;
        T->right = NULL;
    }
    else if(X < T->Element) {
        T->left = Insert(X, T->left);
        if(abs(height(T->left) - height(T->right)) >= 2) {
            if(X < T->left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
        T->Height = max(height(T->left), height(T->right)) + 1;
    }
    else if(X > T->Element) {
        T->right = Insert(X, T->right);
        if(abs(height(T->left) - height(T->right)) >= 2) {
            if(X > T->right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
        T->Height = max(height(T->left), height(T->right)) + 1;
    }
    else {
       fprintf(output, "[Error] %d already in the tree!\n", X); 
    }
    return T;
}

Position SingleRotateWithLeft(Position node) {
    Position tmp;
    tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->Height = max(height(node->left), height(node->right)) + 1;
    tmp->Height = max(height(tmp->left), node->Height) + 1;
    return tmp;
}

Position SingleRotateWithRight(Position node) {
    Position tmp;
    tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    node->Height = max(height(node->left), height(node->right)) + 1;
    tmp->Height = max(height(tmp->right), node->Height) + 1;
    return tmp;
}

Position DoubleRotateWithLeft(Position node) {
    node->left = SingleRotateWithRight(node->left);
    return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node) {
    node->right = SingleRotateWithLeft(node->right);
    return SingleRotateWithRight(node);
}

void printInorder(AVLTree T) {
    if(T != NULL) {
        printInorder(T->left);
        fprintf(output, "%d(%d) ", T->Element, T->Height);
        printInorder(T->right);
    }
}

void deleteTree(AVLTree T) {
    if(T != NULL) {
        deleteTree(T->left);
        deleteTree(T->right);
        free(T);
    }
}

int height(Position P) {
    if(P == NULL)
        return -1;
    else
        return P->Height;
}

int max(int val1, int val2) {
    return ((val1 > val2) ? val1 : val2);
}
