00_hello: 00_hello.cu
	nvcc 00_hello.cu
01_thread: 01_thread.cu
	nvcc 01_thread.cu
02_block: 02_block.cu
	nvcc 02_block.cu
03_if: 03_if.cu
	nvcc 03_if.cu
04_atomic: 04_atomic.cu
	nvcc 04_atomic.cu
05_reduction: 05_reduction.cu
	nvcc 05_reduction.cu
06_shared: 06_shared.cu
	nvcc 06_shared.cu
07_warp: 07_warp.cu
	nvcc 07_warp.cu
08_scan: 08_scan.cu
	nvcc 08_scan.cu
09_stream: 09_stream.cu
	nvcc 09_stream.cu --default-stream per-thread
10_cooperative: 10_cooperative.cu
	nvcc 10_cooperative.cu
11_mpi: 11_mpi.cu
	nvcc 11_mpi.cu -lmpi
12_hip: 12_hip.cpp
	hipcc 12_hip.cpp
13_bucket_sort: 13_bucket_sort.cpp
	g++ 13_bucket_sort.cpp
