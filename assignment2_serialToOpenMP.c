#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000000

int main() {
    int arr[SIZE];
    long long sum_serial = 0, sum_parallel = 0;
    clock_t start, end;
    double serial_time, parallel_time;

    srand(0); // initialize random seed

    // Fill array with random numbers
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 100;

    // ---------------- SERIAL SUM ----------------
    start = clock();
    for (int i = 0; i < SIZE; i++)
        sum_serial += arr[i];
    end = clock();
    serial_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // ---------------- PARALLEL SUM (OpenMP) ----------------
    double p_start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum_parallel) num_threads(4)
    for (int i = 0; i < SIZE; i++)
        sum_parallel += arr[i];

    double p_end = omp_get_wtime();
    parallel_time = p_end - p_start;

    // Output Results
    printf("Serial Sum: %lld\n", sum_serial);
    printf("Parallel Sum: %lld\n", sum_parallel);
    printf("Execution Time (Serial): %f seconds\n", serial_time);
    printf("Execution Time (Parallel): %f seconds\n", parallel_time);

    return 0;
}
