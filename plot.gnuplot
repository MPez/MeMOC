#set title "Tempo soluzioni ottime"
set terminal pdf
set grid
set xrange [10:80]
set yrange [0:50]
set xlabel "Numero nodi"
set ylabel "Tempo (s)"
set key top left
set xtics rotate

set output "results/cplex_casuali.pdf"
plot "results/plot_results.txt" every ::0::100 using 1:2:3 with yerrorlines title "Istanze casuali"

set output "results/cplex_cluster.pdf"
plot "results/plot_results.txt" every ::101::500 using 1:2:3 with yerrorlines title "Istanze cluster"

set output "results/cplex_circolari.pdf"
plot "results/plot_circular.txt" using 1:2 with linespoints title "Istanze circolari"
