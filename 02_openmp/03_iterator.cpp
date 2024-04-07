#include <cstdio>
#include <vector>
#include <omp.h>

int main() {
  std::vector<int> a(8);
  std::vector<int>::iterator it;
#pragma omp parallel for
  for(it=a.begin(); it<a.end(); it++) {
    *it = omp_get_thread_num();
    printf("%d\n",*it);
  }
}
