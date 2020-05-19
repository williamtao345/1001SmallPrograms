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
    printf("There are %ld rooms in the hotel.\n", room_numbers);
}

int main()
{
    printf("--------------------------------------------------------------------------------------\n");
    printf("This small program solves an interesting Math problem about opening and closing rooms.\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("Introduction:\n");
    printf("There are 10,000 rooms in the hotel, numbered from 1 to 10, 000. The first waiter opened all the doors of the rooms, the second waiter \" reversed \" all the rooms numbered multiple of 2, and the third waiter \" reversed \" all the rooms numbered multiple of 3... (1<-n<-10000) the waiters \" reversed \" all rooms numbered multiple of n.\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("\t---- Made by William Tao----\n");
    printf("--------------------------------------------------------------------------------------\n");
    char *rooms = (char *)calloc(ROOM_NUMBERS, sizeof(char));
    long number_of_waiters = 0;
    show_how_many_rooms();
    while (true)
    {
        printf("Input the number of the waiters (Input 0 to exit): ");
        fflush(stdout);
        scanf("%ld", &number_of_waiters);
        if (number_of_waiters == 0)
        {
            exit(0);
        }
        clock_t start_of_time = clock();
        calculate(rooms, number_of_waiters);
        long numbers_of_open_rooms = find_open_rooms(rooms);
        double time_of_calculating = calculate_time_sec(start_of_time);

        memset(rooms, 0, sizeof(char) * ROOM_NUMBERS);
        printf("The number of open rooms is %ld\nCalculating spends %12.6lf seconds\n",
               numbers_of_open_rooms, time_of_calculating);
        printf("------------------------------------------\n");
    }
}