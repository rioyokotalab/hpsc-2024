00_loop: 00_loop.cpp
	nvc++ 00_loop.cpp -acc -Minfo
01_gang: 01_gang.cpp
	nvc++ 01_gang.cpp -acc -Minfo
02_parallel: 02_parallel.cpp
	nvc++ 02_parallel.cpp -acc -Minfo
03_kernels: 03_kernels.cpp
	nvc++ 03_kernels.cpp -acc -Minfo
04_array: 04_array.cpp
	nvc++ 04_array.cpp -acc -Minfo
05_vector: 05_vector.cpp
	nvc++ 05_vector.cpp -acc -gpu=managed -Minfo
06_iterator: 06_iterator.cpp
	nvc++ 06_iterator.cpp -acc -gpu=managed -Minfo
07_scope: 07_scope.cpp
	nvc++ 07_scope.cpp -acc -Minfo
08_reduction: 08_reduction.cpp
	nvc++ 08_reduction.cpp -acc -Minfo
09_matmult: 09_matmult.cpp
	nvc++ 09_matmult.cpp -acc -gpu=managed -Minfo
10_openmp: 10_openmp.cpp
	g++ 10_openmp.cpp -fopenmp
11_loop: 11_loop.cpp
	g++ 11_loop.cpp -fopenmp
12_matmult: 12_matmult.cpp
	g++ 12_matmult.cpp -fopenmp -O3
