
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL_READERS 5
#define TOTAL_WRITERS 2

int shared_data = 0;
int reader_count = 0;

sem_t mutex;
sem_t write_lock;

// Reader function
void *reader(void *arg)
{
    int id = *(int *)arg;

    // Protect reader_count
    sem_wait(&mutex);

    reader_count++;

    if (reader_count == 1)
    {
        sem_wait(&write_lock);
    }

    sem_post(&mutex);

    // Reading shared data
    printf("Reader %d is reading: %d\n", id, shared_data);
    sleep(1);

    sem_wait(&mutex);

    reader_count--;

    if (reader_count == 0)
    {
        sem_post(&write_lock);
    }

    sem_post(&mutex);

    return NULL;
}

// Writer function
void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&write_lock);

    shared_data++;

    printf("Writer %d is writing: %d\n", id, shared_data);
    sleep(1);

    sem_post(&write_lock);

    return NULL;
}

int main(void)
{
    pthread_t readers[TOTAL_READERS];
    pthread_t writers[TOTAL_WRITERS];

    int reader_ids[TOTAL_READERS];
    int writer_ids[TOTAL_WRITERS];

    // Initialize semaphores
    if (sem_init(&mutex, 0, 1) != 0 ||
        sem_init(&write_lock, 0, 1) != 0)
    {
        perror("sem_init");
        return 1;
    }

    printf("Readers-Writers Problem Started\n\n");

    // Create reader threads
    for (int i = 0; i < TOTAL_READERS; i++)
    {
        reader_ids[i] = i + 1;

        if (pthread_create(&readers[i], NULL,
                           reader, &reader_ids[i]) != 0)
        {
            perror("pthread_create reader");
            return 1;
        }
    }

    // Create writer threads
    for (int i = 0; i < TOTAL_WRITERS; i++)
    {
        writer_ids[i] = i + 1;

        if (pthread_create(&writers[i], NULL,
                           writer, &writer_ids[i]) != 0)
        {
            perror("pthread_create writer");
            return 1;
        }
    }

    // Wait for all readers
    for (int i = 0; i < TOTAL_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writers
    for (int i = 0; i < TOTAL_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    printf("\nFinal shared data: %d\n", shared_data);
    printf("Readers-Writers Problem Completed\n");

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
