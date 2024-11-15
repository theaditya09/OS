#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

char str[] = "Multithreading in C is powerful for parallel execution!";

void* count_vowels(void* arg) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
    }
    printf("Thread for vowels : Vowels count = %d, Thread ID = %lu\n", count, pthread_self());
    return NULL;
}

void* count_consonants(void* arg) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        char ch = tolower(str[i]);
        if (isalpha(ch) && !(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')) {
            count++;
        }
    }
    printf("Thread for consonants : Consonants count = %d, Thread ID = %lu\n", count, pthread_self());
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, count_vowels, NULL);
    pthread_create(&thread2, NULL, count_consonants, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
