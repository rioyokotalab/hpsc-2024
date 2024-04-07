#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <mpi.h>

int main(int argc, char** argv) {
  const int N = 20;
  double x0[N], y0[N], m0[N], fx0[N], fy0[N];
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int begin = rank * (N / size);
  int end = (rank + 1) * (N / size);
  srand48(rank);
  for(int i=begin; i<end; i++) {
    x0[i] = drand48();
    y0[i] = drand48();
    m0[i] = drand48();
    fx0[i] = fy0[i] = 0;
  }
  double x[N], y[N], m[N], fx[N], fy[N];
  MPI_Gather( &x0[begin], end-begin, MPI_DOUBLE,  x, end-begin, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Gather( &y0[begin], end-begin, MPI_DOUBLE,  y, end-begin, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Gather( &m0[begin], end-begin, MPI_DOUBLE,  m, end-begin, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Gather(&fx0[begin], end-begin, MPI_DOUBLE, fx, end-begin, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Gather(&fy0[begin], end-begin, MPI_DOUBLE, fy, end-begin, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  MPI_Bcast( x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast( y, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast( m, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(fx, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(fy, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(i != j) {
        double rx = x[i] - x[j];
        double ry = y[i] - y[j];
        double r = std::sqrt(rx * rx + ry * ry);
        fx[i] -= rx * m[j] / (r * r * r);
        fy[i] -= ry * m[j] / (r * r * r);
      }
    }
    if(rank==0) printf("%d %g %g\n",i,fx[i],fy[i]);
  }
  MPI_Finalize();
}
