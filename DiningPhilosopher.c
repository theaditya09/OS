#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;

void *philosopher(void *arg) {
    int id = *((int *)arg);
    int leftFork = id;
    int rightFork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        pthread_mutex_lock(&mutex);

        sem_wait(&forks[leftFork]);
        sem_wait(&forks[rightFork]);

        pthread_mutex_unlock(&mutex);

        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        sem_post(&forks[leftFork]);
        sem_post(&forks[rightFork]);

        printf("Philosopher %d has finished eating and put down forks %d and %d.\n", id, leftFork, rightFork);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherIds[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        philosopherIds[i] = i;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopherIds[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}
