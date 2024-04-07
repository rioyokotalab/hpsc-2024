#include <cstdio>
#include <cmath>
#include <vector>
#include "mpi.h"

int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  const int N = 10000000;
  std::vector<int> send(N);
  std::vector<int> recv(N);
  for(int i=0; i<N; i++) {
    send[i] = rank+10*i;
    recv[i] = 0;
  }
  int send_to = (rank - 1 + size) % size;
  MPI_Win win;
  MPI_Win_create(&recv[0], N*sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  MPI_Win_fence(0, win);
  MPI_Put(&send[0], N, MPI_INT, send_to, 0, N, MPI_INT, win);
  MPI_Win_fence(0, win);
  MPI_Win_free(&win);
  MPI_Finalize();
}
