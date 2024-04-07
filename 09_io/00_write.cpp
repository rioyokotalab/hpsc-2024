#include <cstdio>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

int main (int argc, char** argv) {
  const int N = 1000000;
  vector<int> buffer(N,1);
  ofstream file("data.dat");
  auto tic = chrono::steady_clock::now();
  for(int i=0; i<N; i++)
    file << buffer[i] << "\n";
  auto toc = chrono::steady_clock::now();
  file.close();
  double time = chrono::duration<double>(toc - tic).count();
  printf("N=%d: %lf s (%lf GB/s)\n",N,time,4*N/time/1e9);
}
