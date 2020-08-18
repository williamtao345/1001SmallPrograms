#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>

/* int Search1(int *list, int length, int value)
{
    int *tmpList = (int *)calloc(length + 1, sizeof(int));
    return 0;
} */

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

int BitDelete2(BSTree &BT, int value)
{
    BSNode *deleteNode, *fatherDelete = NULL, *p = BT;
    if ((deleteNode = BitSearth(p, value, fatherDelete)) == NULL)
        return 0;
    if (deleteNode->leftNode != NULL)
    {
        BSNode *nF = deleteNode, *n = deleteNode->leftNode;
        while (n->rightNode != NULL)
        {
            nF = n;
            n = n->rightNode;
        }
        deleteNode->value = n->value;
        deleteNode = n;
        fatherDelete = nF;
    }
    BSNode **f;
    (deleteNode->value < fatherDelete->value) ? f = &fatherDelete->leftNode : f = &fatherDelete->rightNode;

    if (deleteNode->leftNode)
        *f = deleteNode->leftNode;
    else
        *f = deleteNode->rightNode;
    free(deleteNode);
    return 1;
    /* if (deleteNode->leftNode == NULL)
    {
        if (deleteNode->value < fatherDelete->value)
            fatherDelete->leftNode = deleteNode->rightNode;
        else
            fatherDelete->rightNode = deleteNode->rightNode;
        free(deleteNode);
        return 1;
    }
    else
    {
        BSNode *nF = deleteNode, *n = deleteNode->leftNode;
        while (n->rightNode != NULL)
        {
            nF = n;
            n = n->rightNode;
        }

        deleteNode->value = n->value;
        if()
    } */
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

/* int GetLowestAVLNode(AVLTree tree, AVLNode *node)
{
    if(tree == NULL)
        return NULL;
    if(tree->leftNode == NULL && tree->rightNode == NULL)
        return 1;
    else if(GetLowestAVLNode(tree->leftNode, node) > GetLowestAVLNode(tree->leftNode, node))
        return 
} */

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

/* AVLNode *AVLRebalance(AVLTree &tree, int key)
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
} */

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
    int numbers[10] = {3, 2, 6, 5, 4, 7};
    AVLTree tree = AVLBuildTree(numbers, 6);
    AVLDeleteNode(tree, 3);
    printf("Hello World!\n");
}