#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_WORD_SIZE 20
#define MAX_TXTNAME_SIZE 30
#define PATH_LENGTH 256
#define EXIT_IF_NULL(varibleName) \
    if (varibleName == 0)         \
        exit(0);

struct WordNode
{
    char word[20];
    int frequency;
    struct WordNode *nextWordLink;
};
typedef struct node
{
    struct WordNode *firstWordLink, *lastWordLink;
} * WordTree;

void PrintInfo()
{
    printf("------------------------------------------------------------------------------------------\n");
    printf("This small program calculates times every word appears in one paragraph(Word frequencies).\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("Introduction:\n");
    printf("Calculate how many times each word appears in one paragraph.\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("\t---- Made by William Tao----\n");
    printf("------------------------------------------------------------------------------------------\n");
}

char *CatNameToLink(char *fileCWD, char *txtName)
{
    strcat(fileCWD, "/");
    strcat(fileCWD, txtName);
    return fileCWD;
};

char *GetFileCWD()
{
    char *fileCWD;
    fileCWD = (char *)calloc(PATH_LENGTH, sizeof(char));
    getcwd(fileCWD, PATH_LENGTH);
    return fileCWD;
};

char *GetTxtCWD(char *txtName)
{
    return CatNameToLink(GetFileCWD(), txtName);
}

FILE *OpenFile(char *txtCWD)
{
    FILE *file = fopen(txtCWD, "r");
    EXIT_IF_NULL(file)
    return file;
};

WordTree InitWordTree()
{
    WordTree wordTree = (WordTree)calloc(1, sizeof(WordTree));
    WordNode *wordNode = (WordNode *)calloc(1, sizeof(WordNode));
    wordTree->firstWordLink = wordNode;
    wordTree->lastWordLink = wordNode;
    return wordTree;
};

char *GetWordFromFile(FILE *file)
{
    char *word = (char *)calloc(MAX_WORD_SIZE, sizeof(char));
    fscanf(file, "%s", word);
    return word;
}

char *WordLink(WordNode *wordNode)
{
    return wordNode->word;
}

WordNode *NextWordLink(WordNode *wordNode)
{
    return wordNode->nextWordLink;
}

int WordFrequency(WordNode *wordNode)
{
    return wordNode->frequency;
}

WordNode *AddEmptyWordNode(WordTree wordTree, char *word)
{
    WordNode *wordNode = (WordNode *)calloc(1, sizeof(WordNode));
    strcpy(wordNode->word, word);
    wordNode->frequency = 1;
    wordTree->lastWordLink->nextWordLink = wordNode;
    wordTree->lastWordLink = wordNode;
    return wordNode;
};

WordNode *FindWordInWordTree(WordTree wordTree, char *word)
{
    WordNode *p = wordTree->firstWordLink;
    do
    {
        if (!strcmp(p->word, word))
        {
            return p;
        };
        p = p->nextWordLink;
    } while (p != 0);
    return 0;
};

int AddWordNodeToWordTree(WordTree wordTree, char *word)
{
    WordNode *wordNodeLink;
    wordNodeLink = FindWordInWordTree(wordTree, word);
    if (wordNodeLink == 0)
    {
        AddEmptyWordNode(wordTree, word);
        return 1;
    }
    else
    {
        wordNodeLink->frequency++;
        return 0;
    };
}

int FormWordTree(WordTree wordTree, FILE *file)
{
    strcpy(WordLink(wordTree->firstWordLink), GetWordFromFile(file));
    EXIT_IF_NULL(*WordLink(wordTree->firstWordLink))
    wordTree->firstWordLink->frequency = 1;

    int numberOfWordNodes = 1;
    char *word = 0;
    while (true)
    {
        word = GetWordFromFile(file);
        if (*word == 0)
        {
            break;
        }
        numberOfWordNodes += AddWordNodeToWordTree(wordTree, word);
    };
    return numberOfWordNodes;
};

//After changing, node->nextWordLink becomes to wordNode->nextWordLink->nextWordLink's nextWordLink!
void SwitchWordNodes(WordNode *wordNode)
{
    WordNode *p = wordNode->nextWordLink;
    wordNode->nextWordLink = NextWordLink(NextWordLink(wordNode));
    p->nextWordLink = NextWordLink(wordNode);
    NextWordLink(wordNode)->nextWordLink = p;
};

void SwitchFirststSecondWordNodes(WordTree wordTree)
{
    WordNode *wordNode = wordTree->firstWordLink;
    wordTree->firstWordLink = wordNode->nextWordLink;
    WordNode *p = wordNode->nextWordLink->nextWordLink;
    wordTree->firstWordLink->nextWordLink = wordNode;
    wordNode->nextWordLink = p;
}

void SortWordTree(WordTree &wordTree, int numberOfWordNodes)
{
    if (numberOfWordNodes == 2)
    {
        if (WordFrequency(wordTree->firstWordLink) < WordFrequency(NextWordLink(wordTree->firstWordLink)))
            SwitchFirststSecondWordNodes(wordTree);
    }

    if (numberOfWordNodes > 2)
    {
        WordNode *wordNode = wordTree->firstWordLink;
        for (int i = 0; i < numberOfWordNodes; i++)
        {
            if (WordFrequency(wordTree->firstWordLink) < WordFrequency(NextWordLink(wordTree->firstWordLink)))
            {
                SwitchFirststSecondWordNodes(wordTree);
            };
            while (NextWordLink(wordNode->nextWordLink) != 0)
            {
                if (WordFrequency(wordNode->nextWordLink) < WordFrequency(NextWordLink(wordNode->nextWordLink)))
                {
                    SwitchWordNodes(wordNode);
                };
                wordNode = wordNode->nextWordLink;
            };
            wordNode = wordTree->firstWordLink;
        };
    };
};

void PrintWordTree(WordTree wordTree, int numberOfWordNodes)
{
    WordNode *wordNode = wordTree->firstWordLink;
    printf("---------------------------------\n");
    for (int i = 0; i < numberOfWordNodes; i++)
    {
        printf("%s\t%d\n", wordNode->word, wordNode->frequency);
        printf("-----------------\n");
        wordNode = wordNode->nextWordLink;
    };
};

int FreeWordTree(WordNode *wordNode)
{
    if(wordNode->nextWordLink == 0)
    {
        free(wordNode);
        return 0;
    }
    if(FreeWordTree(wordNode->nextWordLink) == 0)
    {
        free(wordNode);
        return 0;
    }
    return 1;
}

int main()
{
    PrintInfo();
    char txtName[] = "Word-Frequency-Input.txt"; //Your name of txt file in the folder.
    FILE *file = OpenFile(GetTxtCWD(txtName));
    //--------Form word tree--------
    WordTree wordTree = InitWordTree();
    int numberOfWordNodes = FormWordTree(wordTree, file);

    //--------Sort word tree--------
    SortWordTree(wordTree, numberOfWordNodes);

    //--------Print word tree--------
    PrintWordTree(wordTree, numberOfWordNodes);
    FreeWordTree(wordTree->firstWordLink);
};