#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

void calculate_by_tzs(char *rooms10000, long number_of_waiters)
{
    for (long i = 0; i < number_of_waiters; i++)
    {
        for (long j = i; j < ROOM_NUMBERS; j = j + i + 1)
        {
            if ((j + 1) % (i + 1) == 0)
            {
                rooms10000[j] = !rooms10000[j];
            }
        };
    };
};

int main()
{
    while (1)
    {
        char *rooms10000 = (char *)calloc(ROOM_NUMBERS, sizeof(char));
        long number_of_waiters = 0;

        printf("Input the number of the waiters:\n");
        scanf("%ld", &number_of_waiters);
        clock_t start_of_time = clock();
        calculate(rooms10000, number_of_waiters);
        long numbers_of_open_rooms = 0;
        for (long i = 0; i < ROOM_NUMBERS; i++)
        {
            if (rooms10000[i] == 1)
            {
                numbers_of_open_rooms++;
            };
        };
        double time_by_txf = (clock() - start_of_time) * 1.0 / CLOCKS_PER_SEC;
        free(rooms10000);

        rooms10000 = (char *)calloc(ROOM_NUMBERS, sizeof(char));
        start_of_time = clock();
        calculate_by_tzs(rooms10000, number_of_waiters);
        int numbers_of_open_rooms_by_tzs = 0;
        for (long i = 0; i < ROOM_NUMBERS; i++)
        {
            if (rooms10000[i] == 1)
            {
                numbers_of_open_rooms_by_tzs++;
            };
        };
        double time_by_tzs = (clock() - start_of_time) * 1.0 / CLOCKS_PER_SEC;

        printf("The number of open rooms is %ld\nCalculator by txf spends %12.6lf seconds\nCalculator by tzs spends %12.6lf seconds\n%8.6lf%% faster!\n",
               numbers_of_open_rooms, time_by_txf, time_by_tzs, (time_by_tzs - time_by_txf) / time_by_tzs * 100);
        printf("---------------------------------------\n");
    }
}