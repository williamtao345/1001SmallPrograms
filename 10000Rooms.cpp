#include <stdio.h>
int changes = 0;
void open_or_close(char *rooms1000, int number_of_room)
{
    if (rooms1000[number_of_room] == 0)
    {
        rooms1000[number_of_room] = 1;
        changes++;
    }
    else
    {
        rooms1000[number_of_room] = 0;
    };
};

void calculate(char *rooms1000, int number_of_waiters)
{
    for (int i = 0; i < number_of_waiters; i++)
    {
        for (int j = i; j < 10000; j = j + i + 1)
        {
            open_or_close(rooms1000, j);
        };
    };
};

int main()
{
    char rooms1000[9999] = {0};
    int number_of_waiters = 0;
    printf("Input the number of the waiters:\n");
    scanf("%d", &number_of_waiters);
    calculate(rooms1000, number_of_waiters);
    int numbers_of_open_rooms = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (rooms1000[i] == 1)
        {
            numbers_of_open_rooms++;
        };
    };
    printf("The number of open rooms is %d\nOpened for %d times!\n", numbers_of_open_rooms, changes);
}