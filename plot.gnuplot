#set title "Tempo soluzioni ottime"
set terminal pdf
set grid
set logscale y
set xlabel "Numero nodi"
set ylabel "Tempo (s)"
set key top left Left reverse

set xrange [0:56]
set xtics 0, 4, 56

set output "results/cplex_casuali.pdf"
plot "results/CPXplot_results.txt" every ::0::9 using 1:2:3 with yerrorlines title "Istanze casuali CPX"

set output "results/tabu_4_tempo.pdf"
plot "results/TABUplot_results.txt" every ::0::9 using 1:2:3 with yerrorlines title "Istanze casuali TABU 4"

set output "results/tabu_5_tempo.pdf"
plot "results/TABUplot_results.txt" every ::10::19 using 1:2:3 with yerrorlines title "Istanze casuali TABU 5"

set output "results/tabu_6_tempo.pdf"
plot "results/TABUplot_results.txt" every ::20::29 using 1:2:3 with yerrorlines title "Istanze casuali TABU 6"

set output "results/tabu_7_tempo.pdf"
plot "results/TABUplot_results.txt" every ::30::39 using 1:2:3 with yerrorlines title "Istanze casuali TABU 7"

set output "results/tabu_8_tempo.pdf"
plot "results/TABUplot_results.txt" every ::40::49 using 1:2:3 with yerrorlines title "Istanze casuali TABU 8"

unset logscale y
set ylabel "Costo"

set output "results/tabu_4_costo.pdf"
plot "results/TABUplot_results.txt" every ::0::9 using 1:4:5 with yerrorlines title "Istanze casuali TABU 4"

set output "results/tabu_5_costo.pdf"
plot "results/TABUplot_results.txt" every ::10::19 using 1:4:5 with yerrorlines title "Istanze casuali TABU 5"

set output "results/tabu_6_costo.pdf"
plot "results/TABUplot_results.txt" every ::20::29 using 1:4:5 with yerrorlines title "Istanze casuali TABU 6"

set output "results/tabu_7_costo.pdf"
plot "results/TABUplot_results.txt" every ::30::39 using 1:4:5 with yerrorlines title "Istanze casuali TABU 7"

set output "results/tabu_8_costo.pdf"
plot "results/TABUplot_results.txt" every ::40::49 using 1:4:5 with yerrorlines title "Istanze casuali TABU 8"

set xrange [0:88]
set xtics 0, 4, 88
set ylabel "Tempo (s)"
set logscale y

set output "results/cplex_circolari.pdf"
plot "results/CPXplot_circular.txt" using 1:2 with linespoints title "Istanze circolari"

set xrange [0:18]
set xtics 0, 2, 50

set output "results/cplex_cluster_1.pdf"
plot "results/CPXplot_results.txt" every 4::10::49 using 1:2:3 with yerrorlines title "Istanze 1 cluster"

set xrange [0:36]

set output "results/cplex_cluster_2.pdf"
plot "results/CPXplot_results.txt" every 4::11::49 using 1:2:3 with yerrorlines title "Istanze 2 cluster"

set xrange [0:50]

set output "results/cplex_cluster_3.pdf"
plot "results/CPXplot_results.txt" every 4::12::49 using 1:2:3 with yerrorlines title "Istanze 3 cluster"

set xrange [0:70]
set xtics 0, 4, 70

set output "results/cplex_cluster_4.pdf"
plot "results/CPXplot_results.txt" every 4::13::49 using 1:2:3 with yerrorlines title "Istanze 4 cluster"

set xrange [0:88]
set xtics 0, 4, 88
set key font ", 6"
set pointsize 0.4

set output "results/cplex_all.pdf"
plot \
    "results/CPXplot_results.txt" every ::0::9 using 1:2:3 with linespoints title "Istanze casuali", \
    "results/CPXplot_results.txt" every 4::10::49 using 1:2:3 with linespoints title "Istanze 1 cluster", \
    "results/CPXplot_results.txt" every 4::11::49 using 1:2:3 with linespoints title "Istanze 2 cluster", \
    "results/CPXplot_results.txt" every 4::12::49 using 1:2:3 with linespoints title "Istanze 3 cluster", \
    "results/CPXplot_results.txt" every 4::13::49 using 1:2:3 with linespoints title "Istanze 4 cluster", \
    "results/CPXplot_circular.txt" using 1:2 with linespoints title "Istanze circolari"

set xrange [0:56]
set xtics 0, 4, 56

set output "results/tabu_all_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every ::0::9 using 1:2:3 with yerrorlines title "Istanze casuali TABU 4", \
    "results/TABUplot_results.txt" every ::10::19 using 1:2:3 with yerrorlines title "Istanze casuali TABU 5", \
    "results/TABUplot_results.txt" every ::20::29 using 1:2:3 with yerrorlines title "Istanze casuali TABU 6", \
    "results/TABUplot_results.txt" every ::30::39 using 1:2:3 with yerrorlines title "Istanze casuali TABU 7", \
    "results/TABUplot_results.txt" every ::40::49 using 1:2:3 with yerrorlines title "Istanze casuali TABU 8"

set ylabel "Costo"
unset logscale y

set output "results/tabu_all_costo.pdf"
plot \
    "results/TABUplot_results.txt" every ::0::9 using 1:4:5 with yerrorlines title "Istanze casuali TABU 4", \
    "results/TABUplot_results.txt" every ::10::19 using 1:4:5 with yerrorlines title "Istanze casuali TABU 5", \
    "results/TABUplot_results.txt" every ::20::29 using 1:4:5 with yerrorlines title "Istanze casuali TABU 6", \
    "results/TABUplot_results.txt" every ::30::39 using 1:4:5 with yerrorlines title "Istanze casuali TABU 7", \
    "results/TABUplot_results.txt" every ::40::49 using 1:4:5 with yerrorlines title "Istanze casuali TABU 8"