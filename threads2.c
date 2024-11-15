#include <stdio.h>
#include <pthread.h>

void* addition(void* arg) {
    int a = 10, b = 20;
    int sum = a + b;
    printf("Thread 1: Addition result = %d, Thread ID = %lu\n", sum, pthread_self());
    return NULL;
}

void* odd_or_even(void* arg) {
    int num = 15;
    if (num % 2 == 0) {
        printf("Thread 2: %d is even, Thread ID = %lu\n", num, pthread_self());
    } else {
        printf("Thread 2: %d is odd, Thread ID = %lu\n", num, pthread_self());
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, addition, NULL);
    pthread_create(&thread2, NULL, odd_or_even, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
