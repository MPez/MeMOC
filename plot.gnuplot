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
plot "results/TABUplot_results.txt" every ::50::59 using 1:2:3 with yerrorlines title "Istanze casuali TABU 5"

set output "results/tabu_6_tempo.pdf"
plot "results/TABUplot_results.txt" every ::100::109 using 1:2:3 with yerrorlines title "Istanze casuali TABU 6"

set output "results/tabu_7_tempo.pdf"
plot "results/TABUplot_results.txt" every ::150::159 using 1:2:3 with yerrorlines title "Istanze casuali TABU 7"

set output "results/tabu_8_tempo.pdf"
plot "results/TABUplot_results.txt" every ::200::209 using 1:2:3 with yerrorlines title "Istanze casuali TABU 8"

unset logscale y
set ylabel "Costo"

set output "results/tabu_4_costo.pdf"
plot "results/TABUplot_results.txt" every ::0::9 using 1:4:5 with yerrorlines title "Istanze casuali TABU 4"

set output "results/tabu_5_costo.pdf"
plot "results/TABUplot_results.txt" every ::50::59 using 1:4:5 with yerrorlines title "Istanze casuali TABU 5"

set output "results/tabu_6_costo.pdf"
plot "results/TABUplot_results.txt" every ::100::109 using 1:4:5 with yerrorlines title "Istanze casuali TABU 6"

set output "results/tabu_7_costo.pdf"
plot "results/TABUplot_results.txt" every ::150::159 using 1:4:5 with yerrorlines title "Istanze casuali TABU 7"

set output "results/tabu_8_costo.pdf"
plot "results/TABUplot_results.txt" every ::200::209 using 1:4:5 with yerrorlines title "Istanze casuali TABU 8"

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

set output "results/tabu_4_cluster_1_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::10::49 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 4"

set output "results/tabu_5_cluster_1_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::60::99 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 5"

set output "results/tabu_6_cluster_1_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::110::149 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 6"

set output "results/tabu_7_cluster_1_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::160::199 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 7"

set output "results/tabu_8_cluster_1_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::210::249 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 8"


set xrange [0:36]

set output "results/cplex_cluster_2.pdf"
plot "results/CPXplot_results.txt" every 4::11::49 using 1:2:3 with yerrorlines title "Istanze 2 cluster"

set output "results/tabu_4_cluster_2_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::11::49 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 4"

set output "results/tabu_5_cluster_2_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::61::99 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 5"

set output "results/tabu_6_cluster_2_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::111::149 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 6"

set output "results/tabu_7_cluster_2_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::161::199 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 7"

set output "results/tabu_8_cluster_2_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::211::249 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 8"


set xrange [0:50]

set output "results/cplex_cluster_3.pdf"
plot "results/CPXplot_results.txt" every 4::12::49 using 1:2:3 with yerrorlines title "Istanze 3 cluster"

set output "results/tabu_4_cluster_3_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::12::49 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 4"

set output "results/tabu_5_cluster_3_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::62::99 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 5"

set output "results/tabu_6_cluster_3_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::112::149 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 6"

set output "results/tabu_7_cluster_3_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::162::199 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 7"

set output "results/tabu_8_cluster_3_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::212::249 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 8"


set xrange [0:70]
set xtics 0, 4, 70

set output "results/cplex_cluster_4.pdf"
plot "results/CPXplot_results.txt" every 4::13::49 using 1:2:3 with yerrorlines title "Istanze 4 cluster"

set output "results/tabu_4_cluster_4_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::13::49 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 4"

set output "results/tabu_5_cluster_4_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::63::99 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 5"

set output "results/tabu_6_cluster_4_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::113::149 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 6"

set output "results/tabu_7_cluster_4_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::163::199 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 7"

set output "results/tabu_8_cluster_4_tempo.pdf"
plot "results/TABUplot_results.txt" every 4::213::249 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 8"


set xrange [0:88]
set xtics 0, 4, 88
set key font ", 6"
set pointsize 0.4
set ylabel "Tempo (s)"

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
    "results/TABUplot_results.txt" every ::50::59 using 1:2:3 with yerrorlines title "Istanze casuali TABU 5", \
    "results/TABUplot_results.txt" every ::100::109 using 1:2:3 with yerrorlines title "Istanze casuali TABU 6", \
    "results/TABUplot_results.txt" every ::150::159 using 1:2:3 with yerrorlines title "Istanze casuali TABU 7", \
    "results/TABUplot_results.txt" every ::200::209 using 1:2:3 with yerrorlines title "Istanze casuali TABU 8"
    
    
set output "results/cplex_tabu_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every ::200::209 using 1:2:3 with yerrorlines title "Istanze casuali TABU 8", \
    "results/CPXplot_results.txt" every ::0::9 using 1:2:3 with yerrorlines title "Istanze casuali CPX"


    
