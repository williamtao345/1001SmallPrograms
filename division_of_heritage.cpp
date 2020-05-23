#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#include <assert.h>
#define ASSERT(value) assert(value)
#else
#define ASSERT(value) (void)(0)
#endif

struct intString
{
    int *link;
    int length;
};

void ResetAll(intString *divisionProportion, int &houseAmount, int &peopleAmount)
{
    free(divisionProportion->link);
    free(divisionProportion);
    houseAmount = 0;
    peopleAmount = 0;
};

int GetNumberFromFile(FILE *file)
{
    int number = 0;
    fscanf(file, "%d", &number);
    if (number == 0)
    {
        return 0;
    };
    return number;
};

intString *GetProportion(FILE *file, int &houseAmount, int &peopleAmount)
{
    intString *divisionProportion = (intString *)calloc(1, sizeof(intString));
    divisionProportion->link = (int *)calloc(peopleAmount, sizeof(int));
    for (int i = 0; i < peopleAmount; i++)
    {
        divisionProportion->link[i] = GetNumberFromFile(file);
        if (divisionProportion->link == 0)
        {
            ResetAll(divisionProportion, houseAmount, peopleAmount);
            printf("Illegal input!\n");
            fclose(file);
            exit(0);
        };
    }
    divisionProportion->length = peopleAmount;
    return divisionProportion;
};

int FindMaxNumber(intString *divisionProportion)
{
    int maxNumber = 0;
    for (int i = 0; i < divisionProportion->length; i++)
    {
        if (divisionProportion->link[i] > maxNumber)
        {
            maxNumber = divisionProportion->link[i];
        };
    };
    return maxNumber;
}

int FindMaximumCommonFactor(intString *divisionProportion)
{
    int maximumCommonFactor = 1;
    int maxNumber = FindMaxNumber(divisionProportion);
    int isCommonFactor;
    for (int i = 2; i < (maxNumber / 2 + 1); i++)
    {
        isCommonFactor = 1;
        for (int j = 0; j < divisionProportion->length; j++)
        {
            if (divisionProportion->link[j] % i != 0)
            {
                isCommonFactor = 0;
            };
        };
        if (isCommonFactor)
        {
            if (i > maximumCommonFactor)
            {
                maximumCommonFactor = i;
            }
        };
    };
    return maximumCommonFactor;
};

int SimplifyDivisionProportion(intString *divisionProportion)
{
    int maximumCommonFactor = FindMaximumCommonFactor(divisionProportion);
    if (maximumCommonFactor == 1)
        return 1;
    for (int i = 0; i < divisionProportion->length; i++)
    {
        divisionProportion->link[i] = divisionProportion->link[i] / maximumCommonFactor;
    };
    return 1;
};

int FindMaximumCommonMultiple(intString *divisionProportion, int houseAmount)
{
    int maximumCommonMultiple = 0;
    int sumOfAllNumbers = 0;
    for (int i = 0; i < divisionProportion->length; i++)
    {
        sumOfAllNumbers += divisionProportion->link[i];
    };
    int productOfAllNumbers = 1;
    while (productOfAllNumbers < houseAmount)
    {
        maximumCommonMultiple++;
        productOfAllNumbers = sumOfAllNumbers * maximumCommonMultiple;
        if (productOfAllNumbers == houseAmount)
        {
            return maximumCommonMultiple;
        }
    }
    return 0;
};

void MultipleAllNumbers(intString *divisionProportion, int multiplier)
{
    for (int i = 0; i < divisionProportion->length; i++)
    {
        divisionProportion->link[i] = divisionProportion->link[i] * multiplier;
    };
}

void PrintAllNumbers(intString *divisionProportion)
{
    for (int i = 0; i < divisionProportion->length; i++)
    {
        printf("%d ", divisionProportion->link[i]);
    };
    printf("\n");
}

int main()
{
    FILE *file = fopen("division_of_heritage_input.txt", "r");
    int houseAmount, peopleAmount;
    intString *divisionProportion;

    while (1)
    {
        if (!(houseAmount = GetNumberFromFile(file)))
        {
            fclose(file);
            exit(0);
        }
        if (!(peopleAmount = GetNumberFromFile(file)))
        {
            fclose(file);
            exit(0);
        }
        divisionProportion = GetProportion(file, houseAmount, peopleAmount);

        SimplifyDivisionProportion(divisionProportion);

        int maximumCommonMultiple = FindMaximumCommonMultiple(divisionProportion, houseAmount);

        if (maximumCommonMultiple)
        {
            MultipleAllNumbers(divisionProportion, maximumCommonMultiple);
            PrintAllNumbers(divisionProportion);
            ResetAll(divisionProportion, houseAmount, peopleAmount);
            continue;
        }
        else
        {
            ResetAll(divisionProportion, houseAmount, peopleAmount);
            printf("Can't solve;\n");
        }
    }
}