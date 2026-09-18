#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "process.h"

int execute_command(char **tokens)
{
    pid_t pid;
    int status;

    if (tokens == NULL || tokens[0] == NULL)
    {
        return 0;
    }

    pid = fork();

    if (pid == 0)
    {
        /* Child process */
        if (execvp(tokens[0], tokens) == -1)
        {
            perror("Database Manager");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Fork failed */
        perror("fork");
        return 0;
    }
    else
    {
        /* Parent process waits for child */
        do
        {
            waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
