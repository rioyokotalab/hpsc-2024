#include <cstdio>
int main() {
  int j, n=5;
  for(int i=1; i<n; i++)
    j = j * i;
  printf("%d!=%d\n",n,j);
}
