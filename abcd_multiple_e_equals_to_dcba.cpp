#include <stdio.h>

int Power(int base, int index)
{
    int number = 1;
    if (base < 0 || index < 0)
    {
        return 0;
    }

    for (int i = 0; i < index; i++)
    {
        number = number * base;
    }
    return number;
}

void TransferToDigits(int *digits, int number)
{
    for (int i = 0; i < 4; i++)
    {
        digits[i] = number / Power(10, 3 - i);
        number -= digits[i] * Power(10, 3 - i);
    };
}

void ReverseDigits(int *digits)
{
    for (int i = 0; i < 2; i++)
    {
        int digit = digits[i];
        digits[i] = digits[3 - i];
        digits[3 - i] = digit;
    };
};

int TransferToNumber(int *digits)
{
    int number = 0;
    for (int i = 0; i < 4; i++)
    {
        number += digits[i] * Power(10, 3 - i);
    };
    return number;
};

int ReverseNumber(int number)
{
    int digits[4];
    TransferToDigits(digits, number);
    ReverseDigits(digits);
    return TransferToNumber(digits);
}

int main()
{
    printf("---------------------\n");
    for (int i = 1000; i < 10000; i++)
    {
        int reversedNumber = ReverseNumber(i);
        for (int j = 1; j < 10; j++)
        {
            if (i * j > 10000)
            {
                break;
            }
            else if (i * j == reversedNumber)
            {
                printf("%d * %d = %d\n", i, j, reversedNumber);
            };
        };
    }
}