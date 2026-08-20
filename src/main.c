#include <stdio.h>
#include <string.h>
#include "database.h"

int main()
{
    Database db;
    char command[1024];
    char table_name[100];

    database_init(&db);

    printf("============================================\n");
    printf("       SHELL BASED DATABASE MANAGER\n");
    printf("============================================\n");
    printf("Type 'help' to see available commands.\n\n");

    while (1)
    {
        printf("db> ");

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting Database Manager...\n");
            break;
        }

        else if (strcmp(command, "help") == 0)
        {
            printf("\nAvailable Commands:\n");
            printf("  create <table>  - Create a new table\n");
            printf("  insert <table>  - Insert a row into a table\n");
            printf("  select <table>  - Display table data\n");
            printf("  show tables     - Show all tables\n");
            printf("  drop <table>    - Delete a table\n");
            printf("  help             - Show this help menu\n");
            printf("  exit             - Exit the program\n\n");
        }

        else if (strcmp(command, "show tables") == 0)
        {
            database_show_tables(&db);
        }

        else if (sscanf(command, "create %99s", table_name) == 1)
        {
            database_create_table(&db, table_name);
        }

        else if (sscanf(command, "insert %99s", table_name) == 1)
        {
            database_insert(&db, table_name);
        }

        else if (sscanf(command, "select %99s", table_name) == 1)
        {
            database_select(&db, table_name);
        }

        else if (sscanf(command, "drop %99s", table_name) == 1)
        {
            database_drop_table(&db, table_name);
        }

        else if (strlen(command) > 0)
        {
            printf("Unknown command. Type 'help' for available commands.\n");
        }
    }

    return 0;
}
