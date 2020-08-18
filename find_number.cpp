#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand((unsigned)time(NULL));
    int num = rand() % 100;
    int ans;
    for (int i = 0; i < 8; i++)
    {
        printf("--%d times left--\n", 8 - i);
        printf("Input Number: ");
        fflush(stdout);
        scanf("%d", &ans);
        printf("\x1b[H\x1b[2J");
        if (ans < num)
        {
            printf("%d is too small;\n", ans);
            printf("----------------\n");
        }
        else if (ans > num)
        {
            printf("%d is too large;\n", ans);
            printf("----------------\n");
        }
        else
        {
            printf("GREAT JOB!\n");
            exit(1);
        }
    }
    printf("\x1b[H\x1b[2J");
    printf("You failed :(\n");
}