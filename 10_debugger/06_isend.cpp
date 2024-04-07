#include <cstdio>
#include "mpi.h"

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  const int N = 4;
  int send[N], recv[N];
  for(int i=0; i<N; i++) {
    send[i] = rank+10*i;
    recv[i] = 0;
  }
  int recv_from = (rank + 1) % size;
  int send_to = (rank - 1 + size) % size;
  MPI_Request request[2];
  MPI_Isend(send, N, MPI_INT, send_to, 0, MPI_COMM_WORLD, &request[0]);
  MPI_Irecv(recv, N, MPI_INT, recv_from, 0, MPI_COMM_WORLD, &request[1]);
  printf("rank%d: send=[%d %d %d %d], recv=[%d %d %d %d]\n",rank,
         send[0],send[1],send[2],send[3],recv[0],recv[1],recv[2],recv[3]);
  MPI_Finalize();
}