set xrange [0:18]
set xtics 0, 2, 50
    
set output "results/tabu_cluster_1_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::10::49 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::60::99 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::110::149 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::160::199 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::210::249 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 8"

set output "results/cplex_tabu_cluster_1_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::210::249 using 1:2:3 with yerrorlines title "Istanze 1 cluster TABU 8", \
    "results/CPXplot_results.txt" every 4::10::49 using 1:2:3 with yerrorlines title "Istanze 1 cluster CPX"
    
set xrange [0:36]
    
set output "results/tabu_cluster_2_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::11::49 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::61::99 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::111::149 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::161::199 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::211::249 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 8"

set output "results/cplex_tabu_cluster_2_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::211::249 using 1:2:3 with yerrorlines title "Istanze 2 cluster TABU 8", \
    "results/CPXplot_results.txt" every 4::11::49 using 1:2:3 with yerrorlines title "Istanze 2 cluster CPX"
    
set xrange [0:50]    

set output "results/tabu_cluster_3_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::12::49 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::62::99 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::112::149 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::162::199 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::212::249 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 8"
    
set output "results/cplex_tabu_cluster_3_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::212::249 using 1:2:3 with yerrorlines title "Istanze 3 cluster TABU 8", \
    "results/CPXplot_results.txt" every 4::12::49 using 1:2:3 with yerrorlines title "Istanze 3 cluster CPX"

set xrange [0:70]
set xtics 0, 4, 70
    
set output "results/tabu_cluster_4_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::13::49 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::63::99 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::113::149 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::163::199 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::213::249 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 8"
    
set output "results/cplex_tabu_cluster_4_tempo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::213::249 using 1:2:3 with yerrorlines title "Istanze 4 cluster TABU 8", \
    "results/CPXplot_results.txt" every 4::13::49 using 1:2:3 with yerrorlines title "Istanze 4 cluster CPX"


set xrange [0:56]
set xtics 0, 4, 56

set ylabel "Costo"
unset logscale y

set output "results/tabu_all_costo.pdf"
plot \
    "results/TABUplot_results.txt" every ::0::9 using 1:4:5 with yerrorlines title "Istanze casuali TABU 4", \
    "results/TABUplot_results.txt" every ::50::59 using 1:4:5 with yerrorlines title "Istanze casuali TABU 5", \
    "results/TABUplot_results.txt" every ::100::109 using 1:4:5 with yerrorlines title "Istanze casuali TABU 6", \
    "results/TABUplot_results.txt" every ::150::159 using 1:4:5 with yerrorlines title "Istanze casuali TABU 7", \
    "results/TABUplot_results.txt" every ::200::209 using 1:4:5 with yerrorlines title "Istanze casuali TABU 8"


set output "results/cplex_tabu_costo.pdf"
plot \
    "results/TABUplot_results.txt" every ::200::209 using 1:4:5 with yerrorlines title "Istanze casuali TABU 8", \
    "results/CPXplot_results.txt" every ::0::9 using 1:4 with linespoints title "Istanze casuali CPX"


set xrange [0:18]
set xtics 0, 2, 50
    
set output "results/tabu_cluster_1_costo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::10::49 using 1:4:5 with yerrorlines title "Istanze 1 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::60::99 using 1:4:5 with yerrorlines title "Istanze 1 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::110::149 using 1:4:5 with yerrorlines title "Istanze 1 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::160::199 using 1:4:5 with yerrorlines title "Istanze 1 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::210::249 using 1:4:5 with yerrorlines title "Istanze 1 cluster TABU 8"
    
set xrange [0:36]
    
set output "results/tabu_cluster_2_costo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::11::49 using 1:4:5 with yerrorlines title "Istanze 2 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::61::99 using 1:4:5 with yerrorlines title "Istanze 2 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::111::149 using 1:4:5 with yerrorlines title "Istanze 2 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::161::199 using 1:4:5 with yerrorlines title "Istanze 2 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::211::249 using 1:4:5 with yerrorlines title "Istanze 2 cluster TABU 8"
    
set xrange [0:50]    

set output "results/tabu_cluster_3_costo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::12::49 using 1:4:5 with yerrorlines title "Istanze 3 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::62::99 using 1:4:5 with yerrorlines title "Istanze 3 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::112::149 using 1:4:5 with yerrorlines title "Istanze 3 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::162::199 using 1:4:5 with yerrorlines title "Istanze 3 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::212::249 using 1:4:5 with yerrorlines title "Istanze 3 cluster TABU 8"
    
set xrange [0:70]
set xtics 0, 4, 70
    
