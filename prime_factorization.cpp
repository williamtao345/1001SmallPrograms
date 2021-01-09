#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long PFType;

#define DEBUG
#define LEAST_PRINT_SECOND 0.1    //Set to 0 in order to print every number

char is_prime_number(PFType number)
{
    int flag = 2;
    for (PFType i = 2; i <= number / flag; i++)
    {
        if (number % i == 0)
            return 0;
        flag = i;
    }
    return 1;
}

PFType GetminPF(PFType number)
{
    for (PFType i = 2; i <= number / 2; i++)
    {
        if (number % i == 0)
            return i;
    }
    return number;
}
#define MAX_PFS_LENGTH 30

//Up to 30 prime numbers
typedef struct PrimeFactorization_
{
    PFType number;
    int primeNumberLength;
    PFType primeNumbers[MAX_PFS_LENGTH];
    int powers[MAX_PFS_LENGTH];
} PFS, *PFSNode;

PFSNode GetEmptyPFStorage()
{
    PFSNode PrimeFactorization = (PFSNode)calloc(1, sizeof(PFS));
    return PrimeFactorization;
}

//Return 0 if initialization is failed
char PFStorageInitializer(PFSNode PrimeFactorization)
{
    PrimeFactorization = (PFSNode)calloc(1, sizeof(PFS));

    if (PrimeFactorization == NULL)
        return 0;
    else
        return 1;
}

char PFS_Input(PFType primeNumber, PFSNode PFS)
{

#ifdef DEBUG
    // printf("%llu\n", primeNumber);
    if (!is_prime_number(primeNumber))
    {
        printf("PFS_Input error.");
        exit(0);
    }
#endif

    for (int i = 0; i < PFS->primeNumberLength; i++)
    {
        if (PFS->primeNumbers[i] == primeNumber)
        {
            PFS->powers[i]++;
            return 1;
        }
    }

    if (PFS->primeNumberLength >= MAX_PFS_LENGTH)
    {
        printf("PFS_Input too mcuh. Prime number: %llu\n", primeNumber);
        return 0;
    }

    PFS->primeNumbers[PFS->primeNumberLength] = primeNumber;
    PFS->powers[PFS->primeNumberLength]++;
    PFS->primeNumberLength++;
    return 1;
}

//Return the number devided by minimum prime factor
PFType PFS_InputMinPrimeFactor(PFType number, PFSNode PFS)
{
    PFType MinPF = GetminPF(number);
    PFS_Input(MinPF, PFS);
    return number / MinPF;
}

void PrintPFS(PFSNode PFS)
{
    printf("%llu = 1", PFS->number);
    for (int i = 0; i < PFS->primeNumberLength; i++)
    {
        if (PFS->powers[i] != 1)
            printf(" * %llu^%d", PFS->primeNumbers[i], PFS->powers[i]);
        else
            printf(" * %llu", PFS->primeNumbers[i]);
    }
    printf("\n");
}

PFSNode PrimeFactorization(PFType number)
{
    clock_t start = clock();
    PFSNode PFS = GetEmptyPFStorage();
    PFS->number = number;
    while (number != 1)
        number = PFS_InputMinPrimeFactor(number, PFS);
    double time = (double)(clock() - start) / CLOCKS_PER_SEC;
    if (time > LEAST_PRINT_SECOND)
    {
        PrintPFS(PFS);
        printf("Spent %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
        printf("--------------------------\n");
     }
    return PFS;
}

int main()
{
    PrimeFactorization(1334771190284846820);
}