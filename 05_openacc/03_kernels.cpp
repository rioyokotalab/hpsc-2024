#include <cstdio>
#include <openacc.h>

int main() {
#pragma acc kernels
  {
    for(int i=0; i<2; i++) {
      printf("%d: %d\n",__pgi_vectoridx(),i);
    }
    for(int i=0; i<2; i++) {
      printf("%d: %d\n",__pgi_vectoridx(),i);
    }
  }
}
