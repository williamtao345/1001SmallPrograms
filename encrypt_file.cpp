#include <stdlib.h>
#include <stdio.h>

typedef char TYPE_OF_ENCRYPT;

// #define TEST
#ifdef TEST
#define PASSWORD 2
#else
#define PASSWORD GetPassword()
#endif

char GetKey()
{
    char input;
    system("stty -icanon");
    input = getchar();
    if (input == '\033')
    {
        input = getchar();
        if (input == '[')
        {
            input = getchar();
        }
    }
    system("stty icanon");
    printf("\r\033[k");
    return input;
}

void ShowPage1()
{
    printf("\x1b[H\x1b[2J");
    printf("Encrypt File <-\n");
    printf("Decrypt File\n");
}

void ShowPage2()
{
    printf("\x1b[H\x1b[2J");
    printf("Encrypt File\n");
    printf("Decrypt File <-\n");
}

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
            printf("\x1b[H\x1b[2J");
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
    printf("\x1b[H\x1b[2J");
    return EOF;
}

char *GetSourceFileName()
{
    char *sourceFileName;
    sourceFileName = (char *)calloc(20, sizeof(char));
    printf("Input source file name :");
    fflush(stdout);
    scanf("%s", sourceFileName);
    return sourceFileName;
}

char *GetEncryptFileName()
{
    char *encryptFileName;
    encryptFileName = (char *)calloc(20, sizeof(char));
    printf("Input encrypt file name :");
    fflush(stdout);
    scanf("%s", encryptFileName);
    return encryptFileName;
}

TYPE_OF_ENCRYPT GetPassword()
{
    TYPE_OF_ENCRYPT password;
    printf("Input password: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%c", &password);
    return password;
}

void EncryptFile()
{
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

    TYPE_OF_ENCRYPT password = PASSWORD;
    TYPE_OF_ENCRYPT info;
    fread(&info, sizeof(TYPE_OF_ENCRYPT), 1, sourceFile);
    while (!feof(sourceFile))
    {
        info = password ^ info;
        fwrite(&info, sizeof(TYPE_OF_ENCRYPT), 1, encryptFile);
        fread(&info, sizeof(TYPE_OF_ENCRYPT), 1, sourceFile);
    }

    fclose(encryptFile);
    fclose(sourceFile);
}

void DecryptFile()
{
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

    TYPE_OF_ENCRYPT password = PASSWORD;
    TYPE_OF_ENCRYPT info;
    fread(&info, sizeof(TYPE_OF_ENCRYPT), 1, encryptFile);
    while (!feof(encryptFile))
    {
        info = info ^ password;
        fwrite(&info, sizeof(TYPE_OF_ENCRYPT), 1, sourceFile);
        fread(&info, sizeof(TYPE_OF_ENCRYPT), 1, encryptFile);
    }

    fclose(encryptFile);
    fclose(sourceFile);
}

int main()
{
    while (1)
    {
        printf("**********type Y to exit**********");
        getchar();
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
}