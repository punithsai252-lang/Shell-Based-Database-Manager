#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "parser.h"
#include "process.h"
#include "signals.h"
#include "pipes.h"

int main(void)
{
    Database db;
    char command[1024];

    database_init(&db);

    /* Initialize signal handlers */
    initialize_signals();

    printf("========================================\n");
    printf("      SHELL BASED DATABASE MANAGER\n");
    printf("========================================\n");
    printf("Type 'help' to see available commands.\n");

    while (1)
    {
        printf("db> ");

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break;
        }

        /* PIPE HANDLING */
        char *pipe_pos = strchr(command, '|');

        if (pipe_pos != NULL)
        {
            *pipe_pos = '\0';

            char *left_command = command;
            char *right_command = pipe_pos + 1;

            char **left_tokens = parse_command(left_command);
            char **right_tokens = parse_command(right_command);

            if (left_tokens[0] == NULL || right_tokens[0] == NULL)
            {
                printf("Error: both commands are required for a pipe.\n");

                free_tokens(left_tokens);
                free_tokens(right_tokens);
                continue;
            }

            execute_pipe(left_tokens, right_tokens);

            free_tokens(left_tokens);
            free_tokens(right_tokens);

            continue;
        }

        char **tokens = parse_command(command);

        if (tokens[0] == NULL)
        {
            free_tokens(tokens);
            continue;
        }

        /* EXIT */
        if (strcmp(tokens[0], "exit") == 0)
        {
            free_tokens(tokens);
            break;
        }

        /* HELP */
        else if (strcmp(tokens[0], "help") == 0)
        {
            printf("\nAvailable Commands:\n");
            printf("  create <table>  - Create a new table\n");
            printf("  insert <table>  - Insert a row into a table\n");
            printf("  select <table>  - Display table data\n");
            printf("  show tables      - Show all tables\n");
            printf("  drop <table>    - Delete a table\n");
            printf("  help             - Show this help menu\n");
            printf("  exit             - Exit the program\n");

            printf("\nExternal Linux Commands:\n");
            printf("  ls, pwd, date, whoami, etc.\n");
        }

        /* SHOW TABLES */
        else if (strcmp(tokens[0], "show") == 0 &&
                 tokens[1] != NULL &&
                 strcmp(tokens[1], "tables") == 0)
        {
            database_show_tables(&db);
        }

        /* CREATE */
        else if (strcmp(tokens[0], "create") == 0)
        {
            if (tokens[1] == NULL)
            {
                printf("Error: table name is required.\n");
            }
            else
            {
                database_create_table(&db, tokens[1]);
            }
        }

        /* INSERT */
        else if (strcmp(tokens[0], "insert") == 0)
        {
            if (tokens[1] == NULL)
            {
                printf("Error: table name is required.\n");
            }
            else
            {
                database_insert(&db, tokens[1]);
            }
        }

        /* SELECT */
        else if (strcmp(tokens[0], "select") == 0)
        {
            if (tokens[1] == NULL)
            {
                printf("Error: table name is required.\n");
            }
            else
            {
                database_select(&db, tokens[1]);
            }
        }

        /* DROP */
        else if (strcmp(tokens[0], "drop") == 0)
        {
            if (tokens[1] == NULL)
            {
                printf("Error: table name is required.\n");
            }
            else
            {
                database_drop_table(&db, tokens[1]);
            }
        }

        /* EXTERNAL LINUX COMMAND */
        else
        {
            execute_command(tokens);
        }

        free_tokens(tokens);
    }

    printf("Exiting Database Manager...\n");

    return 0;
}
