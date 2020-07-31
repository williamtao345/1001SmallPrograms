#include <stdlib.h>
#include <stdio.h>

typedef int TypeOfEncrypt;
#define NEW_ENCRYPT_FILE
#define SOURCE_FILE_NAME "draft.cpp"
#define ENCRYPT_FILE_NAME "draft1.cpp"
#define DECRYPT_FILE_NAME "draft2.cpp"
#define CLEAN_SCREEN printf("\x1b[H\x1b[2J")
// #define WINDOWS
// #define TEST

#ifdef TEST
#define PASSWORD 123
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
    printf("Input 2 to decrypt file;\n");
    printf("Input -1 to quit;\n")
        printf("Your choice: ");
    fflush(stdout);
    char choice;
    scanf("%c", &choice);
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

TypeOfEncrypt GetPassword()
{
    TypeOfEncrypt password;
    printf("Input password: ");
    fflush(stdout);
    fflush(stdin);
    int x;
    scanf("%d", &x);
    password = (TypeOfEncrypt)x;
    return password;
}

int SizeOfFile(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    int count = ftell(file);
    rewind(file);
    return count;
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

    TypeOfEncrypt password = PASSWORD;
    TypeOfEncrypt info;
    int i;
    while (!feof(sourceFile))
#ifdef NEW_ENCRYPT_FILE
    {
        i = fread(&info, sizeof(char), sizeof(TypeOfEncrypt), sourceFile);
        info = password ^ info;
        fwrite(&info, sizeof(char), sizeof(TypeOfEncrypt), encryptFile);
    }
    info = 8 - i;
    info = password ^ info;
    fwrite(&info, sizeof(int), 1, encryptFile);

#else
        while (!feof(sourceFile))
        {
            fread(&info, sizeof(char), sizeof(TypeOfEncrypt), sourceFile);
            info = password ^ info;
            fwrite(&info, sizeof(char), sizeof(TypeOfEncrypt), encryptFile);
        }
#endif

    fclose(encryptFile);
    fclose(sourceFile);
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

    TypeOfEncrypt password = PASSWORD;
    TypeOfEncrypt info;

#ifdef NEW_ENCRYPT_FILE
    int fileSize = SizeOfFile(encryptFile);

    FILE *tmpFp = fopen("tmpFile.txt", "wb");
    for (int i = 0; i < fileSize / sizeof(TypeOfEncrypt); i++)
    {
        fread(&info, sizeof(TypeOfEncrypt), 1, encryptFile);
        info = info ^ password;
        fwrite(&info, sizeof(TypeOfEncrypt), 1, tmpFp);
    }

    fileSize -= info;

    freopen("tmpFile.txt", "rb", tmpFp);
    for (int i = 0; i < fileSize; i++)
    {
        int x = ftell(tmpFp);
        int y = fread(&info, sizeof(char), 1, tmpFp);
        fwrite(&info, sizeof(char), 1, sourceFile);
    }
    fclose(tmpFp);
    remove("tmpFile.txt");

#else
    while (!feof(encryptFile))
    {
        fread(&info, sizeof(TypeOfEncrypt), 1, encryptFile);
        info = info ^ password;
        fwrite(&info, sizeof(TypeOfEncrypt), 1, sourceFile);
    }
#endif

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