#include <stdio.h>

int main()

{

    int data[101] = {0, 2, 3, 5, 8, 9, 10, 18, 26, 32}, right[101];
    int i, n, t, len;

    n = 9;
    len = 9 + 1;

    //initialize

    right[0] = 1; //head

    for (i = 1; i <= n; i++)
    {
        if (i != n)
            right[i] = i + 1;
        else
            right[i] = 0;
    }

    data[len] = 6; //won't work with number less than 2 or greater than 32
    right[len] = 0;

    t = 0;
    while (true)
    {
        if (right[t] == 0)
        {
            right[t] = len;
            break;
        }

        if (data[right[t]] > data[len])
        {
            right[len] = right[t];
            right[t] = len;
            break;
        }

        t = right[t];
    }

    t = right[0];

    while (t != 0)
    {
        printf("%d ", data[t]);
        t = right[t];
    }
    printf("\n");
}