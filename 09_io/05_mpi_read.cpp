#include <mpi.h>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
  int mpisize, mpirank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpisize);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
  ifstream file("data.dat", ios::binary | ios::ate);
  int N = file.tellg()/sizeof(int);
  int Nlocal = N / mpisize;
  int offset = Nlocal * mpirank;
  vector<int> buffer(Nlocal);
  file.seekg (offset, ios::beg);
  auto tic = chrono::steady_clock::now();
  file.read((char*)&buffer[0], Nlocal*sizeof(int));
  auto toc = chrono::steady_clock::now();
  file.close();
  double time = chrono::duration<double>(toc - tic).count();
  int sum = 0;
  for (int i=0; i<Nlocal; i++)
    sum += buffer[i];
  if(!mpirank) printf("N=%d: %lf s (%lf GB/s)\n",N,time,4*N/time/1e9);
  printf("rank=%d sum=%d\n",mpirank,sum);
  MPI_Finalize();
}
