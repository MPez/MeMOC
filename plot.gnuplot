#set title "Tempo soluzioni ottime"
set terminal pdf
set grid
set logscale y
set xlabel "Numero nodi"
set ylabel "Tempo (s)"
set key top left

set xrange [0:56]
set xtics 0, 4, 56

set output "results/cplex_casuali.pdf"
plot "results/plot_results.txt" every ::0::9 using 1:2:3 with yerrorlines title "Istanze casuali"

set output "results/cplex_circolari.pdf"
plot "results/plot_circular.txt" using 1:2 with linespoints title "Istanze circolari"

set xrange [0:18]
set xtics 0, 2, 50

set output "results/cplex_cluster_1.pdf"
plot "results/plot_results.txt" every 4::10::49 using 1:2:3 with yerrorlines title "Istanze 1 cluster"

set xrange [0:36]

set output "results/cplex_cluster_2.pdf"
plot "results/plot_results.txt" every 4::11::49 using 1:2:3 with yerrorlines title "Istanze 2 cluster"

set xrange [0:50]

set output "results/cplex_cluster_3.pdf"
plot "results/plot_results.txt" every 4::12::49 using 1:2:3 with yerrorlines title "Istanze 3 cluster"

set xrange [0:70]
set xtics 0, 4, 70

set output "results/cplex_cluster_4.pdf"
plot "results/plot_results.txt" every 4::13::49 using 1:2:3 with yerrorlines title "Istanze 4 cluster"

set key font ", 7"
set pointsize 0.5

set output "results/cplex_cluster_all.pdf"
plot \
    "results/plot_results.txt" every ::0::9 using 1:2:3 with linespoints title "Istanze casuali", \
    "results/plot_results.txt" every 4::10::49 using 1:2:3 with linespoints title "Istanze 1 cluster", \
    "results/plot_results.txt" every 4::11::49 using 1:2:3 with linespoints title "Istanze 2 cluster", \
    "results/plot_results.txt" every 4::12::49 using 1:2:3 with linespoints title "Istanze 3 cluster", \
    "results/plot_results.txt" every 4::13::49 using 1:2:3 with linespoints title "Istanze 4 cluster", \
    "results/plot_circular.txt" using 1:2 with linespoints title "Istanze circolari"