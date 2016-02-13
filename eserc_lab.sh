#!/bin/bash

# dimensione del pannello
x_dim=15
y_dim=15

# nomi script per generare pannelli e opzioni
gen_script="generator.py"
dim_opt="-d $x_dim $y_dim"

# nomi cartelle istanze, risultati, soluzioni
ins_dir=""
ins_dir_tabu=""
res_dir=""
sol_dir=""

# nome cartella tabu search
tabu_dir="eserc.lab.02/"

# nomi file risultati
res_name="CPXresults.txt"
simp_name="CPXsimple_results.txt"
res_name_tabu="TABUresults.txt"
simp_name_tabu="TABUsimple_results.txt"

# nome file ed estensione delle istanze
ins_name="pannello"
suff=".dat"

# nome script per calcolare statistiche
stat_script="statistic.py"

# nome file gnuplot
plot="plot.gnuplot"

# densità dei fori da creare
dens=5
# numero di ripetizioni stesso problema per cplex
R=0
# numero di problemi da generare per tipologia
N=0
# indici per la creazione delle istanze
i=1
I=0

# numero di problemi da risolvere con tabu search (solo casuali)
T=0
# tabu tenure
tt=4
# numero iterazione tabu search
it=150

# creazione problemi casuali
crea_casuali() {
    ((I = i + N))
    while [[ $i -le $I ]]; do
        for (( j = 1; j <= R; j++ )); do
            command="$gen_script $dim_opt -t casuale -n $dens -i $i"
            python3 $command
            ((i += 1))
        done
        echo "Create $i istanze"
        ((dens += 2))
    done
}

# creazione problemi cluster
crea_cluster() {
    ((I = N * 4 + i))
    while [[ $i -le $I ]]; do
        # 1 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 1 -n $dens -i $i"
            python3 $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 2 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 2 -n $dens -i $i"
            python3 $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 3 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 3 -n $dens -i $i"
            python3 $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 4 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 4 -n $dens -i $i"
            python3 $command
            ((i += 1))
        done
        echo "Create $i istanze"
        ((dens += 3))
    done
}

# creazione problemi circolari
crea_circolari() {
    ((  I = i + R - 1 ))
    while [[ $i -le $I ]]; do
        command="$gen_script -d $x_dim $y_dim -t circolare -i $i"
        python3 $command
        (( x_dim += 2 ))
        (( y_dim += 2 ))
        (( i += 1 ))
        echo "Create $i istanze"
    done
}

# risolvo le istanze create tramite cplex
risolvi_cplex() {
    echo "Risolvo istanze con cplex"
    if [[ $i -eq 1 ]]; then
        a=$1
        ((i = a * 10 + 1))
    fi
    for (( k = 1; k < i; k++ )); do
        instance=$ins_dir$ins_name$k$suff
        ./cplex $instance $k
    done
}

# risolvo le istanze create tramite tabu search
risolvi_tabu() {
    echo "Risolvo istanze con tabu search"
    (( T = R*10 + (N+1)*4 + 1))
    #(( T = R*10 + 1))
    cd $tabu_dir
    for (( h = tt; h <= tt + 4; h++ )); do
        for (( k = 1; k < T; k++ )); do
            for (( j = 0; j < 20; j++ )); do
                instance=$ins_dir_tabu$ins_name$k$suff
                ./tabusearch $instance $k $h $it
            done
        done
    done
    cd ../
}

# calcola statistiche e stampa file per gnuplot
calcola_statistiche() {
    echo "Calcolo statistiche sui risultati ottenuti"
    python3 $stat_script
}

# esegue gnuplot per creare i grafici
crea_grafici() {
    echo "Creo grafici con gnuplot"
    gnuplot $plot
}

# crea cartelle dove inserire file di risultati
crea_cartelle() {
    res_dir="results/"
    sol_dir="solutions/"
    ins_dir="instances/"
    if [[ ! -d $res_dir ]]; then
        mkdir $res_dir
    fi
    if [[ ! -d $sol_dir ]]; then
        mkdir $sol_dir
    fi
    if [[ ! -d $ins_dir ]]; then
        mkdir $ins_dir
    fi
    ins_dir_tabu="../instances/"
}

# elimino file dei risultati cplex
remove_results_cplex() {
    cd $res_dir
    if [[  -a $res_name ]]; then
        rm $res_name
    fi
    if [[  -a $simp_name ]]; then
        rm $simp_name
    fi
    cd ../
}

# elimino file dei risultati tabu search
remove_results_tabu() {
    cd $res_dir
    if [[  -a $res_name_tabu ]]; then
        rm $res_name_tabu
    fi
    if [[  -a $simp_name_tabu ]]; then
        rm $simp_name_tabu
    fi
    cd ../
}

# imposta numero di problemi da generare
imposta_problemi() {
    R=$1
    (( N = R*10 - 1 ))
}

# main
while getopts ":a:c:gi:l:r:st:" flag; do
    case $flag in
        a ) # all
            crea_cartelle
            remove_results_cplex
            remove_results_tabu
            imposta_problemi $OPTARG
            crea_casuali
            # densità dei fori da creare
            dens=5
            crea_cluster
            # dimensioni del pannello
            x_dim=5
            y_dim=5
            crea_circolari
            risolvi_cplex
            risolvi_tabu
            calcola_statistiche
            crea_grafici
            ;;
        c ) # casuali
            crea_cartelle
            remove_results_cplex
            imposta_problemi $OPTARG
            crea_casuali 
            ;;
        g ) # gnuplot
            crea_grafici
            ;;
        i ) # circolari
            crea_cartelle
            remove_results_cplex
            imposta_problemi $OPTARG
            # dimensioni del pannello
            x_dim=5
            y_dim=5
            crea_circolari
            ;;
        l ) # cluster
            crea_cartelle
            remove_results_cplex
            imposta_problemi $OPTARG
            # densità dei fori da creare
            dens=5
            crea_cluster
            ;;
        r ) # cplex
            crea_cartelle
            remove_results_cplex
            imposta_problemi $OPTARG
            risolvi_cplex $OPTARG
            ;;
        s ) # statistiche
            calcola_statistiche
            ;;
        t ) # tabu search
            crea_cartelle
            remove_results_tabu
            imposta_problemi $OPTARG
            risolvi_tabu
            ;;
        * )
            echo "Opzione non presente, nessuna operazione da svolgere."
            ;;
    esac
done