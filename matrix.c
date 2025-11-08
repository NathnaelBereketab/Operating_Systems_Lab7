#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 20         
#define NUM_THREADS 10 // total threads (each handles 2 rows)

int matA[MAX][MAX];
int matB[MAX][MAX];
int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX];
int matProductResult[MAX][MAX];

// Structure to pass range of rows to each thread
typedef struct {
    int startRow;
    int endRow;
} ThreadArgs;

// Fill a matrix with random integers between 1 and 10
void fillMatrix(int matrix[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
}

// Print a matrix neatly
void printMatrix(int matrix[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Thread function: compute Sum, Difference, and Product for assigned rows
void* computeOperations(void* args) {
    ThreadArgs* data = (ThreadArgs*)args;
    int start = data->startRow;
    int end = data->endRow;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < MAX; j++) {
            // Sum
            matSumResult[i][j] = matA[i][j] + matB[i][j];

            // Difference
            matDiffResult[i][j] = matA[i][j] - matB[i][j];

            // Product (Dot product logic for row i, col j)
            int sum = 0;
            for (int k = 0; k < MAX; k++) {
                sum += matA[i][k] * matB[k][j];
            }
            matProductResult[i][j] = sum;
        }
    }

    free(data);
    return NULL;
}

int main() {
    srand(time(0)); // seed random number generator

    // 1. Fill the matrices (A and B)
    fillMatrix(matA);
    fillMatrix(matB);

    // 2. Print initial matrices
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);

    // 3. Create pthreads for computation
    pthread_t threads[NUM_THREADS];
    int rowsPerThread = MAX / NUM_THREADS; // 20/10 = 2 rows per thread

    for (int i = 0; i < NUM_THREADS; i++) {
        ThreadArgs* args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        args->startRow = i * rowsPerThread;
        args->endRow = (i + 1) * rowsPerThread;
        pthread_create(&threads[i], NULL, computeOperations, args);
    }

    // 4. Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 5. Print the resulting matrices
    printf("Result Matrices:\n\n");
    printf("Sum of Matrices:\n");
    printMatrix(matSumResult);

    printf("Difference of Matrices:\n");
    printMatrix(matDiffResult);

    printf("Product of Matrices:\n");
    printMatrix(matProductResult);

    return 0;
}