set output "results/tabu_cluster_4_costo.pdf"
plot \
    "results/TABUplot_results.txt" every 4::13::49 using 1:4:5 with yerrorlines title "Istanze 4 cluster TABU 4", \
    "results/TABUplot_results.txt" every 4::63::99 using 1:4:5 with yerrorlines title "Istanze 4 cluster TABU 5", \
    "results/TABUplot_results.txt" every 4::113::149 using 1:4:5 with yerrorlines title "Istanze 4 cluster TABU 6", \
    "results/TABUplot_results.txt" every 4::163::199 using 1:4:5 with yerrorlines title "Istanze 4 cluster TABU 7", \
    "results/TABUplot_results.txt" every 4::213::249 using 1:4:5 with yerrorlines title "Istanze 4 cluster TABU 8"
    
    
    
    
set xrange [0:56]
set xtics 0, 4, 56
set ytics 0, 2

set ylabel "Costo (%)"

set output "results/cplex_tabu4_compare.pdf"
plot \
    "results/compare.txt" every ::0::9 using 1:2 with linespoints title "Istanze casuali TABU 4 - media", \
    "results/compare.txt" every ::0::9 using 1:4 with linespoints title "Istanze casuali TABU 4 - max"

set output "results/cplex_tabu5_compare.pdf"
plot \
    "results/compare.txt" every ::50::59 using 1:2 with linespoints title "Istanze casuali TABU 5 - media", \
    "results/compare.txt" every ::50::59 using 1:4 with linespoints title "Istanze casuali TABU 5 - max"

set output "results/cplex_tabu6_compare.pdf"
plot \
    "results/compare.txt" every ::100::109 using 1:2 with linespoints title "Istanze casuali TABU 6 - media", \
    "results/compare.txt" every ::100::109 using 1:4 with linespoints title "Istanze casuali TABU 6 - max"

set output "results/cplex_tabu7_compare.pdf"
plot \
    "results/compare.txt" every ::150::159 using 1:2 with linespoints title "Istanze casuali TABU 7 - media", \
    "results/compare.txt" every ::150::159 using 1:4 with linespoints title "Istanze casuali TABU 7 - max"
    
set output "results/cplex_tabu8_compare.pdf"
plot \
    "results/compare.txt" every ::200::209 using 1:2 with linespoints title "Istanze casuali TABU 8 - media", \
    "results/compare.txt" every ::200::209 using 1:4 with linespoints title "Istanze casuali TABU 8 - max"


set xrange [0:18]
set xtics 0, 2, 50
set ytics autofreq

set output "results/cplex_tabu4_cluster1_compare.pdf"
plot \
    "results/compare.txt" every 4::10::49 using 1:2 with linespoints title "Istanze 1 cluster TABU 4 - media", \
    "results/compare.txt" every 4::10::49 using 1:4 with linespoints title "Istanze 1 cluster TABU 4 - max"

set output "results/cplex_tabu5_cluster1_compare.pdf"
plot \
    "results/compare.txt" every 4::60::99 using 1:2 with linespoints title "Istanze 1 cluster TABU 5 - media", \
    "results/compare.txt" every 4::60::99 using 1:4 with linespoints title "Istanze 1 cluster TABU 5 - max"

set output "results/cplex_tabu6_cluster1_compare.pdf"
plot \
    "results/compare.txt" every 4::110::149 using 1:2 with linespoints title "Istanze 1 cluster TABU 6 - media", \
    "results/compare.txt" every 4::110::149 using 1:4 with linespoints title "Istanze 1 cluster TABU 6 - max"

set output "results/cplex_tabu7_cluster1_compare.pdf"
plot \
    "results/compare.txt" every 4::160::199 using 1:2 with linespoints title "Istanze 1 cluster TABU 7 - media", \
    "results/compare.txt" every 4::160::199 using 1:4 with linespoints title "Istanze 1 cluster TABU 7 - max"

set output "results/cplex_tabu8_cluster1_compare.pdf"
plot \
    "results/compare.txt" every 4::210::249 using 1:2 with linespoints title "Istanze 1 cluster TABU 8 - media", \
    "results/compare.txt" every 4::210::249 using 1:4 with linespoints title "Istanze 1 cluster TABU 8 - max"

set xrange [0:36]


set output "results/cplex_tabu4_cluster2_compare.pdf"
plot \
    "results/compare.txt" every 4::11::49 using 1:2 with linespoints title "Istanze 2 cluster TABU 4 - media", \
    "results/compare.txt" every 4::11::49 using 1:4 with linespoints title "Istanze 2 cluster TABU 4 - max"

