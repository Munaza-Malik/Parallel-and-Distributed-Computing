#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10000
int arr[SIZE];
long long total_sum = 0;
int num_threads;
pthread_mutex_t lock; 

// Function executed by each thread
void* partial_sum(void* arg) {
    int thread_part = *(int*)arg;
    int start = thread_part * (SIZE / num_threads);
    int end = (thread_part + 1) * (SIZE / num_threads);
    long long local_sum = 0;

    for (int i = start; i < end; i++)
        local_sum += arr[i];

    pthread_mutex_lock(&lock);
    total_sum += local_sum;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    srand(0);
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 100;

    int threads_list[] = {4, 5, 10};

    for (int t = 0; t < 3; t++) {
        num_threads = threads_list[t];
        pthread_t threads[num_threads];
        int thread_ids[num_threads];
        total_sum = 0;

        clock_t start = clock();

        pthread_mutex_init(&lock, NULL);
        for (int i = 0; i < num_threads; i++) {
            thread_ids[i] = i;
            pthread_create(&threads[i], NULL, partial_sum, &thread_ids[i]);
        }

        for (int i = 0; i < num_threads; i++)
            pthread_join(threads[i], NULL);

        pthread_mutex_destroy(&lock);

        clock_t end = clock();
        double parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Threads: %d , Parallel Sum: %lld , Time: %f sec\n",
               num_threads, total_sum, parallel_time);
    }

    return 0;
}


