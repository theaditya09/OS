#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* print_name(void* arg) {
    char* name = (char*)arg;
    printf("Thread: Name = %s\n", name);
    printf("Thread: Thread ID = %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t thread;
    char name[] = "Aditya Raj Pandit";
    char reg_no[] = "23BRS1157";

    pthread_create(&thread, NULL, print_name, (void*)name);

    printf("Main Thread: Registration No. = %s\n", reg_no);
    printf("Main Thread: Thread ID = %lu\n", pthread_self());

    pthread_join(thread, NULL);

    return 0;
}
