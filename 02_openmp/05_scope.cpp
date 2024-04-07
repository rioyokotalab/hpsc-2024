void foo();
void bar();

int a = 10;
int b = 10;

#pragma omp threadprivate(a,b)

int main() {
#pragma omp parallel for
  for (int i=0; i<4; i++) {
    foo();
    bar();
  }
}
