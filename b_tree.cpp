#include <stdio.h>
#include <stdlib.h>
// #define TEST
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

int PrintBTNode(BTNode *t)
{
    if (t == NULL)
    {
        printf("----NULL----\n");
        return 0;
    }
    printf("key: ");
    PrintKeyArray(t->key, BTree_m + 1);
    printf("ptr: ");
    PrintPtrArray(t->ptr, BTree_m + 2);
    return 1;
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
            printf("%d ", p->key[i]);
        printf("\n");
        if (p->key[i] == x)
        {
            rst.r = p;
            rst.i = i + 1;
            rst.tag = 1;
            return rst;
        }
#ifdef TEST
        printf("-------------------\n");
        PrintBTNode(p);
#endif
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
    printf("\n");
#endif

    //Creat father node;
    int i;
    BTNode *fatherF = f->ptr[f->n + 1];
#ifdef TEST
    printf("---------Before Insert father node---------\n");
    printf("f->key: ");
    PrintKeyArray(f->key, BTree_m + 1);
    printf("f->ptr: ");
    PrintPtrArray(f->ptr, BTree_m + 2);
    printf("--------------------------------------------\n");
#endif
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

#ifdef TEST
    printf("f->key: ");
    PrintKeyArray(f->key, BTree_m + 1);
    printf("f->ptr: ");
    PrintPtrArray(f->ptr, BTree_m + 2);
    printf("================\n");
    printf("L->f: \n");
    PrintBTNode(left->ptr[left->n + 1]);
    printf("================\n");
    printf("R->f: \n");
    PrintBTNode(right->ptr[right->n + 1]);
    printf("\n");
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
    {
        T = r.r;
    }
#ifdef TEST
    printf("r.r=============\n");
    PrintBTNode(r.r);
    PrintBTNode(r.r->ptr[r.r->n]);
    printf("r.r father======\n");
    PrintBTNode(r.r->ptr[r.r->n + 1]);
    printf("================\n");
#endif
    return 1;
}

void BTInsertArray(BTree &tree, int *x, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("\x1b[H\x1b[2J");
        printf("****************\n");
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