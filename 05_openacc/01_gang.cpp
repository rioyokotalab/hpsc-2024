#include <cstdio>
#include <openacc.h>

int main() {
#pragma acc parallel loop num_gangs(2) num_workers(2) vector_length(2)
  for(int i=0; i<8; i++) {
    printf("(%d,%d,%d): %d\n",
           __pgi_gangidx(),
           __pgi_workeridx(),
           __pgi_vectoridx(),i);
  }
}
