#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* char is_relatively_prime(unsigned long num1, unsigned long num2)
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
} */

/* void print_prime_numbers(long count)
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
} */

/* void print_prime_numbers_to_file(unsigned long count, char *fileName)
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
} */

typedef struct PNS_
{
    int *primeNumbers;
    int primeNumbersCount;
    int maxPrimeNumbersCount;
    int process; //next number to check
} PNSNode, *PNSPointer;

PNSPointer PNS_Create()
{
    PNSPointer PNS = (PNSPointer)calloc(1, sizeof(PNSNode));
    PNS->primeNumbers = (int *)calloc(100, sizeof(int));
    PNS->primeNumbersCount = 0;
    PNS->maxPrimeNumbersCount = 100;
    PNS->process = 2;
    return PNS;
}

void PNS_Free(PNSPointer PNS)
{
    free(PNS->primeNumbers);
    free(PNS);
}

void PNStorageCheck(PNSPointer PNS, int count)
{
    if ((PNS->primeNumbersCount + count) > PNS->maxPrimeNumbersCount)
    {
        int *primeNumbers_temp = (int *)calloc(PNS->maxPrimeNumbersCount + 100, sizeof(int));
        memcpy(primeNumbers_temp, PNS->primeNumbers, PNS->primeNumbersCount * sizeof(int));
        free(PNS->primeNumbers);
        PNS->primeNumbers = primeNumbers_temp;
        PNS->maxPrimeNumbersCount += 100;
    }
}

void PNS_Add(PNSPointer PNS, int number)
{
    PNS->primeNumbers[PNS->primeNumbersCount] = number;
    PNS->primeNumbersCount++;
}

void ProcessPNS(PNSPointer PNS, int count)
{
    PNStorageCheck(PNS, count);
    int i = 0;
    while(i<count)
    {
        int j = 0;
        int flag = 1;
        while (PNS->primeNumbers[j] != 0 && PNS->primeNumbers[j] < PNS->process)
        {
            if (PNS->process % PNS->primeNumbers[j] == 0)
            {
                flag = 0;
                break;
            }
            j++;
        }

        if (flag)
        {
            PNS_Add(PNS, PNS->process);
            i++;
        }
        PNS->process++;
    }
}

int main()
{
    PNSPointer PNS = PNS_Create();
    ProcessPNS(PNS, 2000);
    for (int i = 0; i < 2000; i++)
    {
        printf("%d\n", PNS->primeNumbers[i]);
    }
    PNS_Free(PNS);
}