#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* int IfPrimeNumber(int number)
{
    if (number == 2)
    {
        return 1;
    }
    else if (number == 1)
    {
        return 0;
    }
    else
    {
        for (int i = 2; i < number / 2; i++)
        {
            if (number % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }
}

int FindPrimeNumbers(int *primeNumbers, int head, int tail)
{
    int primeNumbersLen = 0;
    for (int x = head; x <= tail; x++)
    {
        if (IfPrimeNumber(x))
        {
            primeNumbers[primeNumbersLen] = x;
            primeNumbersLen++;
        }
    };
    return primeNumbersLen;
}

int FindArithmeticSequence(int *arithmeticSequence, int difference, int *primeNumbers, int primeNumbersLen)
{
    int arithmeticSequenceLen = 0;
    for (int c = 0; c < primeNumbersLen - 1; c++)
    {
        arithmeticSequence[0] = primeNumbers[c];
        int len = 1;
        int a = c;
        for (int b = a + 1; b < primeNumbersLen; ++b)
        {
            if (primeNumbers[b] - primeNumbers[a] == difference)
            {
                arithmeticSequence[len] = primeNumbers[b];
                len++;
                a = b;
            }
        };
        if (len > arithmeticSequenceLen)
        {
            arithmeticSequenceLen = len;
        };
    };
    return arithmeticSequenceLen;
}

void CopyIntString(int *string1, int *string2, int length)
{
    for (int i = 0; i < length; i++)
    {
        string1[i] = string2[i];
    }
}

int FindLongestArithmeticSequence(int *longestarithmeticSequence, int *primeNumbers, int primeNumbersLen)
{
    int longestarithmeticSequenceLen = 0;
    int *arithmeticSequence;
    arithmeticSequence = (int *)calloc(primeNumbersLen, sizeof(int));
    for (int i = 2; i < primeNumbers[primeNumbersLen - 1] - primeNumbers[0]; i++)
    {
        int x = primeNumbers[primeNumbersLen - 1] - primeNumbers[0];
        int arithmeticSequenceLen = FindArithmeticSequence(arithmeticSequence, i, primeNumbers, primeNumbersLen);
        if (arithmeticSequenceLen > longestarithmeticSequenceLen)
        {
            longestarithmeticSequenceLen = arithmeticSequenceLen;
            CopyIntString(longestarithmeticSequence, arithmeticSequence, longestarithmeticSequenceLen);
        }
    };
    return longestarithmeticSequenceLen;
}

void PrintIntString(int *string, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d, ", string[i]);
        fflush(stdout);
    };
    printf("\n");
}

int main()
{
    int head = 2;
    int tail = 10;
    int *primeNumbers, *longestarithmeticSequence;
    primeNumbers = (int *)calloc((tail - head) / 2, sizeof(int));
    int primeNumbersLen = FindPrimeNumbers(primeNumbers, head, tail);
    longestarithmeticSequence = (int *)calloc(primeNumbersLen, sizeof(int));
    int longestarithmeticSequenceLen = FindLongestArithmeticSequence(longestarithmeticSequence, primeNumbers, primeNumbersLen);
    PrintIntString(longestarithmeticSequence, longestarithmeticSequenceLen);
} */

int IfPrimeNumber(int number)
{
    if (number == 2)
    {
        return 1;
    }
    else if (number == 1)
    {
        return 0;
    }
    else
    {
        for (int i = 2; i < number / 2; i++)
        {
            if (number % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }
}

typedef int TYPE_OF_NUMBER_RANGE;

int FindPrimeNumbers(TYPE_OF_NUMBER_RANGE *primeNumbers, TYPE_OF_NUMBER_RANGE head, TYPE_OF_NUMBER_RANGE tail)
{
    int primeNumbersLen = 0;
    for (int x = head; x <= tail; x++)
    {
        if (IfPrimeNumber(x))
        {
            primeNumbers[primeNumbersLen] = x;
            primeNumbersLen++;
        }
    };
    return primeNumbersLen;
}

int IfIsArithmeticSequence(TYPE_OF_NUMBER_RANGE *numbers, int length)
{
    if (length <= 1)
    {
        return 1;
    }
    else
    {
        TYPE_OF_NUMBER_RANGE difference = numbers[1] - numbers[0];
        for (int i = 2; i < length; i++)
        {
            if ((numbers[2] - numbers[1]) != difference)
            {
                return 0;
            }
        }
        return 1;
    }
}

int FindArithmeticSequenceWithSpecificFirstNumber(TYPE_OF_NUMBER_RANGE *LongestArithmeticSequence, TYPE_OF_NUMBER_RANGE *primeNumbers, int primeNumbersLen, int numberNumber, int difference)
{
    int x = 2;
    int num = primeNumbers[numberNumber];
    for (int i = numberNumber + 1; i < primeNumbersLen; i++)
    {
        if (primeNumbers[i] - num == difference)
        {
            LongestArithmeticSequence[x] = primeNumbers[i];
            num = primeNumbers[i];
            x++;
        }
    }
    //printf("%d;\n",x);
    return x;
}

void printASNumbers(int *ASNum)
{
    int x = ASNum[0];
    for (int i = 0; i < ASNum[2]; i++)
    {
        printf("%d; ", x);
        x += ASNum[1];
    }
    printf("\n");
}

int FindLongestArithmeticSequence(TYPE_OF_NUMBER_RANGE *longestArithmeticSequence, TYPE_OF_NUMBER_RANGE *primeNumbers, int primeNumbersLen)
{
    int ASLen = 0;
    int len = 0;
    int ASNum[3]; //In the string: N0 is fisrt number of the string; N1 is the difference between each number; N2 is the length of the string;
    for (int numberNumber = 0; numberNumber < primeNumbersLen - 1; numberNumber++)
    {
        for (int i = numberNumber + 1; i < primeNumbersLen; i++)
        {
            len = FindArithmeticSequenceWithSpecificFirstNumber(longestArithmeticSequence, primeNumbers, primeNumbersLen, i, primeNumbers[i] - primeNumbers[numberNumber]);
            if (len > ASLen)
            {
                ASNum[0] = primeNumbers[numberNumber];
                ASNum[1] = primeNumbers[i] - primeNumbers[numberNumber];
                ASNum[2] = len;
                ASLen = len;
            }
        }
    };
    printASNumbers(ASNum);
    free(ASNum);
    return ASLen;
};

int main()
{
    const TYPE_OF_NUMBER_RANGE head = 100;
    const TYPE_OF_NUMBER_RANGE tail = 10000;

    TYPE_OF_NUMBER_RANGE *primeNumbers, *longestArithmeticSequence;
    primeNumbers = (TYPE_OF_NUMBER_RANGE *)calloc((tail - head) / 2, sizeof(TYPE_OF_NUMBER_RANGE));
    int primeNumbersLen = FindPrimeNumbers(primeNumbers, head, tail);
    longestArithmeticSequence = (TYPE_OF_NUMBER_RANGE *)calloc(primeNumbersLen, sizeof(TYPE_OF_NUMBER_RANGE));
    printf("%d;\n", FindLongestArithmeticSequence(longestArithmeticSequence, primeNumbers, primeNumbersLen));
    free(primeNumbers);
    free(longestArithmeticSequence);
}