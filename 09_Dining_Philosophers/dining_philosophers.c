
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking.\n", id);
    sleep(1);

    // Allow at most four philosophers to compete
    sem_wait(&room);

    // Pick up left fork
    sem_wait(&forks[id]);

    printf("Philosopher %d picked up left fork.\n", id);

    // Pick up right fork
    sem_wait(&forks[(id + 1) % N]);

    printf("Philosopher %d picked up right fork.\n", id);

    // Eat
    printf("Philosopher %d is eating.\n", id);
    sleep(1);

    // Put down forks
    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % N]);

    printf("Philosopher %d finished eating.\n", id);

    // Leave dining room
    sem_post(&room);

    return NULL;
}

int main(void)
{
    pthread_t philosophers[N];
    int ids[N];

    // Initialize room semaphore to 4
    if (sem_init(&room, 0, N - 1) != 0)
    {
        perror("sem_init room");
        return 1;
    }

    // Initialize fork semaphores
    for (int i = 0; i < N; i++)
    {
        if (sem_init(&forks[i], 0, 1) != 0)
        {
            perror("sem_init fork");
            return 1;
        }
    }

    printf("Dining Philosophers Problem Started.\n\n");

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        ids[i] = i;

        if (pthread_create(&philosophers[i], NULL,
                           philosopher, &ids[i]) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    // Wait for all philosophers
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    printf("\nAll philosophers finished eating.\n");

    // Destroy semaphores
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&forks[i]);
    }

    sem_destroy(&room);

    return 0;
}
