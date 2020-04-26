#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

struct Token {
    char* curr;
    char* child;
};

void printAST(char *word, struct Token *tokens) {
    printf("digraph AST {\n");
    printf("\t\"%s\" -> \"%s\"\n", word, tokens[0].curr);
    printf("\t\"%s\" -> \"%s\"\n", word, tokens[1].curr);
    printf("\t\"%s\" -> \"%s\"\n", word, tokens[2].curr);
    printf("\t\"%s\"\n", tokens[0].curr);
    printf("\t\"%s\" -> \"%s\"\n", tokens[1].curr, tokens[1].child);
    printf("\t\"%s\"\n", tokens[2].curr);
    printf("}\n");
}

char *choppy( char *s )
{
    char *n = malloc( strlen( s ? s : "\n" ) );
    if( s )
        strcpy( n, s );
    n[strlen(n)-1]='\0';
    return n;
}

void parse(char *word) {
    struct Token tokens[3];
    word = choppy(word);
    if (strcmp(word, "abc") != 0 && strcmp(word, "abcc")) {
        printf("NULL\n");
        return;
    }

    tokens[0].curr = "a";
    tokens[1].curr = "B";
    tokens[2].curr = "c";
    if (strcmp(word, "abc") == 0) {
        tokens[1].child = "b";
    }
    else {
        tokens[1].child = "bc";
    }
    printAST(word, tokens);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Invalid number of arguments.");
        exit(-1);
    }

    FILE *tokens_file = fopen(argv[1], "r");

    char line[SIZE];
    while (fgets(line, SIZE, tokens_file) != NULL)
    {
        parse(line);
    }

}