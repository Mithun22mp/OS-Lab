
#include <stdio.h>

#define MAX 100

void displayResult(const char *name, int faults, int hits)
{
    printf("\n%s\n", name);
    printf("Page Faults: %d\n", faults);
    printf("Page Hits  : %d\n", hits);
}

void fifo(int pages[], int n, int frames)
{
    int memory[MAX];
    int pointer = 0;
    int faults = 0, hits = 0;

    for (int i = 0; i < frames; i++)
        memory[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < frames; j++)
        {
            if (memory[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
            hits++;
        else
        {
            memory[pointer] = pages[i];
            pointer = (pointer + 1) % frames;
            faults++;
        }
    }

    displayResult("FIFO PAGE REPLACEMENT", faults, hits);
}

void lru(int pages[], int n, int frames)
{
    int memory[MAX];
    int lastUsed[MAX];
    int faults = 0, hits = 0;

    for (int i = 0; i < frames; i++)
    {
        memory[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int found = -1;

        for (int j = 0; j < frames; j++)
        {
            if (memory[j] == pages[i])
            {
                found = j;
                break;
            }
        }

        if (found != -1)
        {
            hits++;
            lastUsed[found] = i;
        }
        else
        {
            int replace = 0;

            for (int j = 0; j < frames; j++)
            {
                if (memory[j] == -1)
                {
                    replace = j;
                    break;
                }

                if (lastUsed[j] < lastUsed[replace])
                    replace = j;
            }

            memory[replace] = pages[i];
            lastUsed[replace] = i;
            faults++;
        }
    }

    displayResult("LRU PAGE REPLACEMENT", faults, hits);
}

int main(void)
{
    int n, frames;
    int pages[MAX];

    printf("PAGE REPLACEMENT ALGORITHMS\n");

    printf("Enter number of page references: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Invalid number of page references.\n");
        return 1;
    }

    printf("Enter page reference string:\n");

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &pages[i]) != 1 || pages[i] < 0)
        {
            printf("Invalid page number.\n");
            return 1;
        }
    }

    printf("Enter number of frames: ");
    if (scanf("%d", &frames) != 1 || frames < 1 || frames > MAX)
    {
        printf("Invalid number of frames.\n");
        return 1;
    }

    fifo(pages, n, frames);
    lru(pages, n, frames);

    return 0;
}
