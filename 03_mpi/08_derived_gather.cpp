#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <mpi.h>

struct Body {
  double x, y, m, fx, fy;
};

int main(int argc, char** argv) {
  const int N = 20;
  Body body0[N];
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int begin = rank * (N / size);
  int end = (rank + 1) * (N / size);
  srand48(rank);
  for(int i=begin; i<end; i++) {
    body0[i].x = drand48();
    body0[i].y = drand48();
    body0[i].m = drand48();
    body0[i].fx = body0[i].fy = 0;
  }
  Body body[N];
  MPI_Datatype MPI_BODY;
  MPI_Type_contiguous(5, MPI_DOUBLE, &MPI_BODY);
  MPI_Type_commit(&MPI_BODY);
  MPI_Allgather(&body0[begin], end-begin, MPI_BODY, body, end-begin, MPI_BODY, MPI_COMM_WORLD);
  for(int i=begin; i<end; i++) {
    for(int j=0; j<N; j++) {
      if(i != j) {
        double rx = body[i].x - body[j].x;
        double ry = body[i].y - body[j].y;
        double r = std::sqrt(rx * rx + ry * ry);
        body0[i].fx -= rx * body[j].m / (r * r * r);
        body0[i].fy -= ry * body[j].m / (r * r * r);
      }
    }
  }
  MPI_Datatype MPI_FORCE;
  int blocksize[1] = {2}, displacement[1] = {3};
  MPI_Type_indexed(1, blocksize, displacement, MPI_DOUBLE, &MPI_FORCE);
  MPI_Type_create_resized(MPI_FORCE, 0, 5*sizeof(double), &MPI_FORCE);
  MPI_Type_commit(&MPI_FORCE);
  MPI_Allgather(&body0[begin], end-begin, MPI_FORCE, body, end-begin, MPI_FORCE, MPI_COMM_WORLD);
  for(int i=0; i<N; i++) {
    if(rank==0) printf("%d %g %g\n",i,body[i].fx,body[i].fy);
  }
  MPI_Finalize();
}