set output "results/cplex_tabu5_cluster2_compare.pdf"
plot \
    "results/compare.txt" every 4::61::99 using 1:2 with linespoints title "Istanze 2 cluster TABU 5 - media", \
    "results/compare.txt" every 4::61::99 using 1:4 with linespoints title "Istanze 2 cluster TABU 5 - max"

set output "results/cplex_tabu6_cluster2_compare.pdf"
plot \
    "results/compare.txt" every 4::111::149 using 1:2 with linespoints title "Istanze 2 cluster TABU 6 - media", \
    "results/compare.txt" every 4::111::149 using 1:4 with linespoints title "Istanze 2 cluster TABU 6 - max"

set output "results/cplex_tabu7_cluster2_compare.pdf"
plot \
    "results/compare.txt" every 4::161::199 using 1:2 with linespoints title "Istanze 2 cluster TABU 7 - media", \
    "results/compare.txt" every 4::161::199 using 1:4 with linespoints title "Istanze 2 cluster TABU 7 - max"

set output "results/cplex_tabu8_cluster2_compare.pdf"
plot \
    "results/compare.txt" every 4::211::249 using 1:2 with linespoints title "Istanze 2 cluster TABU 8 - media", \
    "results/compare.txt" every 4::211::249 using 1:4 with linespoints title "Istanze 2 cluster TABU 8 - max"

set xrange [0:50]
set ytics 0, 2

set output "results/cplex_tabu4_cluster3_compare.pdf"
plot \
    "results/compare.txt" every 4::12::49 using 1:2 with linespoints title "Istanze 3 cluster TABU 4 - media", \
    "results/compare.txt" every 4::12::49 using 1:4 with linespoints title "Istanze 3 cluster TABU 4 - max"

set output "results/cplex_tabu5_cluster3_compare.pdf"
plot \
    "results/compare.txt" every 4::62::99 using 1:2 with linespoints title "Istanze 3 cluster TABU 5 - media", \
    "results/compare.txt" every 4::62::99 using 1:4 with linespoints title "Istanze 3 cluster TABU 5 - max"

set output "results/cplex_tabu6_cluster3_compare.pdf"
plot \
    "results/compare.txt" every 4::112::149 using 1:2 with linespoints title "Istanze 3 cluster TABU 6 - media", \
    "results/compare.txt" every 4::112::149 using 1:4 with linespoints title "Istanze 3 cluster TABU 6 - max"

set output "results/cplex_tabu7_cluster3_compare.pdf"
plot \
    "results/compare.txt" every 4::162::199 using 1:2 with linespoints title "Istanze 3 cluster TABU 7 - media", \
    "results/compare.txt" every 4::162::199 using 1:4 with linespoints title "Istanze 3 cluster TABU 7 - max"

set output "results/cplex_tabu8_cluster3_compare.pdf"
plot \
    "results/compare.txt" every 4::212::249 using 1:2 with linespoints title "Istanze 3 cluster TABU 8 - media", \
    "results/compare.txt" every 4::212::249 using 1:4 with linespoints title "Istanze 3 cluster TABU 8 - max"

set xrange [0:70]
set xtics 0, 4, 70

set output "results/cplex_tabu4_cluster4_compare.pdf"
plot \
    "results/compare.txt" every 4::13::49 using 1:2 with linespoints title "Istanze 4 cluster TABU 4 - media", \
    "results/compare.txt" every 4::13::49 using 1:4 with linespoints title "Istanze 4 cluster TABU 4 - max"

set output "results/cplex_tabu5_cluster4_compare.pdf"
plot \
    "results/compare.txt" every 4::63::99 using 1:2 with linespoints title "Istanze 4 cluster TABU 5 - media", \
    "results/compare.txt" every 4::63::99 using 1:4 with linespoints title "Istanze 4 cluster TABU 5 - max"

set output "results/cplex_tabu6_cluster4_compare.pdf"
plot \
    "results/compare.txt" every 4::113::149 using 1:2 with linespoints title "Istanze 4 cluster TABU 6 - media", \
    "results/compare.txt" every 4::113::149 using 1:4 with linespoints title "Istanze 4 cluster TABU 6 - max"

set output "results/cplex_tabu7_cluster4_compare.pdf"
plot \
    "results/compare.txt" every 4::163::199 using 1:2 with linespoints title "Istanze 4 cluster TABU 7 - media", \
    "results/compare.txt" every 4::163::199 using 1:4 with linespoints title "Istanze 4 cluster TABU 7 - max"

set output "results/cplex_tabu8_cluster4_compare.pdf"
plot \
    "results/compare.txt" every 4::213::249 using 1:2 with linespoints title "Istanze 4 cluster TABU 8 - media", \
    "results/compare.txt" every 4::213::249 using 1:4 with linespoints title "Istanze 4 cluster TABU 8 - max"