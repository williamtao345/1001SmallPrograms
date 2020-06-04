#include <stdio.h>
#include <string.h>

/* void DeleteDigits(char *n, int len)
{
    int x = 0;
    while (n[x] != '\0')
    {
        x++;
    };
    for (int i = 0; i < len; i++)
    {
        n[i] = n[x - len + i];
    };
    for (int i = len; i < 14; i++)
    {
        n[i] = '\0';
    };
}

void AddNumberToEndOfString(char *string, int number)
{
    int x = 0;
    while (string[x] != '\0')
    {
        x++;
    };
    string[x] = number;
}

void FindNextNumber(char *n, char *maxNumber, int len)
{
    for (int i = 9; i >= 0; i--)
    {
        for (int j = 0; j < len; j++)
        {
            if (int(n[j]) == (i + 48))
            {
                if (len - j - 1 > 3)
                {
                    AddNumberToEndOfString(maxNumber, i + 48);
                    maxNumberLen++;
                    len--;
                    DeleteDigits(n, len);
                }
                else if (len - j - 1 == (3 - maxNumberLen))
                {
                    return n;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

char *GetMaxNumber(char *n, char *maxNumber, int len)
{
    int maxNumberLen = 0;
    while (true)
    {
        FindNextNumber(n, maxNumber, len, maxNumberLen);
    }
    return n;
}

int main()
{
    char n[15] = "92081346718538";
    char maxNumber[4];
    memset(maxNumber, 0, 4);
    GetMaxNumber(n, maxNumber, 14);

    printf("%s", maxNumber);
} */

#define NUMBER_LENGTH 14
#define ANSWER_LENGTH 4
//return place of next number;
int maxNumber = 9;
int FindNextNumber(char *n, int len)
{
    for (int i = maxNumber; i >= 0; i--)
    {
        for (int j = 0; j < len; j++)
        {
            if (n[j] == (i + '0'))
            {
                return j;
            }
        }
    }
    return -1;
};

void AddNumberToEndOfChar(char *n, int number)
{
    int x = 0;
    while (n[x] != '\0')
    {
        x++;
    };
    n[x] = number;
}

//delete including n[numberPlace];
void DeletePreviousDigits(char *n, int numberPlace)
{
    int x = 0;
    while (n[x] != '\0')
    {
        x++;
    };
    for (int i = 0; i < x - numberPlace - 1; i++)
    {
        n[i] = n[numberPlace + 1 + i];
    };
    for (int i = x - numberPlace - 1; i < NUMBER_LENGTH; i++)
    {
        n[i] = '\0';
    };
}

void FindMaxNum1(char *n)
{
    char answer[5];
    memset(answer, 0, ANSWER_LENGTH);
    int answerLen = 0;
    int len = NUMBER_LENGTH;

    while (1)
    {
        int nextNumberPlace = FindNextNumber(n, len);
        if (len - nextNumberPlace < ANSWER_LENGTH - answerLen)
        {
            maxNumber = n[nextNumberPlace] - '0' - 1;
            continue;
        }
        else if (len - nextNumberPlace == ANSWER_LENGTH - answerLen)
        {
            for (int i = 0; i < ANSWER_LENGTH - answerLen; i++)
            {
                answer[answerLen + i] = n[nextNumberPlace + i];
            };
            break;
        }
        else
        {
            maxNumber = 9;
        };
        len = len - nextNumberPlace - 1;

        AddNumberToEndOfChar(answer, n[nextNumberPlace]);
        answerLen++;
        DeletePreviousDigits(n, nextNumberPlace);
        if (answerLen == ANSWER_LENGTH)
        {
            break;
        }
    };
    printf("%s\n", answer);
}

void Char2Int(const char *input, char *n)
{
    int x = 0;
    while (input[x] != '\0')
    {
        n[x] = input[x] - 48;
        x++;
    };
}

char FindMaxNum(char *n, char start, char end)
{
    for (int i = 9; i >= 0; i--)
    {
        for (int j = start; j < end + 1; j++)
        {
            if (n[j] == i)
            {
                return j;
            }
        }
    }
    return 0;
}

void FindMaxNum2(char *n)
{
    char input[] = {0};
    Char2Int(n, input);

    char result[4] = {0};

    char seed = -1;

    for (int i = 0; i < 4; i++)
    {
        seed = FindMaxNum(input, seed + 1, 10 + i);
        result[i] = input[seed];
    }

    for (int i = 0; i < 4;i++)
    {
        printf("%d", result[i]);
    };
    printf("\n");
}

int main()
{
    char x[] = "20813467185319";
    FindMaxNum1(x);
    char y[] = "20813467185319";
    FindMaxNum2(y);
}