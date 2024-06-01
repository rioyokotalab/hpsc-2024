#include <cstdlib>
#include <cstring>

#define NX 41
#define NY 41
#define NT 500
#define NIT 50
#define DX (2 / (NX - 1))
#define DY (2 / (NY - 1))
#define DT 0.01
#define RHO 1
#define NU 0.02

float *array(size_t size)
{
  float *array = (float *)malloc(size);
  memset(array, 0, size);
  return array;
}

int main()
{
  float *u, *v, *p, *b;
  u = array(sizeof(float) * 2 * NX * NY);
  v = array(sizeof(float) * 2 * NX * NY);
  p = array(sizeof(float) * 2 * NX * NY);
  b = array(sizeof(float) * NX * NY);
}