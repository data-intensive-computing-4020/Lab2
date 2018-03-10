# ELEN4020 - Data Intensive Computing
## Lab 2 - In-Place Parallel Matrix Transposition
The lab report pdf and latex file can be found in the Report Folder. Furthermore the source code that was written and used for the lab can be found in the Code folder.

This lab involved the implementation of 3 algorithms that all achieve in-place matrix transposition. These operate on square matrices of sizes 128, 1024 and 8192. The algorithms are as follows:

1. Naive Iteration Algorithm - This algorithm serially does transposition on a matrix through 2 loops.
2. OpenMp Algorithm - This algorithm does transposition on a matrix in parallel through the use of OpenMp.
3. PThreads Algorithm - This algorithm does transposition on a matrix in parallel through the use of PThreads.

The amount of threads that OpenMp and PThreads algorithms use are varied from 4, 8, 16, 64 and 128. This is to establish the impact of more threads on the speed of the algorithms. The naive solution is implemented in both openMP.c and pThread.c files. The size of the matrix and the number of threads can be changed by editting the variable declarations at the top of each file.

### Installation instructions

In a terminal:

```bash
# Clone the Repo
git clone https://github.com/data-intensive-computing-4020/Lab2.git

# Change to the correct directory
cd Lab2
cd Code

# Compile openMP.c
gcc -o openMP openMP.c -fopenmp -lgomp

# Run openMP executable 
./openMP

# Compile pThread.c
gcc -o pThread pThread.c -fopenmp -lgomp -lpthread

# Run openMP executable 
./pThread

```
