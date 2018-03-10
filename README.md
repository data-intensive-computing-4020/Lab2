# ELEN4020 - Data Intensive Computing
## Lab 2 - In-Place Parallel Matrix Transposition
This program has 3 algorithms that all achieve in-place matrix transposition. These operate on square matrices of sizes 128, 1024 and 8192. The algorithms are as follows:

1. Naive Iteration Algorithm - This algorithm serially does transposition on a matrix through 2 loops.
2. OpenMp Algorithm - This algorithm does transposition on a matrix in parallel through the use of OpenMp.
3. PThreads Algorithm - This algorithm does transposition on a matrix in parallel through the use of PThreads.

The amount of threads that OpenMp and PThreads algorithms use are varied from 4, 8, 16, 64 and 128. This is to establish the impact of more threads on the speed of the algorithms.
