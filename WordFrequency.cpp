#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WNN word_node->next_word_link

typedef struct node
{
    char word[20];
    int frequency;
    struct node *next_word_link;
} WordNode, *WordTree;

WordNode *init_WordNode(WordTree word_tree, char *word)
{
    WordNode *p;
    strcpy(p->word, word);
    p->frequency = 1;
    return p;
};

WordNode *find_word_in_word_tree(WordTree word_tree, char *word)
{
    WordNode *p = word_tree;
    while (p->next_word_link != 0)
    {
        if (!strcmp(p->word, word))
        {
            return p;
        };
    };
    return 0;
};

//After changing, node->next_word_link becomes to word_node->next_word_link->next_word_link's next_word_link!
void switch_word_nodes(WordNode *word_node)
{
    WordNode *p = WNN;
    WNN = WNN->next_word_link;
    p->next_word_link = WNN->next_word_link;
    WNN->next_word_link = p;
};

WordTree sort_word_tree(WordTree &word_tree, int number_of_word_nodes)
{
    WordNode *word_node = word_tree;
    for (int i = 0; i < number_of_word_nodes; i++)
    {
        if (word_node->frequency < WNN->frequency)
        {
            word_tree = WNN;
            WordNode *p = WNN->next_word_link;
            WNN = word_node;
            WNN = p;
        };
        while (WNN->next_word_link != 0)
        {
            if (WNN->frequency < WNN->next_word_link->frequency)
            {
                switch_word_nodes(word_node);
            };
            word_node = WNN;
        };
        word_node = word_tree;
    };
    return 0;
};

void print_word_tree(WordTree word_tree, int number_of_word_nodes)
{
    WordNode *word_node = word_tree;
    for (int i = 0; i < number_of_word_nodes; i++)
    {
        printf("%s %d", word_tree->word, word_tree->frequency);
        word_node = WNN;
    };
};

int main()
{
    char *string;
    char delim = ' ';
    string = (char *)calloc(100, sizeof(char));
    printf("Input words (Input 0 to exit):\n");
    gets(string);

    //--------Form word tree--------
    WordTree word_tree;
    strcpy(word_tree->word, strtok(string, &delim));
    if (*word_tree->word == 0)
    {
        exit(0);
    }
    else
    {
        word_tree->frequency = 1;
    }

    int number_of_word_nodes = 1; //Including word_tree.
    char *p_strtok;
    WordNode *p_WordNode;
    while ((p_strtok = strtok(string, &delim)))
    {
        p_WordNode = find_word_in_word_tree(word_tree, p_strtok);
        if (p_WordNode == 0)
        {
            init_WordNode(word_tree, p_strtok);
            number_of_word_nodes++;
        }
        else
        {
            p_WordNode->frequency++;
        };
    };

    //--------Sort word tree--------
    sort_word_tree(word_tree, number_of_word_nodes);

    //--------Print word tree--------
    print_word_tree(word_tree, number_of_word_nodes);
};