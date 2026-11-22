
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main(void)
{
    int fd;
    char message[BUFFER_SIZE];

    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");
    }

    printf("Enter a message: ");
    fgets(message, BUFFER_SIZE, stdin);

    fd = open(FIFO_NAME, O_WRONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, message, strlen(message) + 1);

    printf("Message sent successfully!\n");

    close(fd);

    return 0;
}
