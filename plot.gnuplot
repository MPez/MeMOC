set title "Optimal solution times"
set terminal pdf
set xlabel "Numero nodi"
set ylabel "Tempo (s)"
set pointsize 1
set xtics rotate

set output "risultati/insert_length1.pdf"
plot "risultati/insert_length.txt" every ::1::50000 using 1:3 with dots title "Inserti da 1 a 50000"
