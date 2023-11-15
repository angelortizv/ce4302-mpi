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
#include <time.h>

#define N 500  // Size of the matrices
#define ANSI_COLOR_RED "\x1b[31m"

void fillMatriz(int matriz[N][N]) {
    // Fill the matrix with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = rand() % 10;
        }
    }
}

void printMatriz(FILE *file, int matriz[N][N]) {
    // Print the matrix to file
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", matriz[i][j]);
        }
        fprintf(file, "\n");
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This program requires at least two MPI nodes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Create matrices A and B
    int A[N][N], B[N][N], result[N][N];

    if (rank == 0) {
        fillMatriz(A);
        fillMatriz(B);
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
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    // Get the processor name
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf(ANSI_COLOR_RED "\nProcess %d of %d on %s\n", rank, size, processor_name);

    printf("Node %d: Local sum of rows %d to %d\n", rank, inicio, fin - 1);

    // Gather results back to node 0
    MPI_Gather(result + inicio, chunkSize * N, MPI_INT, result, chunkSize * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Wait for all processes to synchronize
    MPI_Barrier(MPI_COMM_WORLD);

    // Node 0 writes the matrices to a file
    if (rank == 0) {
        FILE *file = fopen("./src/files/results.txt", "w");
        if (file == NULL) {
            perror("Error opening file");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        fprintf(file, "Matriz A:\n");
        printMatriz(file, A);
        fprintf(file, "\nMatriz B:\n");
        printMatriz(file, B);
        fprintf(file, "\nResult:\n");
        printMatriz(file, result);

        fclose(file);
    }

    MPI_Finalize();

    return 0;
}
