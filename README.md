# MPI-CollectiveEmulation
Implementation of MPI collective communication functions using point-to-point communication methods for educational and optimization purposes

This repository contains custom implementations of various MPI collective communication functions using only point-to-point (PtoP) operations. This project serves as a demonstration of how underlying MPI collectives can be emulated with basic MPI communication primitives.

## Overview

The implemented functions include:
- `MPI_Allgather`: Gathers data from all processes and distributes it to all processes.
- `MPI_Allgatherv`: Gathers variable-sized data from all processes and distributes it to all.
- `MPI_Alltoall`: Each process sends data to all processes and receives data from all.
- `MPI_Alltoallv`: Generalized version of MPI_Alltoall that handles data of varying sizes.

These functions are fundamental in MPI programming but here are implemented in a way to understand the underlying mechanics using simpler point-to-point methods.

## Features

- **Custom MPI Functions**: Re-implementation of MPI's collective functions using only `MPI_Send` and `MPI_Recv`.
- **Performance Evaluation**: Analysis of the overhead and performance comparison with native MPI collectives.
- **Educational Tool**: Helps in understanding the internal workings and challenges of collective communication in distributed computing environments.

## Build and Run

Ensure you have an MPI library installed (e.g., MPICH, OpenMPI). Compile the code using the MPI compiler wrapper:

```bash
mpicc -o mpi_collector mpi_collector.c
mpiexec -n <number_of_processes> ./mpi_collector


