#!/bin/bash
make
for i in {2..11}
do
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp $i
done
make clean
echo All Done
exit