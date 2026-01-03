#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Different input sizes
    long sizes[] = {100000, 500000, 1000000, 5000000,
                    10000000, 50000000, 100000000,
                    500000000, 1000000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    // Seed random number generator
    srand(time(0));

    for (int s = 0; s < numSizes; s++) {
        long n = sizes[s];

        // Record start time
        clock_t start = clock();

        // Allocate memory for float array
        float *arr = (float *)malloc(n * sizeof(float));
        if (arr == NULL) {
            printf("Memory allocation failed for size %ld\n", n);
            continue;
        }

        // Fill array with random floats between 0 and 1
        for (long i = 0; i < n; i++) {
            arr[i] = (float)rand() / RAND_MAX;  
        }

        // Record end time
        clock_t end = clock();

        // Calculate elapsed time in seconds
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Input Size: %ld -> Execution Time: %f sec\n", n, time_taken);

        free(arr); // Free allocated memory
    }

    return 0;
}