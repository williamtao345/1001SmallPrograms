#include <stdio.h>
#include <stdlib.h>

char GetKey()
{
    char input;
    system("stty -icanon");
    input = getchar();
    if (input == '\033')
    {
        input = getchar();
        if (input == '[')
        {
            input = getchar();
        }
    }
    system("stty icanon");
    printf("\r\033[k");
    return input;
}

void ShowPage1()
{
    printf("\x1b[H\x1b[2J");
    printf("Here is 1; <-\n");
    printf("Here is 2;\n");
}

void ShowPage2()
{
    printf("\x1b[H\x1b[2J");
    printf("Here is 1;\n");
    printf("Here is 2; <-\n");
}

int VisualPage()
{
    ShowPage1();
    char input = GetKey();
    char choice = 1;
    while (input != 'y')
    {
        switch (input)
        {
        case 'A':
            ShowPage1();
            choice = 1;
            break;
        case 'B':
            ShowPage2();
            choice = 0;
            break;
        case '\n':
            printf("\x1b[H\x1b[2J");
            return choice;
        default:
            switch (choice)
            {
            case 1:
                ShowPage1();
                break;
            case 0:
                ShowPage2();
                break;
            }
            break;
        }
        input = GetKey();
    }
    printf("\x1b[H\x1b[2J");
    return EOF;
}

int main()
{
    int a = VisualPage();
    printf("%d\n", a);
}