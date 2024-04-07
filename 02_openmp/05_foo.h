#include <cstdio>

static int a = 0;
extern int b;

#pragma omp threadprivate(a,b)

void foo() {
  printf("a: %d\n",a++);
  printf("b: %d\n",b++);
}
