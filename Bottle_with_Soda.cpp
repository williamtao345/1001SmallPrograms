#include <stdio.h>
#include <stdlib.h>

typedef long _DATATYPE_OF_BOTTLES_;

/* int change_bottles_to_sodas(int number_of_sodas, int number_of_bottles)
{
    if(number_of_bottles<3)
    {
        return number_of_sodas;
    };
    number_of_sodas += number_of_bottles / 3;
    number_of_bottles = number_of_bottles % 3 + number_of_sodas;
    return change_bottles_to_sodas(number_of_bottles,number_of_bottles);
} */

int main()
{
    while (1)
    {
        _DATATYPE_OF_BOTTLES_ number_of_bottles = 0;
        _DATATYPE_OF_BOTTLES_ number_of_sodas = 0;
        printf("Input the amount of bottles (Input 0 to exit): ");
        fflush(stdout);
        scanf("%ld", &number_of_bottles);
        if(number_of_bottles == 0)
        {
            exit(0);
        };
        _DATATYPE_OF_BOTTLES_ max_amount_of_sodas;
        _DATATYPE_OF_BOTTLES_ number_of_add_sodas = 0;
        while (number_of_bottles >= 3)
        {
            number_of_add_sodas = number_of_bottles / 3;
            number_of_sodas += number_of_add_sodas;
            number_of_bottles = number_of_bottles % 3 + number_of_add_sodas;
        }
        if(number_of_bottles == 2)
        {
            number_of_sodas++;
        }
        printf("The max amount of sodas is %ld\n", number_of_sodas);
    };
}