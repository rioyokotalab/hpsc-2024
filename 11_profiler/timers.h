//#define GETTIME 1

#if TIME
#include <time.h>
time_t start;
time_t elapse = 0;
#elif CLOCK
#include <time.h>
clock_t start;
clock_t elapse = 0;
#elif GETTIMEOFDAY
#include <sys/time.h>
struct timeval start; 
double elapse = 0;
#elif BOOST
#include <boost/timer/timer.hpp>
boost::timer::cpu_timer timer;
#elif CHRONO
#include <chrono>
using namespace std::chrono;
system_clock::time_point start;
double elapse = 0;
#elif GETTIME
#include <time.h>
struct timespec start;
double elapse = 0;
#elif OMP
#include <omp.h>
double start;
double elapse;
#elif MPIWTIME
#include <mpi.h>
double start;
double elapse;
#else
#error Define macro for timer type
#endif

void startTimer() {
#if TIME
  start = time(NULL);
#elif CLOCK
  start = clock();
#elif GETTIMEOFDAY
  gettimeofday(&start, NULL);
#elif BOOST
  timer.start();
#elif CHRONO
  start = system_clock::now();
#elif GETTIME
  clock_gettime(CLOCK_REALTIME, &start);
#elif OMP
  start = omp_get_wtime();
#elif MPIWTIME
  start = MPI_Wtime();
#endif
}

void stopTimer() {
#if TIME
  elapse += time(NULL) - start;
#elif CLOCK
  elapse += clock() - start;
#elif GETTIMEOFDAY
  struct timeval stop;
  gettimeofday(&stop, NULL);
  elapse += stop.tv_sec-start.tv_sec+(stop.tv_usec-start.tv_usec)*1e-6;
#elif BOOST
  timer.stop();
#elif CHRONO
  elapse += duration<double>(system_clock::now() - start).count();
#elif GETTIME
  struct timespec stop;
  clock_gettime(CLOCK_REALTIME, &stop);
  elapse += stop.tv_sec-start.tv_sec+(stop.tv_nsec-start.tv_nsec)*1e-9;
#elif OMP
  elapse += omp_get_wtime() - start;
#elif MPIWTIME
  elapse += MPI_Wtime() - start;
#endif
}

double getTime() {
#if TIME
  return (double) elapse;
#elif CLOCK
  return (double) elapse / CLOCKS_PER_SEC;
#elif GETTIMEOFDAY
  return elapse;
#elif BOOST
  return (double)timer.elapsed().wall*1e-9;
#elif CHRONO
  return elapse;
#elif GETTIME
  return elapse;
#elif OMP
  return elapse;
#elif MPIWTIME
  return elapse;
#endif
}
