#include <cstdio>
#include <cstdlib>
#include <cmath>

int main() {
  const int N = 20;
  //const int np = 4;
  double x[N], y[N], m[N], fx[N], fy[N];
  for(int i=0; i<N; i++) {
    //if(i % (N / np) == 0) srand48(i / (N / np));
    x[i] = drand48();
    y[i] = drand48();
    m[i] = drand48();
    fx[i] = fy[i] = 0;
  }
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(i != j) {
        double rx = x[i] - x[j];
        double ry = y[i] - y[j];
        double r = std::sqrt(rx * rx + ry * ry);
        fx[i] -= rx * m[j] / (r * r * r);
        fy[i] -= ry * m[j] / (r * r * r);
      }
    }
    printf("%d %g %g\n",i,fx[i],fy[i]);
  }
}
