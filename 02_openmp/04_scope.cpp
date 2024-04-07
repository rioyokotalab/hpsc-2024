#include <cstdio>
#include <omp.h>

int main() {
  int a = 0;
  int b[1] = {0};
#pragma omp parallel for
  for(int i=0; i<8; i++) {
    a = omp_get_thread_num();
    b[0] = omp_get_thread_num();
  }
  printf("%d %d\n",a,b[0]);
}
