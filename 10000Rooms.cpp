#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ROOM_NUMBERS 100000000L

long open = 0;
long close = 0;

void calculate(char *rooms10000, long number_of_waiters)
{
    for (long i = 0; i < number_of_waiters; i++)
    {
        for (long j = i; j < ROOM_NUMBERS; j = j + i + 1)
        {
            rooms10000[j] = !rooms10000[j];
        };
    };
};

int find_open_rooms(char *rooms10000)
{
    int numbers_of_open_rooms = 0;
    for (long i = 0; i < ROOM_NUMBERS; i++)
    {
        if (rooms10000[i] == 1)
        {
            numbers_of_open_rooms++;
        };
    };
    return numbers_of_open_rooms;
};

double calculate_time(clock_t start_of_time)
{
    return (clock() - start_of_time) * 1.0 / CLOCKS_PER_SEC;
}

int main()
{
    char *rooms10000 = (char *)calloc(ROOM_NUMBERS, sizeof(char));
    long number_of_waiters = 0;

    while (true)
    {
        printf("Input the number of the waiters:\n");
        scanf("%ld", &number_of_waiters);
        clock_t start_of_time = clock();
        calculate(rooms10000, number_of_waiters);
        long numbers_of_open_rooms = find_open_rooms(rooms10000);
        double time_of_calculating = calculate_time(start_of_time);

        for (int i = 0; i < ROOM_NUMBERS; i++)
        {
            rooms10000[i] = 0;
        };

        memset(rooms10000, 0, sizeof(char));

        printf("The number of open rooms is %ld\nCalculating spends %12.6lf seconds\n",
               numbers_of_open_rooms, time_of_calculating);
        printf("------------------------------------------\n");
    }
}