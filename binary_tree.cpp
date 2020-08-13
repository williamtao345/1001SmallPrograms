#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>

int Search1(int *list, int length, int value)
{
    int *tmpList = (int *)calloc(length + 1, sizeof(int));
    return 0;
}

int Search2(int *list, int length, int value, int &p)
{
    int head = 0;
    int tail = length - 1;
    int mid;
    while (head <= tail)
    {
        mid = (tail + head) / 2;
        if (list[mid] == value)
        {
            p = mid;
            return mid;
        }
        else
        {
            (value < list[mid]) ? tail = mid - 1 : head = mid + 1;
        }
    }
    p = head;
    return -1;
}

typedef struct BSNode_
{
    int value;
    struct BSNode_ *leftNode, *rightNode;
} * BSTree, BSNode;

BSNode *BitSearth(BSTree BT, int value, BSNode *&father)
{
    father = NULL;
    while (BT != NULL)
    {
        if (BT->value == value)
        {
            return BT;
        }
        father = BT;
        (value < BT->value) ? BT = BT->leftNode : BT = BT->rightNode;
    }
    return NULL;
}

BSNode *BitSearth2(BSTree BT, int value, BSNode *&node)
{
    if (BT == NULL)
    {
        return NULL;
    }
    else if (value < BT->value)
    {
        node = BT;
        BT = BitSearth2(BT->leftNode, value, node);
    }
    else if (value > BT->value)
    {
        node = BT;
        BT = BitSearth2(BT->rightNode, value, node);
    }
    else
    {
        return BT;
    }
    return BT;
}

BSNode *BitAdd(BSTree &BT, int value)
{
    BSNode *p;
    BSNode *tmp;
    if ((p = BitSearth(BT, value, tmp)) == NULL)
    {
        BSNode *node;
        node = (BSNode *)calloc(1, sizeof(BSNode));
        node->value = value;
        node->leftNode = NULL;
        node->rightNode = NULL;
        if (tmp == NULL)
            BT = node;
        else if (value < tmp->value)
            tmp->leftNode = node;
        else
            tmp->rightNode = node;
        return node;
    }
    return p;
}

BSNode *BitMax(BSTree BT, BSNode *&father)
{
    if (BT == NULL)
    {
        father = NULL;
        return NULL;
    }
    if (BT->rightNode == NULL)
    {
        father = NULL;
        return BT;
    }
    father = BT;
    while (father->rightNode->rightNode != NULL)
    {
        father = father->rightNode;
    }
    BT = father->rightNode;
    return BT;
}

BSNode *BitMin(BSTree BT)
{
    while (BT->leftNode != NULL)
    {
        BT = BT->leftNode;
    }
    return BT;
}

int BitDelete(BSTree &BT, int value)
{
    BSNode *temp, *fatherDelete = NULL, *p = BT;
    if ((temp = BitSearth(p, value, fatherDelete)) == NULL)
        return 0;
    if (temp->leftNode != NULL && temp->rightNode != NULL)
    {
        BSNode *nF, *n = temp->leftNode;
        while (n->rightNode != NULL)
        {
            nF = n;
            n = n->rightNode;
        }
        temp->value = n->value;
        fatherDelete = nF;
        temp = n;
    }
    BSTree *f;
    (temp->value < fatherDelete->value) ? f = &fatherDelete->leftNode : f = &fatherDelete->rightNode;

    if (temp->leftNode)
        *f = temp->leftNode;
    else
        *f = temp->rightNode;
    free(temp);
    return 1;
}

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
        return 1;
    else if (GetAVLHeight(tree->leftNode) > GetAVLHeight(tree->rightNode))
        return tree->leftNode->height + 1;
    else
        return tree->rightNode->height + 1;
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

/* int GetLowestAVLNode(AVLTree tree, AVLNode *node)
{
    if(tree == NULL)
        return NULL;
    if(tree->leftNode == NULL && tree->rightNode == NULL)
        return 1;
    else if(GetLowestAVLNode(tree->leftNode, node) > GetLowestAVLNode(tree->leftNode, node))
        return 
} */
AVLNode *AVLRebalance(AVLTree &tree, int key)
{
    int balanceFactor = GetAVLHeight(tree);
    if (balanceFactor > 1 && key < tree->leftNode->value)
    {
        AVLRightRotation(tree);
    }
    else if (balanceFactor < -1 && key > tree->rightNode->value)
    {
        AVLLeftRotation(tree);
    }
    else if (balanceFactor > 1 && key > tree->leftNode->value)
    {
        AVLLeftRotation(tree->leftNode);
        AVLRightRotation(tree);
    }
    else if (balanceFactor < -1 && key < tree->rightNode->value)
    {
        AVLRightRotation(tree->rightNode);
        AVLLeftRotation(tree);
    }
    return tree;
}

AVLTree AddAVLNode(AVLTree tree, int value)
{
    AVLTree p = tree;
    if (p == NULL)
    {
        AVLNode *addNode;
        addNode = (AVLNode *)calloc(1, sizeof(AVLNode));
        addNode->value = value;
        addNode->leftNode = NULL;
        addNode->rightNode = NULL;
        addNode->height = GetAVLHeight(p);
        return addNode;
    }
    else if (value < p->value)
    {
        p->leftNode = AddAVLNode(p->leftNode, value);
        p->height = GetAVLHeight(p);
        if (GetAVLHeight(p->leftNode) - GetAVLHeight(p->rightNode) > 1)
        {
        }
    }
    else if (value > p->value)
    {
        p->rightNode = AddAVLNode(p->rightNode, value);
        p->height = GetAVLHeight(p);
        if (GetAVLHeight(p->rightNode) - GetAVLHeight(p->leftNode) > 1)
        {
        }
    }
    return p;
}

int main()
{
    printf("Hello World!\n");
}