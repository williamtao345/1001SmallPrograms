#include <stdio.h>
#include <stdlib.h>
// #define TEST
int BTree_m = 5;
typedef unsigned int BTreeKeyType;
typedef struct BTree_
{
    int n;
    struct node *parent;
    BTreeKeyType *key;   //key[BTree_m + 1]
    struct BTree_ **ptr; //*ptr[BTree_m + 2]
    /*int **recptr;*/    //recptr[BTree_m + 2]
} BTNode, *BTree;

int InitBTNode(BTree &T)
{
    if (T == NULL)
        T = (BTree)calloc(1, sizeof(BTNode));
    else
    {
        free(T->key);
        free(T->ptr);
    }

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
    {
        T->ptr[T->n + 1] = f;
        return ifRoot;
    }

    BTNode *left = T;
    if (f == NULL)
    {
        InitBTNode(f);
        T = f;
        ifRoot = 1;
    }

    //Seperate node;
    BTreeKeyType middle = left->key[(BTree_m + 1) / 2];
    left->key[(BTree_m + 1) / 2] = NULL;
    left->n--;

    BTNode *right = NULL;
    InitBTNode(right);
    int q;
    for (q = 0; q < BTree_m / 2; q++)
    {
        right->key[q] = left->key[q + (BTree_m + 1) / 2 + 1];
        left->key[q + (BTree_m + 1) / 2 + 1] = NULL;
        right->ptr[q] = left->ptr[q + (BTree_m + 1) / 2 + 1];
        left->ptr[q + (BTree_m + 1) / 2 + 1] = NULL;
        left->n--;
        right->n++;
    }
    right->ptr[q] = left->ptr[q + (BTree_m + 1) / 2 + 2];
    left->ptr[q + (BTree_m + 1) / 2 + 2] = NULL;

    left->ptr[left->n + 1] = f;
    right->ptr[right->n + 1] = f;

    //Creat father node;
    int i;
    BTNode *fatherF = f->ptr[f->n + 1];

    for (i = 0; middle > f->key[i] && i < f->n; i++)
        ;

    for (int j = BTree_m; j > i; j--)
    {
        f->key[j] = f->key[j - 1];
        f->ptr[j + 1] = f->ptr[j];
    }
    f->key[i] = middle;
    f->ptr[i] = left;
    f->ptr[i + 1] = right;
    f->n++;

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
    BTNode *f = r.r->ptr[r.r->n + 1];
    r.r->ptr[r.r->n + 1] = NULL;
    for (int j = r.r->n; j > r.i; j--)
    {
        r.r->key[j] = r.r->key[j - 1];
        r.r->ptr[j + 1] = r.r->ptr[j];
    }
    r.r->key[r.i] = x;
    r.r->n++;

    if (RebalanceBTNode(r.r, f) == 1)
        T = r.r;
    return 1;
}

void BTInsertArray(BTree &tree, int *x, int length)
{
    for (int i = 0; i < length; i++)
        BTInsert(tree, x[i]);
}
/*---------------------------------------------------------------------------------*/

int main()
{
    // BTree_m = 4;
    BTree tree = NULL;
    int x[20] = {1, 2, 4, 3, 5, 6, 10, 9, 8, 7, 15, 14, 13, 12, 11, 20, 19, 18, 17, 16};
    BTInsertArray(tree, x, 20);
    tree = tree->ptr[1];
}