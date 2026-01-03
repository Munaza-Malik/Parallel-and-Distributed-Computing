#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

int main() {
    int arr[SIZE];
    long long sum = 0;
    clock_t start, end;
    double cpu_time_used;

    srand(0); // initialize random seed

    // Fill array with random numbers
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 100;

    // Start timing
    start = clock();

    // Serial sum
    for (int i = 0; i < SIZE; i++)
        sum += arr[i];

    // End timing
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Serial Sum: %lld\n", sum);
    printf("Execution Time (Serial): %f seconds\n", cpu_time_used);

    return 0;
}
