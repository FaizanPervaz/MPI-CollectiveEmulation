#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int my_MPI_Allgather(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            MPI_Send(sendbuf, sendcount, sendtype, i, 0, comm);
        } else {
            for (int j = 0; j < size; j++) {
                if (j != rank) {
                    MPI_Recv(recvbuf + j * recvcount * sizeof(recvtype), recvcount, recvtype, j, 0, comm, MPI_STATUS_IGNORE);
                }
            }
        }
    }

    return MPI_SUCCESS;
}

int my_MPI_Allgatherv(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int* recvcounts, int* displs, MPI_Datatype recvtype, MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            MPI_Send(sendbuf, sendcount, sendtype, i, 0, comm);
        } else {
            for (int j = 0; j < size; j++) {
                if (j != rank) {
                    MPI_Recv(recvbuf + displs[j] * sizeof(recvtype), recvcounts[j], recvtype, j, 0, comm, MPI_STATUS_IGNORE);
                }
            }
        }
    }

    return MPI_SUCCESS;
}

int my_MPI_Alltoall(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    for (int i = 0; i < size; i++) {
        MPI_Sendrecv(sendbuf + i * sendcount * sizeof(sendtype), sendcount, sendtype, i, 0, recvbuf + rank * recvcount * sizeof(recvtype), recvcount, recvtype, i, 0, comm, MPI_STATUS_IGNORE);
    }

    return MPI_SUCCESS;
}

int my_MPI_Alltoallv(void* sendbuf, int* sendcounts, int* sdispls, MPI_Datatype sendtype, void* recvbuf, int* recvcounts, int* rdispls, MPI_Datatype recvtype, MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    for (int i = 0; i < size; i++) {
        MPI_Sendrecv(sendbuf + sdispls[i] * sizeof(sendtype), sendcounts[i], sendtype, i, 0, recvbuf + rdispls[i] * sizeof(recvtype), recvcounts[i], recvtype, i, 0, comm, MPI_STATUS_IGNORE);
    }

    return MPI_SUCCESS;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Example usage of MPI_Allgather
    int sendbuf = rank;
    int recvbuf[size];
    my_MPI_Allgather(&sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);
    printf("MPI_Allgather - Process %d received: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    // Example usage of MPI_Allgatherv
    int recvcounts[size];
    int displs[size];
    for (int i = 0; i < size; i++) {
        recvcounts[i] = 1;
        displs[i] = i;
    }
    my_MPI_Allgatherv(&sendbuf, 1, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, MPI_COMM_WORLD);
    printf("MPI_Allgatherv - Process %d received: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    // Example usage of MPI_Alltoall
    my_MPI_Alltoall(&sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);
    printf("MPI_Alltoall - Process %d received: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    // Example usage of MPI_Alltoallv
    int sendcounts[size];
    for (int i = 0; i < size; i++) {
        sendcounts[i] = 1;
        recvcounts[i] = 1;
        displs[i] = i;
    }
    my_MPI_Alltoallv(&sendbuf, sendcounts, displs, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, MPI_COMM_WORLD);
    printf("MPI_Alltoallv - Process %d received: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

