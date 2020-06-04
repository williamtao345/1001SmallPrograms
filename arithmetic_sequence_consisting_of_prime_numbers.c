#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}