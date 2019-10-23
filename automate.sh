#!/bin/bash
make
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 2
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 3
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 4
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 5
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 6
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 7
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 8
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 9
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp 10
make clean
echo All Done