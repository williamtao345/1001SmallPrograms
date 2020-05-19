#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_INPUT 100

struct node;
struct WordNode
{
    char word[20];
    int frequency;
    struct WordNode *next_word_link;
};
typedef struct node
{
    struct WordNode *first_word_link, *last_word_link;
} * WordTree;

WordTree init_word_tree()
{
    WordTree word_tree = (WordTree)calloc(1, sizeof(WordTree));
    WordNode *word_node = (WordNode *)calloc(1, sizeof(WordNode));
    word_tree->first_word_link = word_node;
    word_tree->last_word_link = word_node;
    return word_tree;
};

WordNode *add_word_node(WordTree word_tree, char *word)
{
    WordNode *word_node = (WordNode *)calloc(1, sizeof(WordNode));
    strcpy(word_node->word, word);
    word_node->frequency = 1;
    word_tree->last_word_link->next_word_link = word_node;
    word_tree->last_word_link = word_node;
    return word_node;
};

WordNode *find_word_in_word_tree(WordTree word_tree, char *word)
{
    WordNode *p = word_tree->first_word_link;
    do
    {
        if (!strcmp(p->word, word))
        {
            return p;
        };
        p = p->next_word_link;
    } while (p != 0);
    return 0;
};

int form_word_tree(WordTree word_tree, char *&input_string, char *delim)
{
    char sep = '\n';
    input_string = strtok(input_string, &sep);
    strcpy(word_tree->first_word_link->word, strtok(input_string, delim));
    if (*word_tree->first_word_link->word == 0)
    {
        exit(0);
    }
    else
    {
        word_tree->first_word_link->frequency = 1;
    };

    int number_of_word_nodes = 1;
    WordNode *p_WordNode;
    char *p_strtok;
    while ((p_strtok = strtok(NULL, delim)))
    {
        p_WordNode = find_word_in_word_tree(word_tree, p_strtok);
        if (p_WordNode == 0)
        {
            add_word_node(word_tree, p_strtok);
            number_of_word_nodes++;
        }
        else
        {
            p_WordNode->frequency++;
        };
    };
    return number_of_word_nodes;
};

//After changing, node->next_word_link becomes to word_node->next_word_link->next_word_link's next_word_link!
void switch_word_nodes(WordNode *word_node)
{
    WordNode *p = word_node->next_word_link;
    word_node->next_word_link = word_node->next_word_link->next_word_link;
    p->next_word_link = word_node->next_word_link->next_word_link;
    word_node->next_word_link->next_word_link = p;
};

void sort_word_tree(WordTree &word_tree, int number_of_word_nodes)
{
    WordNode *word_node = word_tree->first_word_link;
    if (number_of_word_nodes == 2)
    {
        if (word_node->frequency < word_node->next_word_link->frequency)
        {
            word_tree->first_word_link = word_node->next_word_link;
            WordNode *p = word_node->next_word_link->next_word_link;
            word_tree->first_word_link->next_word_link = word_node;
            word_node->next_word_link = p;
        };
    }
    if (number_of_word_nodes > 2)
    {
        for (int i = 0; i < number_of_word_nodes; i++)
        {
            if (word_node->frequency < word_node->next_word_link->frequency)
            {
                word_tree->first_word_link = word_node->next_word_link;
                WordNode *p = word_node->next_word_link->next_word_link;
                word_tree->first_word_link->next_word_link = word_node;
                word_node->next_word_link = p;
            };
            while (word_node->next_word_link->next_word_link != 0)
            {
                if (word_node->next_word_link->frequency < word_node->next_word_link->next_word_link->frequency)
                {
                    switch_word_nodes(word_node);
                };
                word_node = word_node->next_word_link;
            };
            word_node = word_tree->first_word_link;
        };
    };
};

void print_word_tree(WordTree word_tree, int number_of_word_nodes)
{
    WordNode *word_node = word_tree->first_word_link;
    printf("---------------------------------\n");
    for (int i = 0; i < number_of_word_nodes; i++)
    {
        printf("%s\t%d\n", word_node->word, word_node->frequency);
        printf("-----------------\n");
        word_node = word_node->next_word_link;
    };
};

int main()
{
    printf("------------------------------------------------------------------------------------------\n");
    printf("This small program calculates times every word appears in one paragraph(Word frequencies).\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("Introduction:\n");
    printf("Calculate how many times each word appears in one paragraph.\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("\t---- Made by William Tao----\n");
    printf("------------------------------------------------------------------------------------------\n");
    while (true)
    {
        char *input_string;
        char delim = ' ';
        input_string = (char *)calloc(SIZE_OF_INPUT, sizeof(char));
        printf("Input words (Input 0 to exit): ");
        fflush(stdout);
        fgets(input_string, SIZE_OF_INPUT, stdin);

        //--------Form word tree--------
        WordTree word_tree = init_word_tree();
        int number_of_word_nodes = form_word_tree(word_tree, input_string, &delim);

        //--------Sort word tree--------
        sort_word_tree(word_tree, number_of_word_nodes);

        //--------Print word tree--------
        print_word_tree(word_tree, number_of_word_nodes);
        free(word_tree);
    };
};