#include <cstdio>
#include <omp.h>

int main() {
  int num_devices = omp_get_num_devices();
#pragma omp target
  {
    int num_teams= omp_get_num_teams(); 
    int num_threads= omp_get_num_threads();
    printf("%d %d %d\n", num_devices, num_teams, num_threads);
  }
}
