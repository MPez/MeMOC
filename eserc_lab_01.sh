#!/bin/bash

# elimino file dei risultati
rm "results.txt"
rm "plot_results.txt"

# dimensione del pannello
x_dim=15
y_dim=15

# nomi script per generare pannelli e opzioni
gen_script="generator.py"
dim_opt="-d $x_dim $y_dim"

# nome cartella istanze
ins_dir="instances/"

# nome file ed estensione delle istanze
ins_name="pannello"
suff=".dat"

# nome script per calcolare statistiche
stat_script="statistics.py"

# nome file gnuplot
plot="plot.gnuplot"

# densità dei fori da creare
dens=5

# indici per la creazione delle istanze
i=1
I=0

# numero di problemi da generare
N=99

# creazione problemi casuali
crea_casuali() {
    ((I = $i + $N))
    while [[ $i -le $I ]]; do
        for (( j = 1; j <= 10; j++ )); do
            command="$gen_script $dim_opt -t casuale -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        ((dens += 2))
    done
}

# creazione problemi cluster
crea_cluster() {
    ((I = $N * 4 + $i))
    while [[ $i -le $I ]]; do
        # 1 cluster
        for (( j = 0; j < 10; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 1 -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 2 cluster
        for (( j = 0; j < 10; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 2 -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 3 cluster
        for (( j = 0; j < 10; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 3 -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 4 cluster
        for (( j = 0; j < 10; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 4 -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        ((dens += 1))
    done
}

# creazione problemi circolari
crea_circolari() {
    ((I = $i + 9))
    while [[ $i -le $I ]]; do
        command="$gen_script -d $x_dim $y_dim -t circolare -i $i"
        python $command
        echo "Create $i istanze"
        ((x_dim += 2))
        ((y_dim += 2))
        ((i += 1))
    done
}


# risolvo le istanze create tramite cplex
risolvi_cplex() {
    echo "Risolvo istanze con cplex"
    for (( k = 1; k < i; k++ )); do
        instance=$ins_dir$ins_name$k$suff
        ./main $instance $k
    done
}

# calcola statistiche e stampa file per gnuplot
calcola_statistiche() {
    echo "Calcolo statistiche sui risultati ottenuti"
    python $stat_script
}

# esegue gnuplot per creare i grafici
crea_grafici() {
    echo "Creo grafici con gnuplot"
    gnuplot $plot
}

# main
while getopts ":acgilrs" flag; do
    case $flag in
        a )
            crea_casuali
            # densità dei fori da creare
            dens=5
            crea_cluster
            # dimensioni del pannello
            x_dim=5
            y_dim=5
            crea_circolari
            risolvi_cplex
            calcola_statistiche
            crea_grafici
            ;;
        c )
            crea_casuali
            ;;
        g )
            crea_grafici
            ;;
        i )
            # dimensioni del pannello
            x_dim=5
            y_dim=5
            crea_circolari
            ;;
        l )
            # densità dei fori da creare
            dens=5
            crea_cluster
            ;;
        r )
            risolvi_cplex
            ;;
        s )
            calcola_statistiche
            ;;
        * )
            echo "Opzione non presente, nessuna operazione da svolgere."
            ;;
    esac
done