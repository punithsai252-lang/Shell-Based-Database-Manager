#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "builtin.h"

int is_builtin(char **tokens)
{
    if (tokens == NULL || tokens[0] == NULL)
    {
        return 0;
    }

    if (strcmp(tokens[0], "cd") == 0 ||
        strcmp(tokens[0], "pwd") == 0 ||
        strcmp(tokens[0], "help") == 0 ||
        strcmp(tokens[0], "clear") == 0 ||
        strcmp(tokens[0], "env") == 0 ||
        strcmp(tokens[0], "exit") == 0)
    {
        return 1;
    }

    return 0;
}

int execute_builtin(char **tokens)
{
    if (tokens == NULL || tokens[0] == NULL)
    {
        return 0;
    }

    /* cd */
    if (strcmp(tokens[0], "cd") == 0)
    {
        const char *path;

        if (tokens[1] == NULL)
        {
            path = getenv("HOME");
        }
        else
        {
            path = tokens[1];
        }

        if (chdir(path) != 0)
        {
            perror("cd");
        }

        return 1;
    }

    /* pwd */
    if (strcmp(tokens[0], "pwd") == 0)
    {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("pwd");
        }

        return 1;
    }

    /* help */
    if (strcmp(tokens[0], "help") == 0)
    {
        printf("\nShell Based Database Manager Commands:\n\n");

        printf("Database Commands:\n");
        printf("  create <table>  - Create a new table\n");
        printf("  insert <table>  - Insert a row into a table\n");
        printf("  select <table>  - Display table data\n");
        printf("  show tables     - Show all tables\n");
        printf("  drop <table>    - Delete a table\n\n");

        printf("Built-in Commands:\n");
        printf("  cd <directory>  - Change current directory\n");
        printf("  pwd             - Show current directory\n");
        printf("  clear           - Clear the terminal\n");
        printf("  env             - Display environment variables\n");
        printf("  help            - Show this help menu\n");
        printf("  exit            - Exit the program\n\n");

        return 1;
    }

    /* clear */
    if (strcmp(tokens[0], "clear") == 0)
    {
        system("clear");
        return 1;
    }

    /* env */
    if (strcmp(tokens[0], "env") == 0)
    {
        extern char **environ;

        for (char **env = environ; *env != NULL; env++)
        {
            printf("%s\n", *env);
        }

        return 1;
    }

    /* exit */
    if (strcmp(tokens[0], "exit") == 0)
    {
        printf("Exiting Database Manager...\n");
        exit(0);
    }

    return 0;
}
