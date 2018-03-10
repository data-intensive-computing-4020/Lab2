#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

// Enter the matrix size and number of threads here
const int MATRIX_SIZE = 8192;
const int NUMBER_OF_THREADS = 128;

// Struct containing information that we need to pass into the transposition function
struct ThreadInfo {
    int **matrix;
    int startIndex;
    int endIndex;
};

void *transposePthread(void *args) {
    struct ThreadInfo *threadInfo;
    threadInfo = (struct ThreadInfo *) args;
    int temp;

    for (int i = threadInfo->startIndex; i < threadInfo->endIndex; i++) {
        for (int j = i + 1; j < MATRIX_SIZE; j++) {
            temp = threadInfo->matrix[i][j];
            threadInfo->matrix[i][j] = threadInfo->matrix[j][i];
            threadInfo->matrix[j][i] = temp;
        }
    }
    pthread_exit(NULL);
}

void naiveSolutionInt(int **matrix) {
    int temp;
    for (int i = 0; i < MATRIX_SIZE - 1; i++) {
        for (int j = i + 1; j < MATRIX_SIZE; j++) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

void printSquareMatrixInt(int n, int **A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d \t", A[i][j]);
        }
        printf("\n");
    }
}


int main() {



    int **matrix;
    matrix = malloc(MATRIX_SIZE * sizeof(int *));

    for (int i = 0; i < MATRIX_SIZE; i++)
        matrix[i] = (int *) malloc(MATRIX_SIZE * sizeof(int));

    int count = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = count;
            count++;
        }
    }


    double matrixSize = MATRIX_SIZE;

    //printSquareMatrixInt(MATRIX_SIZE, matrix);
    struct ThreadInfo *threadInfo;
    double time, timeTaken;
    time = omp_get_wtime();
    pthread_t threads[NUMBER_OF_THREADS];
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        threadInfo = malloc(sizeof(struct temp *));
        threadInfo->matrix = matrix;
        threadInfo->startIndex = ( matrixSize/ NUMBER_OF_THREADS) * i;
        threadInfo->endIndex = (matrixSize / NUMBER_OF_THREADS) * (i + 1);
        pthread_create(&threads[i], NULL, transposePthread, (void *) threadInfo);
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    //printSquareMatrixInt(MATRIX_SIZE, matrix);
    printf("Size %c %c: %d\n", ' ',' ', MATRIX_SIZE);
    printf("Threads  %c: %d\n", ' ', NUMBER_OF_THREADS );
    timeTaken = omp_get_wtime() - time;
    printf("Pthreads: %c %c: %f\n", ' ', ' ', timeTaken);


    time = omp_get_wtime();
    naiveSolutionInt(matrix);
    timeTaken = omp_get_wtime() - time;
    printf("Naive : %f\n", timeTaken);

//    printSquareMatrixInt(MATRIX_SIZE, matrix);

    return 0;
}

