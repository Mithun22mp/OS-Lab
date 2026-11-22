
#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main(void)
{
    int n, m;

    int allocation[MAX_P][MAX_R];
    int request[MAX_P][MAX_R];
    int available[MAX_R];

    int work[MAX_R];
    bool finish[MAX_P] = {false};

    printf("DEADLOCK DETECTION ALGORITHM\n");

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_P)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter number of resource types: ");
    if (scanf("%d", &m) != 1 || m < 1 || m > MAX_R)
    {
        printf("Invalid number of resource types.\n");
        return 1;
    }

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            if (scanf("%d", &allocation[i][j]) != 1 ||
                allocation[i][j] < 0)
            {
                printf("Invalid allocation value.\n");
                return 1;
            }
        }
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            if (scanf("%d", &request[i][j]) != 1 ||
                request[i][j] < 0)
            {
                printf("Invalid request value.\n");
                return 1;
            }
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");

    for (int j = 0; j < m; j++)
    {
        if (scanf("%d", &available[j]) != 1 ||
            available[j] < 0)
        {
            printf("Invalid available resource value.\n");
            return 1;
        }

        work[j] = available[j];
    }

    // Initialize Finish
    for (int i = 0; i < n; i++)
    {
        bool has_allocation = false;

        for (int j = 0; j < m; j++)
        {
            if (allocation[i][j] != 0)
            {
                has_allocation = true;
                break;
            }
        }

        finish[i] = !has_allocation;
    }

    // Deadlock detection
    bool progress;

    do
    {
        progress = false;

        for (int i = 0; i < n; i++)
        {
            if (finish[i])
                continue;

            bool can_finish = true;

            for (int j = 0; j < m; j++)
            {
                if (request[i][j] > work[j])
                {
                    can_finish = false;
                    break;
                }
            }

            if (can_finish)
            {
                for (int j = 0; j < m; j++)
                {
                    work[j] += allocation[i][j];
                }

                finish[i] = true;
                progress = true;
            }
        }

    } while (progress);

    // Display result
    bool deadlock = false;

    printf("\nDeadlock Detection Result:\n");

    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            printf("P%d is deadlocked.\n", i);
            deadlock = true;
        }
    }

    if (!deadlock)
    {
        printf("No deadlock detected.\n");
        printf("All processes can complete.\n");
    }

    return 0;
}
