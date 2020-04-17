#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree {
    int value;
    Tree left;
    Tree right;
};

Tree insertNode(Tree root, int key);
void findNode(Tree root, int key);
void printInorder(Tree root);
Tree deleteNode(Tree root, int key);
void deleteTree(Tree root);

Tree findMin(Tree root);

FILE *input;
FILE *output;

int message = 1;

int main(int argc, char* argv[]) {
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
    
    char command;
    int val;
    Tree tree;
    while(EOF != fscanf(input, "%c", &command)) {
        switch(command) {
            case 'i':
                fscanf(input, "%d", &val);
                tree = insertNode(tree, val);
                break;
            case 'd':
                fscanf(input, "%d", &val);
                tree = deleteNode(tree, val);
                if(message)
                    fprintf(output, "delete %d\n", val);
                message = 1;
                break;
            case 'f':
                fscanf(input, "%d", &val);
                findNode(tree, val);
                break;
            case 'p':
                fscanf(input, "%c", &command);
                if(command = 'i') {
                    printInorder(tree);
                    fprintf(output, "\n");
                }
                break;
        } 
    }

    fclose(input);
    fclose(output);
    deleteTree(tree);
    return 0;
}

Tree insertNode(Tree root, int key) {
    if(root == NULL) {
        root = (Tree)malloc(sizeof(struct BinarySearchTree));
        root->value = key;
        root->left = NULL;
        root->right = NULL;
        fprintf(output, "insert %d\n", key);
    }
    else if(key < root->value) {
        root->left = insertNode(root->left, key);
    }
    else if(key > root->value) {
        root->right = insertNode(root->right, key);
    }
    else {
        fprintf(output, "%d is already in the tree.\n", key);
    }
    return root;
}

void findNode(Tree root, int key) {
    if(root == NULL)
        fprintf(output, "%d is not in the tree.\n", key);
    else if(key < root->value)
        findNode(root->left, key);
    else if(key > root->value)
        findNode(root->right, key);
    else
        fprintf(output, "%d is in the tree.\n", key);
}

void printInorder(Tree root) {
    if(root) {
        printInorder(root->left);
        fprintf(output, "%d ", root->value);
        printInorder(root->right);
    }
}

Tree deleteNode(Tree root, int key) {
    Tree tmp;
    if(root == NULL) {
        fprintf(output, "Deletion Error : %d is not in the tree.\n", key);
        message = 0;
    }
    else if(key < root->value)
        root->left = deleteNode(root->left, key);
    else if(key > root->value)
        root->right = deleteNode(root->right, key);
    else if(root->left && root->right) {
        tmp = findMin(root->right);
        root->value = tmp->value;
        root->right = deleteNode(root->right, root->value);
    }
    else {
        tmp = root;
        if(root->left == NULL)
            root = root->right;
        else
            root = root->left;
        free(tmp);
    }
    return root;
}


void deleteTree(Tree root) {
    if(root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

Tree findMin(Tree root) {
    if(root == NULL)
        return NULL;
    while(root->left != NULL) {
        root = root->left;
    }
    return root;
}
