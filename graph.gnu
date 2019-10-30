set terminal png size 800,600
set output 'outGraph.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (sec)'
set title 'Matrix multiplication speed on Wlofgang Cluster'
plot  "SLOW.txt" using 1:2 title 'Slow' with linespoint, "FAST.txt" using 1:2 title 'Fast' with linespoint
