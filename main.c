/*
 * File: main.c
 * Author: @angelortizv, @jesquivel48
 * Date: November 14, 2023
 * Description: The main.c file is a C program utilizing the MPI library to compile and execute the source file sum_matrices.c
 *              To run the program, open a terminal in the main directory, execute the command mpicc -o main main.c, and then run the compiled program with ./main.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int choice;

    printf("Choose a program to execute:\n");
    printf("1. Sum Matrices\n");
    printf("2. Performance Evaluation\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        system("mpicc -o src/output/sum_matrices src/sum_matrices.c");
        //system("mpirun -np 3 src/output/sum_matrices");
        system("mpirun -np 3 -H manager,worker1,worker2 src/output/sum_matrices");
    } else if (choice == 2) {
        system("mpicc -o src/output/performance_evaluation src/performance_evaluation.c");
        system("mpirun -np 3 src/output/performance_evaluation");
    } else {
        printf("Invalid choice. Please enter 1 or 2.\n");
    }

    return 0;
}
