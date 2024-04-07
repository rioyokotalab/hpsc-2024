#include <cstdio>

int main() {
  int a = 0;
  int b[1] = {0};
#pragma acc parallel loop private(a)
  for(int i=0; i<8; i++) {
    a = i;
    b[0] = i;
  }
  printf("%d %d\n",a,b[0]);
}
