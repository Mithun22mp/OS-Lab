
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main(void)
{
    int shmid;
    char *shared_memory;
    pid_t pid;

    // Create shared memory segment
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    // Attach shared memory
    shared_memory = (char *)shmat(shmid, NULL, 0);

    if (shared_memory == (char *)-1)
    {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    printf("Shared memory created successfully.\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    if (pid == 0)
    {
        // Child process writes data
        printf("\nChild Process:\n");

        strcpy(shared_memory, "Hello from Child Process!");

        printf("Data written to shared memory.\n");
        printf("Child PID: %d\n", getpid());

        shmdt(shared_memory);
        exit(0);
    }
    else
    {
        // Parent waits for child
        wait(NULL);

        printf("\nParent Process:\n");
        printf("Data received: %s\n", shared_memory);
        printf("Parent PID: %d\n", getpid());

        // Detach and remove shared memory
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);

        printf("\nShared memory removed successfully.\n");
    }

    return 0;
}
