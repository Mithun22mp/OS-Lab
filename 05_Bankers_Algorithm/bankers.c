
#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main(void)
{
    int n, m;

    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int available[MAX_R];

    int work[MAX_R];
    int safe_sequence[MAX_P];
    bool finish[MAX_P] = {false};

    int count = 0;

    printf("BANKER'S ALGORITHM\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    if (n < 1 || n > MAX_P || m < 1 || m > MAX_R)
    {
        printf("Invalid number of processes or resources.\n");
        return 1;
    }

    // Input Allocation matrix
    printf("\nEnter Allocation Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);

            if (allocation[i][j] < 0)
            {
                printf("Invalid allocation value.\n");
                return 1;
            }
        }
    }

    // Input Maximum matrix
    printf("\nEnter Maximum Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);

            if (max[i][j] < allocation[i][j])
            {
                printf("Maximum cannot be less than allocation.\n");
                return 1;
            }
        }
    }

    // Input Available resources
    printf("\nEnter Available Resources:\n");

    for (int j = 0; j < m; j++)
    {
        scanf("%d", &available[j]);

        if (available[j] < 0)
        {
            printf("Invalid available resource value.\n");
            return 1;
        }
    }

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display Need matrix
    printf("\nNeed Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    // Initialize Work
    for (int j = 0; j < m; j++)
    {
        work[j] = available[j];
    }

    // Find safe sequence
    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (finish[i])
                continue;

            bool can_execute = true;

            for (int j = 0; j < m; j++)
            {
                if (need[i][j] > work[j])
                {
                    can_execute = false;
                    break;
                }
            }

            if (can_execute)
            {
                for (int j = 0; j < m; j++)
                {
                    work[j] += allocation[i][j];
                }

                safe_sequence[count++] = i;
                finish[i] = true;
                found = true;
            }
        }

        if (!found)
            break;
    }

    // Display result
    if (count == n)
    {
        printf("\nSystem is in SAFE STATE.\n");

        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safe_sequence[i]);

            if (i < n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is in UNSAFE STATE.\n");
        printf("No safe sequence exists.\n");
    }

    return 0;
}
