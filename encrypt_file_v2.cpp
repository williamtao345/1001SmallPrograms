#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "md5.h"

typedef char TypeOfEncrypt;
#define SOURCE_FILE_NAME "draft.cpp"
#define ENCRYPT_FILE_NAME "draft1.cpp"
#define DECRYPT_FILE_NAME "draft2.cpp"
#define CLEAN_SCREEN printf("\x1b[H\x1b[2J")
// #define WINDOWS
#define TEST

#ifdef TEST
#define PASSWORD   \
    {              \
        "hello", 5 \
    }
#else
#define PASSWORD GetPassword()
#endif

char GetKey()
{
    char input;
#ifndef WINDOWS
    system("stty -icanon");
#endif
    input = getchar();
    if (input == '\033')
    {
        input = getchar();
        if (input == '[')
        {
            input = getchar();
        }
    }
#ifndef WINDOWS
    system("stty icanon");
#endif
    printf("\r\033[k");
    return input;
}

void ShowPage1()
{
    CLEAN_SCREEN;
    printf("Encrypt File <-\n");
    printf("Decrypt File\n");
}

void ShowPage2()
{
    CLEAN_SCREEN;
    printf("Encrypt File\n");
    printf("Decrypt File <-\n");
}

#ifdef WINDOWS
int VisualPage()
{
    printf("Input 1 to encrypt file;\n");
    printf("Input 0 to decrypt file;\n");
    printf("Input -1 to quit;\n");
    printf("Your choice: ");
    fflush(stdout);
    fflush(stdin);
    char choice;
    int x;
    scanf("%d", &x);
    choice = (char)x;
    system("cls");
    return choice;
}
#else
int VisualPage()
{
    ShowPage1();
    char input = GetKey();
    char choice = 1;
    while (input != 'y')
    {
        switch (input)
        {
        case 'A':
            ShowPage1();
            choice = 1;
            break;
        case 'B':
            ShowPage2();
            choice = 0;
            break;
        case '\n':
            CLEAN_SCREEN;
            return choice;
        default:
            switch (choice)
            {
            case 1:
                ShowPage1();
                break;
            case 0:
                ShowPage2();
                break;
            }
            break;
        }
        input = GetKey();
    }
    CLEAN_SCREEN;
    return EOF;
}
#endif

char *GetSourceFileName()
{
    char *sourceFileName;
    sourceFileName = (char *)calloc(20, sizeof(char));
    printf("Input source file name  : ");
    fflush(stdout);
    scanf("%s", sourceFileName);
    return sourceFileName;
}

char *GetEncryptFileName()
{
    char *encryptFileName;
    encryptFileName = (char *)calloc(20, sizeof(char));
    printf("Input encrypt file name : ");
    fflush(stdout);
    scanf("%s", encryptFileName);
    return encryptFileName;
}

typedef struct
{
    char password[20];
    int length;
} Password;

Password GetPassword()
{
    Password password;
    printf("Input password: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%s", password.password);
    password.length = strlen(password.password);
    return password;
}

/* void WriteMd5(char *password, int length, FILE *fp)
{
    unsigned char *p = (unsigned char *)password;
    char *md5 = getMd5(p);
    fwrite(md5, sizeof(char), strlen(md5), fp);
    free(md5);
} */

void EncryptInfo(char *info, char *password, int length)
{
    for (int i = 0; i < length; i++)
    {
        info[i] = password[i] ^ info[i];
    }
}

void EncryptFile()
{

#ifdef TEST
    FILE *sourceFile;
    sourceFile = fopen(SOURCE_FILE_NAME, "rb");

    FILE *encryptFile;
    encryptFile = fopen(ENCRYPT_FILE_NAME, "wb");
#else
    FILE *sourceFile;
    char *sourceFileName;
    do
    {
        sourceFileName = GetSourceFileName();
    } while ((sourceFile = fopen(sourceFileName, "rb")) == NULL);

    FILE *encryptFile;
    char *encryptFileName;
    do
    {
        encryptFileName = GetEncryptFileName();
    } while ((encryptFile = fopen(encryptFileName, "wb")) == NULL);
#endif

    Password password = PASSWORD;
    char *info;
    info = (char *)calloc(password.length, sizeof(char));

    int valuebleBytes;
    while (!feof(sourceFile))
    {
        valuebleBytes = fread(info, sizeof(char), password.length, sourceFile);
        EncryptInfo(info, password.password, valuebleBytes);
        fwrite(info, sizeof(char), valuebleBytes, encryptFile);
    }

    fclose(encryptFile);
    fclose(sourceFile);
}

void DecryptInfo(char *info, char *password, int length)
{
    for (int i = 0; i < length; i++)
    {
        *(info + i) = (*(info + i)) ^ (*(password + i));
    }
}

void DecryptFile()
{

#ifdef TEST
    FILE *encryptFile;
    encryptFile = fopen(ENCRYPT_FILE_NAME, "rb");

    FILE *sourceFile;
    sourceFile = fopen(DECRYPT_FILE_NAME, "wb");
#else
    FILE *encryptFile;
    char *encryptFileName;
    do
    {
        encryptFileName = GetEncryptFileName();
    } while ((encryptFile = fopen(encryptFileName, "rb")) == NULL);

    FILE *sourceFile;
    char *sourceFileName;
    do
    {
        sourceFileName = GetSourceFileName();
    } while ((sourceFile = fopen(sourceFileName, "wb")) == NULL);
#endif

    Password password = PASSWORD;
    char *info;
    info = (char *)calloc(password.length, sizeof(char));
    int valuebleBytes;

    while (!feof(encryptFile))
    {
        valuebleBytes = fread(info, sizeof(char), password.length, encryptFile);
        DecryptInfo(info, password.password, valuebleBytes);
        fwrite(info, sizeof(char), valuebleBytes, sourceFile);
    }

    fclose(encryptFile);
    fclose(sourceFile);
}

int main()
{
#ifdef TEST
    EncryptFile();
    DecryptFile();
#else
    while (true)
    {
        printf("Reminder: Type Y to exit;\n");
        printf("Type any key to continue: ");
#ifndef WINDOWS
        system("stty -icanon");
#endif
        getchar();
#ifndef WINDOWS
        system("stty icanon");
#endif
        fflush(stdin);
        int selection = VisualPage();
        if (selection == EOF)
        {
            break;
        }

        switch (selection)
        {
        case 1:
            EncryptFile();
            break;
        case 0:
            DecryptFile();
        default:
            break;
        }
    }
#endif
}