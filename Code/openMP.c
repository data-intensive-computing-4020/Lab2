#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "omp.h"

// Set the matrix sixe, number of threads and chunk size
const int MATRIX_SIZE = 8192;
const int NUMBER_OF_THREADS = 128;
const int CHUNK_SIZE = 2;

//iterate through the array and print the matrix in matrix readable fashion
void printSquareMatrixInt(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d \t", matrix[i][j]);
        }
        printf("\n");
    }
}


void naiveSolutionInt(int** matrix) {
    int temp;
    for (int i = 0; i < MATRIX_SIZE - 1; i++) {
        for (int j = i + 1; j < MATRIX_SIZE; j++) {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

void openMPsolution(int** matrix) {
    int i, j, temp;
    #pragma omp parallel shared(matrix) private(temp, i, j)
    {
        #pragma omp for schedule(dynamic, CHUNK_SIZE)  nowait
        for (i = 0; i < MATRIX_SIZE - 1; i++) {
            for (j = i + 1; j < MATRIX_SIZE; j++) {
                temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
    }
}

int main() {
    omp_set_num_threads(NUMBER_OF_THREADS);

    // Create dynamic array and populate it
    int ** matrix;
    matrix = malloc(MATRIX_SIZE * sizeof(int *));
    
    for(int i = 0; i < MATRIX_SIZE; i++)
        matrix[i] = (int *)malloc(MATRIX_SIZE * sizeof(int));
    
    int count = 0;    
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = count;   
            count++;
        }
    }


    printf("Size %c %c: %d\n", ' ',' ', MATRIX_SIZE);
    printf("Threads  %c: %d\n", ' ', NUMBER_OF_THREADS );
    double dtime;
   
    // printSquareMatrixInt(MATRIX_SIZE, matrix);
    dtime = omp_get_wtime();
    naiveSolutionInt(matrix);
	dtime = omp_get_wtime() - dtime;
	printf("Naive %c %c: %f\n", ' ',' ', dtime);
   


   
    // printf(" \n --------------------------------------- \n");
    // printSquareMatrixInt(MATRIX_SIZE, matrix);
    dtime = omp_get_wtime();
    openMPsolution(matrix);
	dtime = omp_get_wtime() - dtime;
	printf("Parallel : %f\n", dtime);

    // printf(" \n --------------------------------------- \n");
    // printSquareMatrixInt(MATRIX_SIZE, matrix);

}

