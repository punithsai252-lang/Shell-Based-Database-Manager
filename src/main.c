#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "parser.h"

int main(void)
{
    Database db;
    char command[1024];

    database_init(&db);

    printf("============================================\n");
    printf("     SHELL BASED DATABASE MANAGER\n");
    printf("============================================\n");
    printf("Type 'help' to see available commands.\n");

    while (1)
    {
        printf("db> ");

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break;
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

        /* UNKNOWN COMMAND */
        else
        {
            printf("Error: Unknown command '%s'.\n", tokens[0]);
            printf("Type 'help' to see available commands.\n");
        }

        free_tokens(tokens);
    }

    printf("Exiting Database Manager...\n");

    return 0;
}
