#include <stdio.h>
#include <stdlib.h>

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

TYPE_OF_WASTE_SPACE GetTotalSumWithWasteSpace(int *nString, int *numbersOfEachGroupsNumbers, int GroupNumber)
{
    TYPE_OF_WASTE_SPACE sum = 0;
    int headNumber = 0;
    int tailNumber = numbersOfEachGroupsNumbers[0] - 1;
    int maxNumberInGroup;
    for (int i = 0; i < (GroupNumber); i++)
    {
        maxNumberInGroup = (FindMaxNumberInGroup(nString, headNumber, tailNumber));
        headNumber += numbersOfEachGroupsNumbers[i];
        tailNumber += numbersOfEachGroupsNumbers[i + 1];
        sum += maxNumberInGroup * numbersOfEachGroupsNumbers[i];
    }
    return sum;
}

void PrintNumberWays(int *numbers,int len)
{
    for (int i = 0; i < len;i++)
    {
        printf("%d\t", numbers[i]);
    }
    printf("\n");
}

TYPE_OF_WASTE_SPACE TotalSumWithWasteSpace;
int IfIsFirstTime = 1;
int forFunction(int *nString, int nStringLength, int *numbersOfEachGroupsNumbers, int GroupNumber, int digit, int totalSum)
{
    if (digit == 1)
    {
        numbersOfEachGroupsNumbers[GroupNumber - digit] = nStringLength - totalSum;
        // printf("%d\n", numbersOfEachGroupsNumbers[GroupNumber - digit]);
        PrintNumberWays(numbersOfEachGroupsNumbers, GroupNumber);
        TYPE_OF_WASTE_SPACE x = GetTotalSumWithWasteSpace(nString, numbersOfEachGroupsNumbers, GroupNumber);
        if (IfIsFirstTime)
        {
            TotalSumWithWasteSpace = x;
            IfIsFirstTime = 0;
        }
        else if (x > TotalSumWithWasteSpace)
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
            // printf("%d", i);
            if ((nStringLength - totalSum - i) < (digit - 1))
            {
                break;
            }
            numbersOfEachGroupsNumbers[GroupNumber - digit] = i;
            forFunction(nString, nStringLength, numbersOfEachGroupsNumbers, GroupNumber, digit - 1, totalSum + i);
            i++;
        };
    };

    return 1;
}

void FormLeastWasteSpace(int *nString, int nStringLength, int GroupNumber, TYPE_OF_TOTAL_SUM stringSum)
{
    int *numbersOfEachGroupsNumbers = (int *)calloc(GroupNumber, sizeof(int));
    forFunction(nString, nStringLength, numbersOfEachGroupsNumbers, GroupNumber, GroupNumber, 0);
}

int main()
{
    printf("--------------------\n");
    FILE *file = fopen("input_for_snakes.txt", "r");
    int nStringLength = GetStringLength(file);
    int GroupNumber = GetChangingTimes(file) + 1;
    int *nString;
    nString = (int *)calloc(nStringLength, sizeof(int));
    GetnStringFromFile(nString, file, nStringLength);
    TYPE_OF_TOTAL_SUM stringSum = GetTotalSum(nString, nStringLength);
    FormLeastWasteSpace(nString, nStringLength, GroupNumber, stringSum);
    printf("%lld - %lld = %lld\n", TotalSumWithWasteSpace, stringSum, TotalSumWithWasteSpace - stringSum);
}