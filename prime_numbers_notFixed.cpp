#include<stdio.h>
#include<time.h>

char is_relatively_prime(unsigned long num1, unsigned long num2)
{
    
    if (num2 > num1)
    {
        num1 = num1 ^ num2;
        num2 = num1 ^ num2;
        num1 = num1 ^ num2;
    }
    long temp = num2;
    num2 = num1 % num2;
    while (num2 != 0)
    {
        num1 = temp;
        temp = num2;
        num2 = num1 % num2;
    }
    if(temp == 1)
        return 1;
    else
        return 0;
}

void print_prime_numbers(long count)
{
    unsigned long x = 1;
    clock_t start = clock();
    unsigned long i = 2;
    while (count != 0)
    {
        if (is_relatively_prime(i, x))
        {
            printf("%ld \ttime: %f\n", i, (double)(clock() - start)/ CLOCKS_PER_SEC);
            x *= i;
            count--;
            start = clock();
        }
        i++;
    }
}

void print_prime_numbers_to_file(unsigned long count, char *fileName)
{
    FILE *file = fopen(fileName, "w");
    unsigned long x = 1;
    clock_t start = clock();
    unsigned long i = 2;
    while (count != 0)
    {
        if (is_relatively_prime(i, x))
        {
            fprintf(file, "%ld \ttime: %f\n", i, (double)(clock() - start) / CLOCKS_PER_SEC);
            x *= i;
            count--;
            start = clock();
        }
        i++;
    }
}

int main()
{
    char fileName[30] = "prime_numbers";
    print_prime_numbers(50);
}