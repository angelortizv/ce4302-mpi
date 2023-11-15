# Parallel Matrix Addition and Performance Evaluation

## Description

This project consists of two programs implemented in C using the MPI (Message Passing Interface) standard for parallel processing:

1. **sum_matrices.c**: Performs the addition of two matrices using MPI to distribute the computation of the sum across different nodes.

2. **performance_evaluation.c**: Measures the communication time between two MPI nodes for messages of different sizes.

## Instructions to Run

### Prerequisites

1. Make sure to have MPI installed on your system. You can install it using:

```bash
sudo apt update
sudo apt install openmpi-bin
sudo apt install libopenmpi-dev
mpicc --version
```

2. Create a MPI Cluster

3 Virtual Machines with Ubuntu 18.04.06 were created for this task using VirtualBox.

Follow these instructions to create the MPI CLUSTER:
https://www.geeksforgeeks.org/creating-an-mpi-cluster/


### Compile and Execute

1. Clone this repository to your local machine.

2. Navigate to the project directory:

```bash
cd ce4302-mpi
```

3. Compile the code using `mpicc`:

```bash
mpicc -o main sum_matrices.c
```

4. Run the program:

```bash
./main
```

5. Choose one of the options:
   - `1` to execute the matrix addition.
   - `2` to view the performance evaluation for different message sizes.

### Results

#### Execution of `sum_matrices.c`

The program performs the addition of two matrices by distributing the computation across different nodes. The initial matrices are printed to the `initial.txt` file, and the result is printed to the `results.txt` file.

![sum_matrices](https://github.com/angelortizv/ce4302-mpi/assets/18412939/50029337-4157-40cb-a279-eedb4d594711)

![files](https://github.com/angelortizv/ce4302-mpi/assets/18412939/e769f9db-81f5-49fb-9a33-01eecef7efa0)

#### Execution of `performance_evaluation.c`

The program measures the communication time between two MPI nodes for messages of different sizes. The results are displayed in the console, providing information about the communication time for each message size.

![performance_evaluation](https://github.com/angelortizv/ce4302-mpi/assets/18412939/7b7feb9a-9e9f-4c0f-87ee-1edbbcb9ba16)
