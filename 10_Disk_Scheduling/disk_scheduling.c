
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void fcfs(int requests[], int n, int head)
{
    int totalMovement = 0;
    int current = head;

    printf("\nFCFS DISK SCHEDULING\n");
    printf("Seek Sequence: %d", current);

    for (int i = 0; i < n; i++)
    {
        totalMovement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement: %d\n", totalMovement);
}

void scan(int requests[], int n, int head, int diskSize, int direction)
{
    int sorted[MAX];
    int totalMovement = 0;
    int current = head;

    for (int i = 0; i < n; i++)
        sorted[i] = requests[i];

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (sorted[j] > sorted[j + 1])
            {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("\nSCAN DISK SCHEDULING\n");
    printf("Seek Sequence: %d", head);

    if (direction == 1)
    {
        int i = 0;

        while (i < n && sorted[i] < head)
            i++;

        for (int j = i; j < n; j++)
        {
            totalMovement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", current);
        }

        if (current != diskSize - 1)
        {
            totalMovement += abs((diskSize - 1) - current);
            current = diskSize - 1;
            printf(" -> %d", current);
        }

        for (int j = i - 1; j >= 0; j--)
        {
            totalMovement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", current);
        }
    }
    else
    {
        int i = n - 1;

        while (i >= 0 && sorted[i] > head)
            i--;

        for (int j = i; j >= 0; j--)
        {
            totalMovement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", current);
        }

        if (current != 0)
        {
            totalMovement += current;
            current = 0;
            printf(" -> %d", current);
        }

        for (int j = i + 1; j < n; j++)
        {
            totalMovement += abs(sorted[j] - current);
            current = sorted[j];
            printf(" -> %d", current);
        }
    }

    printf("\nTotal Head Movement: %d\n", totalMovement);
}

int main(void)
{
    int n, requests[MAX];
    int head, diskSize, direction;

    printf("DISK SCHEDULING ALGORITHMS\n");

    printf("Enter number of disk requests: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter disk request sequence:\n");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &requests[i]) != 1 || requests[i] < 0)
        {
            printf("Invalid request.\n");
            return 1;
        }
    }

    printf("Enter initial head position: ");
    if (scanf("%d", &head) != 1 || head < 0)
    {
        printf("Invalid head position.\n");
        return 1;
    }

    printf("Enter disk size (number of cylinders): ");
    if (scanf("%d", &diskSize) != 1 || diskSize < 1 ||
        diskSize > 100000 || head >= diskSize)
    {
        printf("Invalid disk size or head position.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (requests[i] >= diskSize)
        {
            printf("Request outside disk range.\n");
            return 1;
        }
    }

    printf("Enter SCAN direction (1 = right, 0 = left): ");
    if (scanf("%d", &direction) != 1 ||
        (direction != 0 && direction != 1))
    {
        printf("Invalid direction.\n");
        return 1;
    }

    fcfs(requests, n, head);
    scan(requests, n, head, diskSize, direction);

    return 0;
}
