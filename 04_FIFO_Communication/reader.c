
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main(void)
{
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(FIFO_NAME, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    read(fd, buffer, BUFFER_SIZE);

    printf("\nMessage received: %s\n", buffer);

    close(fd);

    return 0;
}
