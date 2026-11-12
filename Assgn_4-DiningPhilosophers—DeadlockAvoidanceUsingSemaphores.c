
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 3; i++)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&room);

        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        sem_post(&room);
    }

    return NULL;
}

int main()
{
    pthread_t thread[N];
    int id[N];

    sem_init(&room, 0, 4);

    for (int i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&thread[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(thread[i], NULL);
    }


    printf("All philosophers finished eating.\n");

    return 0;
}