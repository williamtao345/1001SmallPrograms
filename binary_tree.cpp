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
    (deleteNode->leftNode) ? *f = deleteNode->leftNode : *f = deleteNode->rightNode;

    free(deleteNode);
    AVLRebalance(tree);
    return 1;
};

//Build AVL Tree with array;
AVLTree AVLBuildTree(int *numbers, int length)
{
    AVLTree tree = NULL;
    for (int i = 0; i < length; i++)
        AVLInsertNode(tree, numbers[i]);
    return tree;
}

/*---------------------------------------------------------------------------------*/
#define TEST
int BTree_m = 5;
typedef unsigned int BTreeKeyType;
typedef struct BTree_
{
    int n;
    struct node *parent;
    BTreeKeyType *key;   //key[BTree_m - 1]
    struct BTree_ **ptr; //*ptr[BTree_m+1]
    /*int **recptr;*/    //recptr[BTree_m + 1]
} BTNode, *BTree;

int InitBTNode(BTree &T)
{
    if (T == NULL)
        T = (BTree)calloc(1, sizeof(BTNode));
    free(T->key);
    free(T->ptr);
    T->n = 0;
    T->key = (BTreeKeyType *)calloc(BTree_m + 1, sizeof(BTreeKeyType));
    T->ptr = (BTree_ **)calloc(BTree_m + 2, sizeof(BTree_));

    if (!T->key || !T->ptr)
        return 0;

    return 1;
}

struct BTreeSearch_r
{
    BTNode *r;
    int i, tag;
};

#ifdef TEST

void PrintKeyArray(unsigned int *numbers, int length)
{
    printf(" ");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

void PrintPtrArray(BTNode **ptr, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (ptr[i] == NULL)
            printf("0 ");
        else
            printf("1 ");
    }
    printf("\n");
}

void PrintBTNode(BTNode *t)
{
    printf("key: ");
    PrintKeyArray(t->key, BTree_m + 1);
    printf("ptr: ");
    PrintPtrArray(t->ptr, BTree_m + 2);
}
#endif

BTreeSearch_r BTSearch_a(BTree T, BTreeKeyType x)
{
    int i = 0;

    BTreeSearch_r rst;
    BTNode *p = T, *q = NULL;
    while (p != NULL)
    {
        for (i = 0; x > p->key[i] && i < p->n; i++)
            ;

        if (p->key[i] == x)
        {
            rst.r = p;
            rst.i = i + 1;
            rst.tag = 1;
            return rst;
        }

        q = p;
        p = p->ptr[i];
    }
    rst.r = q;
    rst.i = i;
    rst.tag = 0;
    return rst;
}

int RebalanceBTNode(BTNode *&T, BTNode *f)
{
    int ifRoot = 0;
    if (T->n <= BTree_m)
        return ifRoot;

    BTNode *left = T;
    if (f == NULL)
    {
        InitBTNode(f);
        T = f;
        ifRoot = 1;
    }
    //Seperate node;
    BTreeKeyType middle = left->key[BTree_m / 2 + 1];
    left->key[BTree_m / 2 + 1] = NULL;
    left->n--;

#ifdef TEST
    PrintKeyArray(left->key, BTree_m + 1);
#endif

    BTNode *right = NULL;
    InitBTNode(right);
    int q;
    for (q = 0; q < BTree_m / 2; q++)
    {
        right->key[q] = left->key[q + BTree_m / 2 + 2];
        left->key[q + BTree_m / 2 + 2] = NULL;
        right->ptr[q] = left->ptr[q + BTree_m / 2 + 2];
        left->ptr[q + BTree_m / 2 + 2] = NULL;
        left->n--;
        right->n++;

#ifdef TEST_
        printf("L->key: ");
        PrintKeyArray(left->key, BTree_m + 1);
        printf("L->ptr: ");
        PrintPtrArray(left->ptr, BTree_m + 2);
        printf("R->key: ");
        PrintKeyArray(right->key, BTree_m + 1);
        printf("R->ptr: ");
        PrintPtrArray(right->ptr, BTree_m + 2);
#endif
    }
    right->ptr[q] = left->ptr[q + BTree_m / 2 + 2];
    left->ptr[q + BTree_m / 2 + 2] = NULL;

    left->ptr[left->n + 1] = f;
    right->ptr[right->n + 1] = f;

#ifdef TEST
    printf("L->key: ");
    PrintKeyArray(left->key, BTree_m + 1);
    printf("L->ptr: ");
    PrintPtrArray(left->ptr, BTree_m + 2);
    printf("R->key: ");
    PrintKeyArray(right->key, BTree_m + 1);
    printf("R->ptr: ");
    PrintPtrArray(right->ptr, BTree_m + 2);
#endif

    //Creat father node;
    int i;
    BTNode *fatherF = f->ptr[f->n + 1];

    for (i = 0; middle > f->key[i] && i < f->n; i++)
        ;

#ifdef TEST
    printf("\n");
#endif

    for (int j = BTree_m; j > i; j--)
    {
        f->key[j] = f->key[j - 1];
        f->ptr[j + 1] = f->ptr[j];
    }
    f->key[i] = middle;
    f->ptr[i] = left;
    f->ptr[i + 1] = right;
    f->n++;

#ifdef TEST
    printf("f->key: ");
    PrintKeyArray(f->key, BTree_m + 1);
    printf("f->ptr: ");
    PrintPtrArray(f->ptr, BTree_m + 2);
#endif

    RebalanceBTNode(f, fatherF);
    return ifRoot;
}

int BTInsert(BTree &T, BTreeKeyType x)
{
    if (T == NULL)
        InitBTNode(T);
    BTreeSearch_r r = BTSearch_a(T, x);
    if (r.tag == 1)
        return 0;
    BTNode *f = r.r->ptr[r.r->n + 2];
    for (int j = r.r->n; j >= r.i; j--)
    {
        r.r->key[j + 1] = r.r->key[j];
        r.r->ptr[j + 2] = r.r->ptr[j + 1];
    }

    r.r->key[r.i] = x;
    r.r->n++;
    PrintBTNode(r.r);
    if (RebalanceBTNode(r.r, f) == 1)
    {
        T = r.r;
    }

    return 1;
}

void BTInsertArray(BTree &tree, int *x, int length)
{
    for (int i = 0; i < length; i++)
    {
        BTInsert(tree, x[i]);
    }
}

/*---------------------------------------------------------------------------------*/

int main()
{
    BTree tree = NULL;
    int x[20] = {1, 2, 4, 3, 5, 6, 10, 9, 8, 7, 15, 14, 13, 12, 11, 20, 19, 18, 17, 16};
    BTInsertArray(tree, x, 20);
    tree = tree->ptr[1];
}