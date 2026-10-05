#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "redirect.h"

int execute_redirection(char **args)
{
    int i;

    /* Check whether the command contains redirection */
    for (i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], ">") == 0 ||
            strcmp(args[i], ">>") == 0 ||
            strcmp(args[i], "<") == 0 ||
            strcmp(args[i], "2>") == 0)
        {
            break;
        }
    }

    /* No redirection found */
    if (args[i] == NULL)
        return 0;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        int fd;

        /*
         * Process every redirection in the command.
         */
        for (i = 0; args[i] != NULL; )
        {
            /*
             * Output redirection: >
             */
            if (strcmp(args[i], ">") == 0)
            {
                if (args[i + 1] == NULL)
                {
                    fprintf(stderr, "Error: output file is required.\n");
                    exit(EXIT_FAILURE);
                }

                fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

                if (fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                args[i] = NULL;
                args[i + 1] = NULL;

                /*
                 * Shift remaining arguments left.
                 */
                int j;

                for (j = i; args[j + 2] != NULL; j++)
                    args[j] = args[j + 2];

                args[j] = NULL;
                args[j + 1] = NULL;

                continue;
            }

            /*
             * Append redirection: >>
             */
            if (strcmp(args[i], ">>") == 0)
            {
                if (args[i + 1] == NULL)
                {
                    fprintf(stderr, "Error: output file is required.\n");
                    exit(EXIT_FAILURE);
                }

                fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_APPEND,
                          0644);

                if (fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                args[i] = NULL;
                args[i + 1] = NULL;

                int j;

                for (j = i; args[j + 2] != NULL; j++)
                    args[j] = args[j + 2];

                args[j] = NULL;
                args[j + 1] = NULL;

                continue;
            }

            /*
             * Input redirection: <
             */
            if (strcmp(args[i], "<") == 0)
            {
                if (args[i + 1] == NULL)
                {
                    fprintf(stderr, "Error: input file is required.\n");
                    exit(EXIT_FAILURE);
                }

                fd = open(args[i + 1], O_RDONLY);

                if (fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                if (dup2(fd, STDIN_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                args[i] = NULL;
                args[i + 1] = NULL;

                int j;

                for (j = i; args[j + 2] != NULL; j++)
                    args[j] = args[j + 2];

                args[j] = NULL;
                args[j + 1] = NULL;

                continue;
            }

            /*
             * Error redirection: 2>
             */
            if (strcmp(args[i], "2>") == 0)
            {
                if (args[i + 1] == NULL)
                {
                    fprintf(stderr, "Error: error output file is required.\n");
                    exit(EXIT_FAILURE);
                }

                fd = open(args[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);

                if (fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                if (dup2(fd, STDERR_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }

                close(fd);

                args[i] = NULL;
                args[i + 1] = NULL;

                int j;

                for (j = i; args[j + 2] != NULL; j++)
                    args[j] = args[j + 2];

                args[j] = NULL;
                args[j + 1] = NULL;

                continue;
            }

            i++;
        }

        /*
         * Execute the cleaned command.
         */
        if (args[0] == NULL)
            exit(EXIT_SUCCESS);

        execvp(args[0], args);

        perror("execvp");
        exit(EXIT_FAILURE);
    }

    /*
     * Parent waits for the child.
     */
    waitpid(pid, NULL, 0);

    return 1;
}
