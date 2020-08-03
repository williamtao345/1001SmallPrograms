#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CountZeroInInt(int number)
{
    int count = 0;
    while (number != 0xffffffff)
    {
        number = number | (number + 1);
        count++;
    }
    return count;
}

int CountOneInInt(int number)
{
    int count = 0;
    while (number != 0)
    {
        number = number & (number - 1);
        count++;
    }
    return count;
}

int Add(int x, int y)
{
    int tmp;
    do
    {
        tmp = x;
        x = x ^ y;
        y = (tmp & y) << 1;
    } while (y != 0);

    return x;
}

int main()
{
    int x = 450;
    int y = 220;
    printf("%d\n", CountOneInInt(999));
    printf("%d\n", CountZeroInInt(999));
    printf("%d\n", Add(x, y));
}