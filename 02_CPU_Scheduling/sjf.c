
#include <stdio.h>

#define MAX 20

int main()
{
    int n;
    int at[MAX], bt[MAX], p[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int completed[MAX] = {0};

    int current_time = 0;
    int completed_count = 0;

    float avg_tat = 0, avg_wt = 0;

    printf("===== SJF CPU SCHEDULING =====\n");

    printf("Enter number of processes: ");

    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    // Input
    for (int i = 0; i < n; i++)
    {
        printf("Enter AT and BT for P%d: ", i + 1);

        if (scanf("%d %d", &at[i], &bt[i]) != 2 ||
            at[i] < 0 || bt[i] <= 0)
        {
            printf("Invalid input.\n");
            return 1;
        }

        p[i] = i + 1;
    }

    // Non-preemptive SJF
    while (completed_count < n)
    {
        int shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && at[i] <= current_time)
            {
                if (shortest == -1 ||
                    bt[i] < bt[shortest] ||
                    (bt[i] == bt[shortest] &&
                     at[i] < at[shortest]) ||
                    (bt[i] == bt[shortest] &&
                     at[i] == at[shortest] &&
                     p[i] < p[shortest]))
                {
                    shortest = i;
                }
            }
        }

        // CPU idle time
        if (shortest == -1)
        {
            current_time++;
            continue;
        }

        current_time += bt[shortest];

        ct[shortest] = current_time;
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];

        avg_tat += tat[shortest];
        avg_wt += wt[shortest];

        completed[shortest] = 1;
        completed_count++;
    }

    // Results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
