
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

// Required union for semctl()
union semun
{
    int val;
};

int main(void)
{
    int shmid, semid;
    char *shared_memory;
    pid_t pid;

    struct sembuf operation;

    // Create shared memory
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

    // Create semaphore
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("semget");
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    // Initialize semaphore to 0
    union semun argument;
    argument.val = 0;

    if (semctl(semid, 0, SETVAL, argument) == -1)
    {
        perror("semctl SETVAL");
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    printf("Shared memory and semaphore created.\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    if (pid == 0)
    {
        // Child waits for parent signal
        printf("\nChild: Waiting for data...\n");
        fflush(stdout);

        operation.sem_num = 0;
        operation.sem_op = -1;
        operation.sem_flg = 0;

        if (semop(semid, &operation, 1) == -1)
        {
            perror("semop wait");
            shmdt(shared_memory);
            _exit(1);
        }

        printf("Child: Data received: %s\n", shared_memory);
        printf("Child PID: %d\n", getpid());

        shmdt(shared_memory);
        _exit(0);
    }
    else
    {
        // Parent writes data
        strcpy(shared_memory,
               "Hello! Shared memory synchronized using semaphore.");

        printf("\nParent: Data written to shared memory.\n");

        // Signal child
        operation.sem_num = 0;
        operation.sem_op = 1;
        operation.sem_flg = 0;

        if (semop(semid, &operation, 1) == -1)
        {
            perror("semop signal");
            wait(NULL);
            shmdt(shared_memory);
            shmctl(shmid, IPC_RMID, NULL);
            semctl(semid, 0, IPC_RMID);
            return 1;
        }

        printf("Parent: Semaphore signal sent.\n");

        wait(NULL);

        printf("\nParent: Child process completed.\n");

        shmdt(shared_memory);

        // Remove IPC resources
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);

        printf("Shared memory and semaphore removed.\n");
    }

    return 0;
}

