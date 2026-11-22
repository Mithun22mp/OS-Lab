
#include <stdio.h>

int main()
{
    int n;
    int at[20], bt[20], p[20];
    int ct[20], tat[20], wt[20];
    int current_time = 0;

    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    // Input arrival and burst times
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        p[i] = i + 1;
        if (at[i] < 0 || bt[i] <= 0)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }
    // Sort processes by arrival time
for (int i = 0; i < n - 1; i++)
{
    for (int j = 0; j < n - i - 1; j++)
    {
        if (at[j] > at[j + 1])
        {
            int temp;

            temp = at[j];
            at[j] = at[j + 1];
            at[j + 1] = temp;

            temp = bt[j];
            bt[j] = bt[j + 1];
            bt[j + 1] = temp;

            temp = p[j];
            p[j] = p[j + 1];
            p[j + 1] = temp;
        }
    }
}
    // FCFS scheduling
    for (int i = 0; i < n; i++)
    {
        if (current_time < at[i])
        {
            current_time = at[i];
        }

        current_time += bt[i];
        ct[i] = current_time;

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    // Display results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
       printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
       p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);

    return 0;
}
