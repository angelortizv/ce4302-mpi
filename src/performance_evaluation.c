/*
 * File: performance_evaluation.c
 * Author: @angelortizv, @jesquivel48
 * Date: November 12, 2023
 * Description: This program measures the communication time between two MPI processes (nodes) for messages of varying sizes. 
 * The communication is done using MPI_Send and MPI_Recv functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_MSG_SIZE 1000000

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This program requires at least two MPI nodes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    double start_time, end_time;

    // Variable-sized message loop
    for (int msg_size = 1; msg_size <= MAX_MSG_SIZE; msg_size *= 10) {
        char* message = (char*)malloc(msg_size * sizeof(char));

        if (rank == 0) {
            // Initialize the message (just for this example)
            for (int i = 0; i < msg_size; i++) {
                message[i] = 'A';
            }

            // Record the start time
            start_time = MPI_Wtime();

            // Send the message from node 0 to node 1
            MPI_Send(message, msg_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        } else if (rank == 1) {
            // Receive the message on node 1
            MPI_Recv(message, msg_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Record the end time
            end_time = MPI_Wtime();

            // Print results on node 1
            printf("Message size: %d bytes, Communication time: %f seconds\n", msg_size, end_time - start_time);
        }

        free(message);
    }

    MPI_Finalize();

    return 0;
}
