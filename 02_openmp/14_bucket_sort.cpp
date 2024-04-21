
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <omp.h>

int main() {
  int n = 50000;
  int range = 5;
  std::vector<int> key(n);
#pragma omp parallel
{
#pragma omp for
  for (int i=0; i<n; i++) {
    key[i] = rand() % range;
    printf("%d ",key[i]);
  }
  printf("\n");
  std::vector<int> bucket(range,0);
#pragma omp parallel
  for (int i=0; i<n; i++){
    bucket[key[i]]++;}
  std::vector<int> offset(range,0);
//we create a temp vector to be able to parallel
std::vector<int> off(range,0);
  for (int i=1; i<range; i++){
    off[i] = offset[i-1] + bucket[i-1];
offset[i]=off[i];}
#pragma omp parallel
  for (int i=0; i<range; i++) {
    int j = offset[i];
    for (; bucket[i]>0; bucket[i]--) {
      key[j++] = i;
    }
  }
#pragma omp parallel
  for (int i=0; i<n; i++) {
    printf("%d ",key[i]);
  }
  printf("\n");
}
}
