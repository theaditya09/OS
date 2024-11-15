#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, writeBlock;
int sharedData = 0;  
int readCount = 0;

void *reader(void *arg) {
    int readerId = *((int *)arg);

    sem_wait(&mutex);
    readCount++;
    if (readCount == 1) {
        sem_wait(&writeBlock);
    }
    sem_post(&mutex);

    printf("Reader %d reads shared data: %d\n", readerId, sharedData);
    sleep(1);

    sem_wait(&mutex);
    readCount--;
    if (readCount == 0) {
        sem_post(&writeBlock);
    }
    sem_post(&mutex);
    return NULL;
}

void *writerIncrement(void *arg) {
    int writerId = *((int *)arg);

    sem_wait(&writeBlock);
    sharedData++;
    printf("Writer %d increments shared data to: %d\n", writerId, sharedData);
    sleep(1);
    sem_post(&writeBlock);
    return NULL;
}

void *writerDecrement(void *arg) {
    int writerId = *((int *)arg);

    sem_wait(&writeBlock);
    sharedData--;
    printf("Writer %d decrements shared data to: %d\n", writerId, sharedData);
    sleep(1);
    sem_post(&writeBlock);
    return NULL;
}

int main() {
    pthread_t r1, r2, w1, w2;
    int r1Id = 1, r2Id = 2, w1Id = 1, w2Id = 2;

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    pthread_create(&r1, NULL, reader, &r1Id);
    pthread_create(&w1, NULL, writerDecrement, &w1Id);
    pthread_create(&r2, NULL, reader, &r2Id);
    pthread_create(&w2, NULL, writerIncrement, &w2Id);

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}
