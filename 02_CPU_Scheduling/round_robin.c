
#include <stdio.h>

#define MAX 50

int main(void)
{
    int n, quantum;
    int burst[MAX], remaining[MAX];
    int completion[MAX], turnaround[MAX], waiting[MAX];
    int time = 0;
    int completed = 0;

    float total_tat = 0, total_wt = 0;

    printf("ROUND ROBIN CPU SCHEDULING\n");

    printf("Enter number of processes: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter burst time for each process:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);

        if (scanf("%d", &burst[i]) != 1 || burst[i] <= 0)
        {
            printf("Invalid burst time.\n");
            return 1;
        }

        remaining[i] = burst[i];
    }

    printf("Enter time quantum: ");

    if (scanf("%d", &quantum) != 1 || quantum <= 0)
    {
        printf("Invalid time quantum.\n");
        return 1;
    }

    // Round Robin scheduling
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                if (remaining[i] > quantum)
                {
                    time += quantum;
                    remaining[i] -= quantum;
                }
                else
                {
                    time += remaining[i];
                    remaining[i] = 0;

                    completion[i] = time;
                    completed++;
                }
            }
        }
    }

    // Calculate TAT and WT
    for (int i = 0; i < n; i++)
    {
        turnaround[i] = completion[i];
        waiting[i] = turnaround[i] - burst[i];

        total_tat += turnaround[i];
        total_wt += waiting[i];
    }

    // Display results
    printf("\nPROCESS\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               burst[i],
               completion[i],
               turnaround[i],
               waiting[i]);
    }

    printf("\nAverage Turnaround Time: %.2f",
           total_tat / n);

    printf("\nAverage Waiting Time: %.2f\n",
           total_wt / n);

    return 0;
}
