
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    printf("===== PROCESS SYSTEM CALLS =====\n");

    printf("\nParent process started.");
    printf("\nParent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\nChild process created.");
        printf("\nChild PID: %d\n", getpid());

        printf("\nExecuting ls command...\n");
        fflush(stdout);

        execlp("ls", "ls", "-l", NULL);

        perror("Exec failed");
        exit(1);
    }
    else
    {
        printf("\nParent is waiting for child...\n");

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Wait failed");
            return 1;
        }

        printf("\nChild process terminated.");

        if (WIFEXITED(status))
        {
            printf("\nExit status: %d\n",
                   WEXITSTATUS(status));
        }
        else
        {
            printf("\nChild did not terminate normally.\n");
        }
    }

    printf("\nParent process completed.\n");

    return 0;
}
