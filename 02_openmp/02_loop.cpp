#include <cstdio>
#include <omp.h>

int main() {
#pragma omp parallel for
  for(int i=0; i<8; i++) {
    printf("%d: %d\n",omp_get_thread_num(),i);
  }
}
