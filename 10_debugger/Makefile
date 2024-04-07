00_bounds: 00_bounds.cpp
	g++ 00_bounds.cpp -fsanitize=bounds
01_factorial: 01_factorial.cpp
	g++ 01_factorial.cpp -Wall -O
02_matmul: 02_matmul.cpp
	g++ 02_matmul.cpp -D_GLIBCXX_DEBUG 
03_bucket_sort: 03_bucket_sort.cpp
	g++ 03_bucket_sort.cpp -g
04_omp_pi: 04_omp_pi.cpp
	g++ 04_omp_pi.cpp -g -O0 -fopenmp
05_ssend: 05_ssend.cpp
	mpicxx 05_ssend.cpp -g -O0
06_isend: 06_isend.cpp
	mpicxx 06_isend.cpp -g -O0
07_put: 07_put.cpp
	mpicxx 07_put.cpp -g -O0
08_check: 08_check.cu
	nvcc 08_check.cu
09_scan: 09_scan.cu
	nvcc 09_scan.cu -g -G
