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
    printf("--------------------------------------------------------------------------------------\n");
    printf("This small program solves an interesting Math problem about change sodas from bottles.\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("Introduction:\n");
    printf("You can get a bottle of soda with 3 bottles.If you have 2 bottles you can get one by rent a bottle from someone and get a soda with 3 bottles. After drinking the soda, you will get a botlle to give it back to the person who you borrowed from. By inputing the number of bottles, this small program can calculate the max number of the sodas you can get with these bottles.\n");
    printf("\t---- Made by William Tao----\n");
    printf("--------------------------------------------------------------------------------------\n");
    while (true)
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