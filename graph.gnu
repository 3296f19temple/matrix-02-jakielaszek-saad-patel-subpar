set terminal png size 800,600
set output 'outGraph.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size (nxn)'
set ylabel 'Time (sec)'
set title 'Matrix multiplication speed on Wolfgang Cluster'
plot  "SLOW.txt" using 1:2 title 'Slow' with linespoint, "FAST.txt" using 1:2 title 'Fast' with linespoint, "MPI.txt" using 1:2 title 'MPI' with linespoint, "OMP.txt" using 1:2 title 'OpenMP' with linespoint
