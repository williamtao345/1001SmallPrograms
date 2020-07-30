#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fwriteName(FILE *file)
{
    char input[20];
    memset(input, 0, 20 * sizeof(char));
    printf("Input your name: ");
    fflush(stdout);
    scanf("%s", input);
    fprintf(file, "Your name: ");
    fwrite(input, sizeof(char), 20, file);
}

void fscanfName(FILE *file)
{
    printf("fscanf: ");
    char output[30];
    memset(output, 0, 30 * sizeof(char));
    rewind(file);
    fscanf(file, "%s", output);
    printf("%s\n", output);
}

void freadName(FILE *file)
{
    printf("fread: ");
    char output[30];
    memset(output, 0, 30 * sizeof(char));
    rewind(file);
    fread(output, sizeof(char), 30, file);
    printf("%s\n", output);
}

int SizeOfFile(FILE *file)
{
    rewind(file);
    int count = 0;
    int p;

    char c;
    c = fgetc(file);
    while (!feof(file))
    {
        count++;
        printf("%X\n", c);
        p = ftell(file);
        c = fgetc(file);
    }
    return count;
}

int SizeOfFile2(FILE *file)
{
    rewind(file);
    int count = 0;
    int p;
    while (!feof(file))
    {
        count++;
        p = fseek(file, sizeof(char), SEEK_CUR);
    }
    /* for (int i = 0; i < 30;i++)
    {
        fseek(file, sizeof(char), SEEK_CUR);
    }
    printf("%ld", ftell(file));
    printf("%c", fgetc(file)); */
    return count;
}

int SizeOfFile3(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    int count = ftell(file);
    return count;
}

void CopyFile(FILE *fSource, FILE *fDestination, int sizeOfFile)
{
    rewind(fSource);
    rewind(fDestination);
    char *info;
    info = (char *)calloc(sizeOfFile, sizeof(char));

    for (int i = 0; i < sizeOfFile; i++)
    {
        fputc(fgetc(fSource), fDestination);
    }
}

int main()
{
    FILE *file = fopen("process_files.txt", "r+");
    FILE *file1 = fopen("process_files2.txt", "w");

    // fwriteName(file);
    // fscanfName(file);
    // freadName(file);

    // CopyFile(file, file1, SizeOfFile2(file));
    SizeOfFile2(file);
    fclose(file);
}