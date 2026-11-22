
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MAX_SIZE 100

// Message structure
struct message
{
    long msg_type;
    char msg_text[MAX_SIZE];
};

int main(void)
{
    int msgid;
    pid_t pid;

    struct message msg;

    // Create message queue
    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    printf("Message queue created successfully.\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        msgctl(msgid, IPC_RMID, NULL);
        return 1;
    }

    if (pid == 0)
    {
        // Child process receives message
        printf("\nChild Process:\n");

        if (msgrcv(msgid, &msg, sizeof(msg.msg_text),
                   1, 0) == -1)
        {
            perror("msgrcv");
            exit(1);
        }

        printf("Message received: %s\n", msg.msg_text);
        printf("Child PID: %d\n", getpid());

        exit(0);
    }
    else
    {
        // Parent process sends message
        printf("\nParent Process:\n");

        msg.msg_type = 1;

        strcpy(msg.msg_text,
               "Hello from Parent using Message Queue!");

        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1)
        {
            perror("msgsnd");
            wait(NULL);
            msgctl(msgid, IPC_RMID, NULL);
            return 1;
        }

        printf("Message sent successfully.\n");
        printf("Parent PID: %d\n", getpid());

        wait(NULL);

        // Remove message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1)
        {
            perror("msgctl");
            return 1;
        }

        printf("\nMessage queue removed successfully.\n");
    }

    return 0;
}
