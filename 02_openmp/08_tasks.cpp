#include <cstdio>

int fib(int n) {
  int i,j;
  if (n<2) return n;
#pragma omp task shared(i)
  i = fib(n-1);
#pragma omp task shared(j)
  j = fib(n-2);
#pragma omp taskwait
  return i+j;
}

int main() {
  int n = 20;
#pragma omp parallel
  for (int i=1; i<n; i++) {
#pragma omp single
    printf("%d ",fib(i));
  }
  printf("\n");
}
