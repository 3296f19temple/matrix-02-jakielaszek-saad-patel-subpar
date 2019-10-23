#!/bin/bash
make
for(n = 2: n<11: n++)
do
mpiexec -f ~/hosts -n 4 ../mmult_mpi_omp $n
done
make clean
echo All Done
exit