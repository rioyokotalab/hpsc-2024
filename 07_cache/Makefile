00_base: 00_base.cpp
	g++ 00_base.cpp -O3
01_loop_order: 01_loop_order.cpp
	g++ 01_loop_order.cpp -O3
02_openmp: 02_openmp.cpp
	g++ 02_openmp.cpp -O3 -fopenmp
03_blocking: 03_blocking.cpp
	g++ 03_blocking.cpp -O3 -fopenmp
04_simd_blocking: 04_simd_blocking.cpp
	g++ 04_simd_blocking.cpp -O3 -fopenmp -march=native
05_sgemm: 05_sgemm.cpp
	g++ 05_sgemm.cpp -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -liomp5
06_base: 06_base.cu
	nvcc 06_base.cu -Xcompiler "-O3 -fopenmp" -lcublas
07_shared: 07_shared.cu
	nvcc 07_shared.cu -Xcompiler "-O3 -fopenmp" -lcublas
08_block_8x8: 08_block_8x8.cu
	nvcc 08_block_8x8.cu -Xcompiler "-O3 -fopenmp" -lcublas
09_reg_load: 09_reg_load.cu
	nvcc 09_reg_load.cu -Xcompiler "-O3 -fopenmp" -lcublas
10_align: 10_align.cu
	nvcc 10_align.cu -Xcompiler "-O3 -fopenmp" -lcublas
11_warp: 11_warp.cu
	nvcc 11_warp.cu -Xcompiler "-O3 -fopenmp" -lcublas
12_vector_4x2: 12_vector_4x2.cu
	nvcc 12_vector_4x2.cu -Xcompiler "-O3 -fopenmp" -lcublas
