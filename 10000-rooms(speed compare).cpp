#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ROOM_NUMBERS 100000000L

void calculate(char *rooms, long number_of_waiters)
{
    for (long i = 0; i < number_of_waiters; i++)
    {
        for (long j = i; j < ROOM_NUMBERS; j = j + i + 1)
        {
            rooms[j] = !rooms[j];
        };
    };
};

void calculate_by_tzs(char *rooms, long number_of_waiters)
{
    for (long i = 0; i < number_of_waiters; i++)
    {
        for (long j = i; j < ROOM_NUMBERS; j = j + i + 1)
        {
            if ((j + 1) % (i + 1) == 0)
            {
                rooms[j] =rooms[j];
            }
        };
    };
};

long find_open_rooms(char *rooms)
{
    long numbers_of_open_rooms = 0;
    for (long i = 0; i < ROOM_NUMBERS; i++)
    {
        numbers_of_open_rooms += rooms[i];
    };
    return numbers_of_open_rooms;
};

double calculate_time_sec(clock_t start_of_time)
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
    char *rooms = (char *)calloc(ROOM_NUMBERS, sizeof(char));
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
        calculate(rooms, number_of_waiters);
        long numbers_of_open_rooms = find_open_rooms(rooms);
        double time_by_txf = calculate_time_sec(start_of_time);
        memset(rooms, 0, sizeof(char) * ROOM_NUMBERS);

        //------------------------------Calculator by tzs------------------------------
        start_of_time = clock();
        calculate_by_tzs(rooms, number_of_waiters);
        find_open_rooms(rooms);
        double time_by_tzs = calculate_time_sec(start_of_time);
        //-----------------------------------------------------------------------------

        memset(rooms, 0, sizeof(char) * ROOM_NUMBERS);
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