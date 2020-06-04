#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// #define CALCULATE_FACTORIAL

typedef long long TYPE_OF_WASTE_SPACE;
typedef long long TYPE_OF_TOTAL_SUM;

TYPE_OF_TOTAL_SUM GetTotalSum(int *nString, int nStringLength)
{
    TYPE_OF_TOTAL_SUM sum = 0;
    for (int i = 0; i < nStringLength; i++)
    {
        sum += nString[i];
    }
    return sum;
}

void GetnStringFromFile(int *nString, FILE *file, int nStringLength)
{
    for (int i = 0; i < nStringLength; i++)
    {
        fscanf(file, "%d", &nString[i]);
    }
}

int GetStringLength(FILE *file)
{
    int x = 0;
    fscanf(file, "%d", &x);
    return x;
};

int GetChangingTimes(FILE *file)
{
    int x = 0;
    fscanf(file, "%d", &x);
    return x;
};

int FindMaxNumberInGroup(int *nString, int headNumber, int tailNumber)
{
    int maxNumber = 0;
    for (int i = headNumber; i <= tailNumber; i++)
    {
        if (nString[i] > maxNumber)
        {
            maxNumber = nString[i];
        }
    }
    return maxNumber;
}

TYPE_OF_WASTE_SPACE GetTotalSumWithWasteSpace(int *nString, int *numbersOfEachGroupsNumbers, int groupNumber)
{
    TYPE_OF_WASTE_SPACE sum = 0;
    int headNumber = 0;
    int tailNumber = numbersOfEachGroupsNumbers[0] - 1;
    int maxNumberInGroup;
    for (int i = 0; i < (groupNumber); i++)
    {
        maxNumberInGroup = (FindMaxNumberInGroup(nString, headNumber, tailNumber));
        headNumber += numbersOfEachGroupsNumbers[i];
        tailNumber += numbersOfEachGroupsNumbers[i + 1];
        sum += maxNumberInGroup * numbersOfEachGroupsNumbers[i];
    }
    return sum;
}

TYPE_OF_WASTE_SPACE TotalSumWithWasteSpace;

#ifndef CALCULATE_FACTORIAL
void PrintNumberWays(int *numbers, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", numbers[i]);
    };
    printf("%lld", TotalSumWithWasteSpace);
    printf("\r\033[k");
}
#endif

#ifdef CALCULATE_FACTORIAL
long long processNum = 0;
long long CalculateFactorial(int num)
{
    long long total = 1;
    for (int i = 2; i <= num; i++)
    {
        total *= i;
    }
    return total;
}
long long CalculateTotalProcessNum(int nStringLength, int groupNumber)
{
    return CalculateFactorial(nStringLength - 1) / (CalculateFactorial(groupNumber - 1) * CalculateFactorial(nStringLength - (groupNumber - 1)));
}
void *PrintProcess(void *arg)
{
    long long totalProcessNum = *(long long *)arg;
    printf("Process is %lld\n", totalProcessNum);
    while (1)
    {
        printf("Calculating: %lld%%", processNum / totalProcessNum);
        sleep(2);
        printf("\r\033[k");
    }
}
#endif

int forFunction(int *nString, int nStringLength, int *numbersOfEachGroupsNumbers, int groupNumber, int digit, int totalSum)
{
    if (digit == 1)
    {
        numbersOfEachGroupsNumbers[groupNumber - digit] = nStringLength - totalSum;
#ifdef CALCULATE_FACTORIAL
        processNum++;
#else
        PrintNumberWays(numbersOfEachGroupsNumbers, groupNumber);
#endif
        TYPE_OF_WASTE_SPACE x = GetTotalSumWithWasteSpace(nString, numbersOfEachGroupsNumbers, groupNumber);
        if (x > TotalSumWithWasteSpace)
        {
            ;
        }
        else if (x < TotalSumWithWasteSpace)
        {
            TotalSumWithWasteSpace = x;
        }
    }
    else
    {
        int i = 1;
        while (1)
        {
            if ((nStringLength - totalSum - i) < (digit - 1))
            {
                break;
            }
            numbersOfEachGroupsNumbers[groupNumber - digit] = i;
            forFunction(nString, nStringLength, numbersOfEachGroupsNumbers, groupNumber, digit - 1, totalSum + i);
            i++;
        };
    };

    return 1;
}

int forFunctionFirstTime(int *nString, int nStringLength, int *numbersOfEachGroupsNumbers, int groupNumber, int digit, int totalSum)
{
    if (digit == 1)
    {
        numbersOfEachGroupsNumbers[groupNumber - digit] = nStringLength - totalSum;
#ifdef CALCULATE_FACTORIAL
        processNum++;
#else
        PrintNumberWays(numbersOfEachGroupsNumbers, groupNumber);
#endif
        TYPE_OF_WASTE_SPACE x = GetTotalSumWithWasteSpace(nString, numbersOfEachGroupsNumbers, groupNumber);
        TotalSumWithWasteSpace = x;
    }
    else
    {
        numbersOfEachGroupsNumbers[groupNumber - digit] = 1;
        forFunction(nString, nStringLength, numbersOfEachGroupsNumbers, groupNumber, digit - 1, totalSum + 1);
    };
    return 1;
}

void FormLeastWasteSpace(int *nString, int nStringLength, int groupNumber, TYPE_OF_TOTAL_SUM stringSum)
{
    int *numbersOfEachGroupsNumbers = (int *)calloc(groupNumber, sizeof(int));
    forFunctionFirstTime(nString, nStringLength, numbersOfEachGroupsNumbers, groupNumber, groupNumber, 0);
    forFunction(nString, nStringLength, numbersOfEachGroupsNumbers, groupNumber, groupNumber, 0);
}

int main()
{
    printf("--------------------\n");
    FILE *file = fopen("/Users/william/Downloads/snakes_gold_open19/3.in", "r");
    int nStringLength = GetStringLength(file);
    int groupNumber = GetChangingTimes(file) + 1;
    int *nString;
    nString = (int *)calloc(nStringLength, sizeof(int));
    GetnStringFromFile(nString, file, nStringLength);
    TYPE_OF_TOTAL_SUM stringSum = GetTotalSum(nString, nStringLength);

#ifdef CALCULATE_FACTORIAL
    pthread_t calculateProcess;
    long long totalProcessNum = CalculateTotalProcessNum(nStringLength, groupNumber);
    pthread_create(&calculateProcess, NULL, PrintProcess, &totalProcessNum);
#endif

    FormLeastWasteSpace(nString, nStringLength, groupNumber, stringSum);
    printf("%lld - %lld = %lld\n", TotalSumWithWasteSpace, stringSum, TotalSumWithWasteSpace - stringSum);
}