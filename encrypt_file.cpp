#include <stdlib.h>
#include <stdio.h>

typedef char TYPE_OF_ENCRYPT;
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

    TYPE_OF_ENCRYPT password = 2/* GetPassword() */;
    TYPE_OF_ENCRYPT info;
    info = fread(&info, sizeof(TYPE_OF_ENCRYPT), 1, sourceFile);
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

    TYPE_OF_ENCRYPT password = 2/* GetPassword() */;
    TYPE_OF_ENCRYPT info;
    while (!feof(encryptFile))
    {
        fread(&info, sizeof(TYPE_OF_ENCRYPT), 1, encryptFile);
        info = info ^ password;
        fwrite(&info, sizeof(TYPE_OF_ENCRYPT), 1, sourceFile);
    }

    fclose(encryptFile);
    fclose(sourceFile);
}

int main()
{
    printf("Input 1 To Encrypt File;\nInput 2 To Decrypt File;\nEncrypt or Decrypt File: ");
    fflush(stdout);

    int selection;
    scanf("%d", &selection);

    switch (selection)
    {
    case 1:
        EncryptFile();
        break;
    case 2:
        DecryptFile();
    default:
        break;
    }
}