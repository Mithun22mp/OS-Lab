
#include <stdio.h>

#define MAX 50

void firstFit(int blocks[], int m, int process[], int n)
{
    int allocation[MAX];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blocks[j] >= process[i])
            {
                allocation[i] = j;
                blocks[j] -= process[i];
                break;
            }
        }
    }

    printf("\nFIRST FIT ALLOCATION\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i + 1, process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blocks[], int m, int process[], int n)
{
    int allocation[MAX];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int best = -1;

        for (int j = 0; j < m; j++)
        {
            if (blocks[j] >= process[i])
            {
                if (best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }

        if (best != -1)
        {
            allocation[i] = best;
            blocks[best] -= process[i];
        }
    }

    printf("\nBEST FIT ALLOCATION\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i + 1, process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blocks[], int m, int process[], int n)
{
    int allocation[MAX];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int worst = -1;

        for (int j = 0; j < m; j++)
        {
            if (blocks[j] >= process[i])
            {
                if (worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            allocation[i] = worst;
            blocks[worst] -= process[i];
        }
    }

    printf("\nWORST FIT ALLOCATION\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i + 1, process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main(void)
{
    int m, n;
    int blocks[MAX], process[MAX];
    int first[MAX], best[MAX], worst[MAX];

    printf("MEMORY ALLOCATION ALGORITHMS\n");

    printf("Enter number of memory blocks: ");
    if (scanf("%d", &m) != 1 || m < 1 || m > MAX)
        return printf("Invalid number of blocks.\n"), 1;

    printf("Enter block sizes:\n");
    for (int i = 0; i < m; i++)
    {
        if (scanf("%d", &blocks[i]) != 1 || blocks[i] <= 0)
            return printf("Invalid block size.\n"), 1;
    }

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
        return printf("Invalid number of processes.\n"), 1;

    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &process[i]) != 1 || process[i] <= 0)
            return printf("Invalid process size.\n"), 1;
    }

    for (int i = 0; i < m; i++)
    {
        first[i] = blocks[i];
        best[i] = blocks[i];
        worst[i] = blocks[i];
    }

    firstFit(first, m, process, n);
    bestFit(best, m, process, n);
    worstFit(worst, m, process, n);

    return 0;
}
