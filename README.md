# fast-matrix-multiplication

Mtrix multiplication is a topic I've been curious about due to the importance of fast matrix operations in machine learning. I briefly explored this topic during CS361: Concurrent Programming

## Background:
I researched the different matrix algorithms such as traditional block-matrix, divide-and-conquer, Strassen’s, and Coppersmith-Winograd. I referenced the following resources (among others):
- CLRS sections on matrix multiplication & parallelizing algorithms
- Skiena’s section on matrix multiplication (chapter 2, pg 46)
- A C++ threaded [approach](https://github.com/mtrebi/matrix-multiplication-threading)
- Parallelizing matrix multiplication [slides](https://www.cl.cam.ac.uk/teaching/1516/AdvAlgo/matrix.pdf)
- Parallelizing matrix multiplication [paper](https://stanford.edu/~rezab/classes/cme323/S16/notes/Lecture03/cme323_lec3.pdf)

## Approach
Based on this research, I decided to go with a multi-threaded approach to the traditional matrix multiplication algorithm. I defined the following constraints due to time limits:
- Only square matrices
- Any size *N*
- Maximum number of threads used can be 30 (the college's thread limit for their linux cluster called tux)

Threads are assigned computations based on the matrix size. One improvement to be made is distributing workload of larger matrix sizes evenly between threads.
Performance was benchmarked against traditional matrix multiplication without any threads,

## Results
Rnadom number generator uses a seed of 42 for comparison purposs. All times are in microseconds.

| **N** | **Sequential Time** | **Threaded Time** |
|-------|---------------------|-------------------|
| 4     | 1                   | 371               |
| 10    | 8                   | 674               |
| 25    | 85                  | 1712              |
| 50    | 784                 | 1745              |
| 75    | 2694                | 2506              |
| 100   | 5746                | 2864              |
| 250   | 88,867              | 52,436            |
| 500   | 706,718             | 167,478           |
| 1000  | 6,792,412           | 823,162           |
| 1500  | 62,540,534          | 4,320,101         |

Research online revealed that *N* = ~100 is the crossover point where threads truly make a performance difference. This is evident from my results – at larger input sizes, matrix multiplication is significantly slower sequentially compared to with 30 threads.
