#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void QuickSortHelpter(int *a, int left, int right)
{
    int i, j, temp;
    if (left > right)
        return;

    temp = a[left];
    i = left;
    j = right;
    while (i != j)
    {
        while (a[j] >= temp && i < j)
            j--;

        while (a[i] <= temp && i < j)
            i++;

        if (i < j)
        {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }


    //Test
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");


    a[left] = a[i];
    a[i] = temp;
    QuickSortHelpter(a, left, i - 1);
    QuickSortHelpter(a, i + 1, right);
}

int *QuickSort(int *str, int aLentgh)
{
    int *a = (int *)calloc(aLentgh, sizeof(int));
    memcpy(a, str, sizeof(int) * aLentgh);
    QuickSortHelpter(a, 0, aLentgh - 1);
    for (int i = 0; i < aLentgh; i++)
    {
        printf("%d ", a[i]);
    }
    return a;
}

int main()
{
    int a[10] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    QuickSort(a, 10);
}