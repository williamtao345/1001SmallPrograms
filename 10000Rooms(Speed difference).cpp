#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ROOM_NUMBERS 10000000L

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

void show_how_many_rooms()
{
    long room_numbers = ROOM_NUMBERS;
    printf("%ld rooms in the hotel.\n", room_numbers);
}

int main()
{
    char *rooms10000 = (char *)calloc(ROOM_NUMBERS, sizeof(char));
    long number_of_waiters = 0;
    char if_calculate_from_1_without_showing_details;
    show_how_many_rooms();
    printf("Calculate from 1 without showing details(y or n)?");
    scanf("%c", &if_calculate_from_1_without_showing_details);
    while (true)
    {
        if (if_calculate_from_1_without_showing_details == 'n')
        {
            printf("Input the number of the waiters:\n");
            scanf("%ld", &number_of_waiters);
        }
        else
        {
            number_of_waiters++;
            printf("Inputting %ld\t", number_of_waiters);
            fflush(stdout);
        };

        clock_t start_of_time = clock();
        calculate(rooms10000, number_of_waiters);
        long numbers_of_open_rooms = find_open_rooms(rooms10000);
        double time_by_txf = calculate_time(start_of_time);

        for (int i = 0; i < ROOM_NUMBERS; i++)
        {
            rooms10000[i] = 0;
        };
        //------------------------------Calculator by tzs------------------------------
        start_of_time = clock();
        calculate_by_tzs(rooms10000, number_of_waiters);
        find_open_rooms(rooms10000);
        double time_by_tzs = calculate_time(start_of_time);
        //-----------------------------------------------------------------------------

        memset(rooms10000, 0, sizeof(char));
        if (if_calculate_from_1_without_showing_details == 'n')
        {
            printf("The number of open rooms is %ld\nCalculator by txf spends %12.6lf seconds\nCalculator by tzs spends %12.6lf seconds\n%8.6lf%% faster!\n",
                   numbers_of_open_rooms, time_by_txf, time_by_tzs, (time_by_tzs - time_by_txf) / time_by_tzs * 100);
            printf("---------------------------------------\n");
        }
        else
        {
            printf("%8.6lf%% faster!\n", (time_by_tzs - time_by_txf) / time_by_tzs * 100);
        }
    }
}