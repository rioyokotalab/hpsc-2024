#include <mpi.h>
#include <cstdio>

__global__ void GPU_Kernel() {
  printf(" GPU block  : %d / %d  GPU thread : %d / %d\n",
         blockIdx.x, gridDim.x, threadIdx.x, blockDim.x);
}

int main(int argc, char **argv) {
  char hostname[256];
  int mpisize, mpirank, gpusize, gpurank, len;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpisize);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
  MPI_Get_processor_name(hostname, &len);
  cudaGetDeviceCount(&gpusize);
  cudaSetDevice(mpirank % gpusize);
  cudaGetDevice(&gpurank);
  for (int irank=0; irank<mpisize; irank++) {
    MPI_Barrier(MPI_COMM_WORLD);
    if (mpirank == irank) {
      printf("Hostname    : %s\n", hostname);
      printf("MPI rank    : %d / %d  GPU device : %d / %d\n",
             mpirank, mpisize, gpurank, gpusize);
      GPU_Kernel<<<2,2>>>();
      cudaDeviceSynchronize();
    }
  }
  MPI_Finalize();
}
