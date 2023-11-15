/*
 * File: sum_matrices.c
 * Author: @angelortizv, @jesquivel48
 * Date: November 12, 2023
 * Description: This program performs matrix addition using MPI (Message Passing Interface) for parallel processing. 
 * It utilizes multiple processes to distribute the computation of the matrix addition across different nodes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 500  // Size of the matrices
#define ANSI_COLOR_RED     "\x1b[31m"

void fillMatriz(int matriz[N][N]) {
    // Fill the matrix with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = rand() % 10;
        }
    }
}

void printMatriz(int matriz[N][N]) {
    // Print the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This program requires at least two MPI nodes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Create matrices A and B
    int A[N][N], B[N][N];

    if (rank == 0) {
        fillMatriz(A);
        fillMatriz(B);

        // printf("Matrix A:\n");
        // printMatriz(A);

        // printf("Matrix B:\n");
        // printMatriz(B);
    }

    // Broadcast matrices A and B to all nodes
    MPI_Bcast(A, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the portion of the matrix that each node will sum
    int chunkSize = N / size;
    int inicio = rank * chunkSize;
    int fin = (rank + 1) * chunkSize;

    // Perform local matrix addition on each node
    for (int i = inicio; i < fin; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] += B[i][j];
        }
    }

    // Print information about the local sum on each node
    printf(ANSI_COLOR_RED "Node %d: Local sum of rows %d to %d\n", rank, inicio, fin - 1);

    // Gather results back to node 0
    MPI_Gather(A + inicio, chunkSize * N, MPI_INT, A, chunkSize * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the result on node 0
    // if (rank == 0) {
    //     printf("Resulting matrix:\n");
    //     printMatriz(A);
    // }

    MPI_Finalize();

    return 0;
}
