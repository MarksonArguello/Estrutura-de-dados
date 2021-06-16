#include <stdio.h>
#include<stdlib.h>

typedef struct _TREE {
    int value;
    int height;
    struct _TREE* left;
    struct _TREE* right;
}TREE;

void showTree(TREE* node) {

    if (node == NULL) return;
    printf("%d\n", node->value);
    showTree(node -> left);
    showTree(node -> right);
}


int max(int a, int b) {
    if (a >= b)
        return a;
    return b;
}


TREE* createNode(int value) {
    TREE *node = (TREE *) malloc(sizeof(TREE));
    node -> left = node -> right = NULL;
    node -> value = value;
    node -> height = 1;
    return (node);
}

TREE* rightRotation(TREE* node) {
    TREE *leftNode = node->left;
    TREE *Tree = leftNode->right;

    leftNode->right = node;
    node->left = Tree;


    int rightHeight = 0, leftHeight = 0;
    if (node -> right != NULL)
        rightHeight = node -> right -> height;
    if (node -> left != NULL)
        leftHeight = node -> left -> height;


    node->height = 1 + max(leftHeight, rightHeight);

    if (leftNode -> right != NULL)
        rightHeight = leftNode -> right -> height;
    if (leftNode -> left != NULL)
        leftHeight = leftNode -> left -> height;

    leftNode->height = 1 + max(leftHeight, rightHeight);

    return leftNode;
}

TREE* leftRotation(TREE* node) {
    TREE *rightNode = node->right;
    TREE *Tree = rightNode->left;


    rightNode->left = node;
    node->right = Tree;


    int rightHeight = 0, leftHeight = 0;

    if (node -> right != NULL)
        rightHeight = node -> right -> height;
    if (node -> left != NULL)
        leftHeight = node -> left -> height;

    node->height = 1 + max(leftHeight, rightHeight);

    if (rightNode -> right != NULL)
        rightHeight = rightNode -> right -> height;
    if (rightNode -> left != NULL)
        leftHeight = rightNode -> left -> height;

    rightNode->height = 1 + max(rightHeight, leftHeight);

    return rightNode;
}


TREE* rebalance(TREE* node, int value) {

    int rightHeight = 0, leftHeight = 0;

    if (node -> right != NULL)
        rightHeight = node -> right -> height;
    if (node -> left != NULL)
        leftHeight = node -> left -> height;


    if (node->left != NULL && leftHeight > 1 + rightHeight && value < node->left->value)
        return rightRotation(node);

    if (node->right!= NULL && rightHeight > 1 + leftHeight && value > node->right->value)
        return leftRotation(node);

    if (node->left != NULL && leftHeight > 1 + rightHeight && value > node->left->value)
    {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    if (node->right!= NULL && rightHeight > 1 + leftHeight && value < node->right->value)
    {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    return node;
}

TREE* insereAVL(TREE* node, int value) {
    if (node == NULL) {
       return createNode(value);
    }

    int newHeight = 0;

    if (value < node-> value) {
        node->left = insereAVL(node -> left, value);
    } else if (value > node -> value) {
        node -> right = insereAVL(node -> right, value);

    } else {
        return node;
    }
    int rightHeight = 0, leftHeight = 0;

    if (node -> right != NULL)
        rightHeight = node -> right -> height;
    if (node -> left != NULL)
        leftHeight = node -> left -> height;

    node -> height = max(rightHeight ,leftHeight) + 1;

    return rebalance(node, value);

}


int main() {
    int value;
    TREE* root = NULL;
    while(!feof(stdin)) {
        if (scanf("%d", &value) == 1) {
            root = insereAVL(root, value);
        }
    }
    showTree(root);
    return 0;
}
