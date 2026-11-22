
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void printResult(const char *name, int sequence[], int count, int movement)
{
    printf("\n%s\n", name);
    printf("Seek Sequence: ");

    for (int i = 0; i < count; i++)
        printf("%d ", sequence[i]);

    printf("\nTotal Head Movement: %d cylinders\n", movement);
}

void fcfs(int requests[], int n, int head)
{
    int sequence[MAX];
    int movement = 0;
    int current = head;

    for (int i = 0; i < n; i++)
    {
        sequence[i] = requests[i];
        movement += abs(current - requests[i]);
        current = requests[i];
    }

    printResult("FCFS DISK SCHEDULING", sequence, n, movement);
}

void sstf(int requests[], int n, int head)
{
    int visited[MAX] = {0};
    int sequence[MAX];
    int movement = 0;
    int current = head;

    for (int i = 0; i < n; i++)
    {
        int nearest = -1;
        int minimum = 2147483647;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int distance = abs(current - requests[j]);

                if (distance < minimum)
                {
                    minimum = distance;
                    nearest = j;
                }
            }
        }

        visited[nearest] = 1;
        sequence[i] = requests[nearest];
        movement += minimum;
        current = requests[nearest];
    }

    printResult("SSTF DISK SCHEDULING", sequence, n, movement);
}

void sortRequests(int requests[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void scan(int requests[], int n, int head, int diskSize, int direction)
{
    int sorted[MAX];
    int sequence[MAX];
    int count = 0;
    int movement = 0;
    int current = head;

    for (int i = 0; i < n; i++)
        sorted[i] = requests[i];

    sortRequests(sorted, n);

    if (direction == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (sorted[i] >= head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }

        movement += abs(current - (diskSize - 1));
        current = diskSize - 1;

        for (int i = n - 1; i >= 0; i--)
        {
            if (sorted[i] < head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }
    }
    else
    {
        for (int i = n - 1; i >= 0; i--)
        {
            if (sorted[i] <= head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }

        movement += current;
        current = 0;

        for (int i = 0; i < n; i++)
        {
            if (sorted[i] > head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }
    }

    printResult("SCAN DISK SCHEDULING", sequence, count, movement);
}

void cscan(int requests[], int n, int head, int diskSize, int direction)
{
    int sorted[MAX];
    int sequence[MAX];
    int count = 0;
    int movement = 0;
    int current = head;

    for (int i = 0; i < n; i++)
        sorted[i] = requests[i];

    sortRequests(sorted, n);

    if (direction == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (sorted[i] >= head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }

        movement += abs(current - (diskSize - 1));
        current = diskSize - 1;

        movement += diskSize - 1;
        current = 0;

        for (int i = 0; i < n; i++)
        {
            if (sorted[i] < head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }
    }
    else
    {
        for (int i = n - 1; i >= 0; i--)
        {
            if (sorted[i] <= head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }

        movement += current;
        current = 0;

        movement += diskSize - 1;
        current = diskSize - 1;

        for (int i = n - 1; i >= 0; i--)
        {
            if (sorted[i] > head)
            {
                sequence[count++] = sorted[i];
                movement += abs(current - sorted[i]);
                current = sorted[i];
            }
        }
    }

    printResult("C-SCAN DISK SCHEDULING", sequence, count, movement);
}

int main(void)
{
    int n, head, diskSize, direction;
    int requests[MAX];

    printf("DISK SCHEDULING ALGORITHMS\n");

    printf("Enter disk size (number of cylinders): ");

    if (scanf("%d", &diskSize) != 1 || diskSize < 2)
    {
        printf("Invalid disk size.\n");
        return 1;
    }

    printf("Enter number of disk requests: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter disk request sequence:\n");

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &requests[i]) != 1 ||
            requests[i] < 0 || requests[i] >= diskSize)
        {
            printf("Invalid cylinder number.\n");
            return 1;
        }
    }

    printf("Enter initial head position: ");

    if (scanf("%d", &head) != 1 || head < 0 || head >= diskSize)
    {
        printf("Invalid head position.\n");
        return 1;
    }

    printf("Enter direction (1 = Higher, 0 = Lower): ");

    if (scanf("%d", &direction) != 1 ||
        (direction != 0 && direction != 1))
    {
        printf("Invalid direction.\n");
        return 1;
    }

    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, diskSize, direction);
    cscan(requests, n, head, diskSize, direction);

    return 0;
}
