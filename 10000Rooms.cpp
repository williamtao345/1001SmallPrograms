#include <stdio.h>
int open = 0;
int close = 0;
void open_or_close(char *rooms10000, int number_of_room)
{
    if (rooms10000[number_of_room] == 0)
    {
        rooms10000[number_of_room] = 1;
        open++;
    }
    else
    {
        rooms10000[number_of_room] = 0;
        close++;
    };
};

void calculate(char *rooms10000, int number_of_waiters)
{
    for (int i = 0; i < number_of_waiters; i++)
    {
        for (int j = i; j < 10000; j = j + i + 1)
        {
            open_or_close(rooms10000, j);
        };
    };
};

int main()
{
    char rooms10000[9999] = {0};
    int number_of_waiters = 0;
    printf("Input the number of the waiters:\n");
    scanf("%d", &number_of_waiters);
    calculate(rooms10000, number_of_waiters);
    int numbers_of_open_rooms = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (rooms10000[i] == 1)
        {
            numbers_of_open_rooms++;
        };
    };
    printf("The number of open rooms is %d\nOpened for %d times\nand closed for %d times!\n", numbers_of_open_rooms, open, close);
}