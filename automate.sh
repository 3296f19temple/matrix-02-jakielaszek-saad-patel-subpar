#!/bin/bash
make
gcc -o create_matrix create_matrix.c

touch log.txt
touch matrix_a.txt
touch matrix_b.txt

rm log.txt
rm matrix_a.txt
rm matrix_b.txt

for i in `seq 1 11`;
do
./create_matrix $i matrix_a.txt
./create_matrix $i matrix_b.txt    
mpiexec -f ~/hosts -n 4 ./mmult_mpi_omp matrix_a.txt matrix_b.txt log.txt
done

make clean
echo All Done
exit
