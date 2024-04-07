#include <cstdio>
#include <vector>

int main() {
  std::vector<int> a(8);
  std::vector<int>::iterator it;
#pragma acc parallel loop
  for(it=a.begin(); it<a.end(); it++) {
    *it = it-a.begin();
    printf("%d\n",*it);
  }
}
