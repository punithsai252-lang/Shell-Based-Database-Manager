#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

int main(void)
{
    char line[200];

    printf("Enter a command: ");
    fgets(line, sizeof(line), stdin);

    char **tokens = parse_command(line);

    printf("\nParsed Tokens:\n");

    for (int i = 0; tokens[i] != NULL; i++)
    {
        printf("tokens[%d] = %s\n", i, tokens[i]);
    }

    free_tokens(tokens);

    return 0;
}
