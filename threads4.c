#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 1000000

int array[ARRAY_SIZE];
long long sum_single = 0;
long long sum_multi = 0;

void* sum_partial(void* arg) {
    int start = ((int*)arg)[0];
    int end = ((int*)arg)[1];
    long long partial_sum = 0;

    for (int i = start; i < end; i++) {
        partial_sum += array[i];
    }

    sum_multi += partial_sum;
    return NULL;
}

void initialize_array() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }
}

void sum_single_thread() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum_single += array[i];
    }
}

int main() {
    clock_t start, end;
    pthread_t threads[4];
    int thread_args[4][2];

    initialize_array();

    start = clock();
    sum_single_thread();
    end = clock();
    double single_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    int segment_size = ARRAY_SIZE / 4;

    for (int i = 0; i < 4; i++) {
        thread_args[i][0] = i * segment_size;
        thread_args[i][1] = (i == 3) ? ARRAY_SIZE : (i + 1) * segment_size;
        pthread_create(&threads[i], NULL, sum_partial, (void*)thread_args[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    end = clock();
    double multi_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Single-threaded sum: %lld, Time: %f seconds\n", sum_single, single_time);
    printf("Multi-threaded sum (4 threads): %lld, Time: %f seconds\n", sum_multi, multi_time);

    return 0;
}
