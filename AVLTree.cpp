#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct AVLNode_
{
    int value;
    int height;
    struct AVLNode_ *leftNode, *rightNode;
} AVLNode, *AVLTree;

int GetAVLHeight(AVLTree tree)
{
    if (tree == NULL)
        return 0;
    if (tree->leftNode == NULL && tree->rightNode == NULL)
    {
        tree->height = 1;
        return 1;
    }
    else if (GetAVLHeight(tree->leftNode) > GetAVLHeight(tree->rightNode))
    {
        tree->height = tree->leftNode->height + 1;
        return tree->height;
    }
    else
    {
        tree->height = tree->rightNode->height + 1;
        return tree->height;
    }
}

void AVLRightRotation(AVLTree &tree)
{
    AVLTree p = tree;
    tree = p->leftNode;
    p->leftNode = p->leftNode->rightNode;
    tree->rightNode = p;
}

void AVLLeftRotation(AVLTree &tree)
{
    AVLTree p = tree;
    tree = p->rightNode;
    p->rightNode = p->rightNode->leftNode;
    tree->leftNode = p;
}

int AVLGetBalanceFactor(AVLTree tree)
{
    if (tree == NULL || (tree->leftNode == NULL && tree->rightNode == 0))
        return 0;
    else
    {
        if (tree->leftNode != NULL && tree->rightNode != NULL)
            return tree->leftNode->height - tree->rightNode->height;
        else if (tree->leftNode)
            return tree->leftNode->height;
        else
            return -tree->rightNode->height;
    }
}

AVLNode *AVLRebalance(AVLTree &tree)
{
    GetAVLHeight(tree);
    int factor = AVLGetBalanceFactor(tree);
    if (factor > 1 && AVLGetBalanceFactor(tree->leftNode) > 0)
    {
        AVLRightRotation(tree);
    }
    else if (factor < -1 && AVLGetBalanceFactor(tree->rightNode) <= 0)
    {
        AVLLeftRotation(tree);
    }
    else if (factor > 1 && AVLGetBalanceFactor(tree->leftNode) <= 0)
    {
        AVLLeftRotation(tree->leftNode);
        AVLRightRotation(tree);
    }
    else if ((factor < -1 && AVLGetBalanceFactor(tree->rightNode) > 0))
    {
        AVLRightRotation(tree->rightNode);
        AVLLeftRotation(tree);
    }
    return tree;
}

int Max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

AVLNode *AVLSearch(AVLTree tree, int value, AVLNode *&father)
{
    AVLTree p = tree;
    father = NULL;
    while (p != NULL)
    {
        if (p->value == value)
        {
            return p;
        }
        father = p;
        (value < p->value) ? p = p->leftNode : p = p->rightNode;
    }
    return p;
}

AVLTree AVLInsertNode(AVLTree &tree, int value)
{
    if (tree == NULL)
    {
        AVLTree p = (AVLTree)calloc(1, sizeof(AVLNode));
        p->value = value;
        p->leftNode = NULL;
        p->rightNode = NULL;
        tree = p;
    }
    else if (value < tree->value)
        AVLInsertNode(tree->leftNode, value);
    else if (value > tree->value)
        AVLInsertNode(tree->rightNode, value);
    else
        return tree;

    if (tree->leftNode != NULL && tree->rightNode != NULL)
        tree->height = 1 + Max(tree->leftNode->height, tree->rightNode->height);
    else if (tree->leftNode == NULL && tree->rightNode == NULL)
        tree->height = 1;
    else if (tree->rightNode == NULL)
        tree->height = 1 + tree->leftNode->height;
    else
        tree->height = 1 + tree->rightNode->height;

    return AVLRebalance(tree);
}

int AVLDeleteNode(AVLTree &tree, int value)
{
    AVLNode *deleteNode, *fatherDelete = NULL, *p = tree;
    if ((deleteNode = AVLSearch(p, value, fatherDelete)) == NULL)
        return 0;
    if (deleteNode->leftNode != NULL && deleteNode->rightNode != NULL)
    {
        AVLNode *nF = deleteNode, *n = deleteNode->leftNode;
        while (n->rightNode != NULL)
        {
            nF = n;
            n = n->rightNode;
        }
        deleteNode->value = n->value;
        fatherDelete = nF;
        deleteNode = n;
    }
    AVLNode **f;
    if (deleteNode == tree)
        f = &tree;
    else
        (fatherDelete->leftNode == deleteNode) ? f = &fatherDelete->leftNode : f = &fatherDelete->rightNode;

    if (deleteNode->leftNode)
        *f = deleteNode->leftNode;
    else
        *f = deleteNode->rightNode;
    free(deleteNode);
    AVLRebalance(tree);
    return 1;
};

AVLTree AVLBuildTree(int *numbers, int length)
{
    AVLTree tree = NULL;
    for (int i = 0; i < length; i++)
        AVLInsertNode(tree, numbers[i]);
    return tree;
}

int main()
{
    int numbers[10] = {2, 1, 5, 3, 4, 6};
    AVLTree tree = AVLBuildTree(numbers, 6);
    AVLDeleteNode(tree, 5);
    printf("Hello World!\n");
}