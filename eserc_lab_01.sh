#!/bin/bash

# dimensione del pannello
x_dim=15
y_dim=15

# nomi script per generare pannelli e opzioni
gen_script="generator.py"
dim_opt="-d $x_dim $y_dim"

# nomi cartelle istanze, risultati, soluzioni
ins_dir=""
res_dir=""
sol_dir=""

# nomi file risultati
res_name="results.txt"
simp_name="simple_results.txt"

# nome file ed estensione delle istanze
ins_name="pannello"
suff=".dat"

# nome script per calcolare statistiche
stat_script="statistic.py"

# nome file gnuplot
plot="plot.gnuplot"

# densità dei fori da creare
dens=5

# numero di ripetizioni stesso problema
R=0

# numero di problemi da generare per tipologia
N=0

# indici per la creazione delle istanze
i=1
I=0

# creazione problemi casuali
crea_casuali() {
    ((I = i + N))
    while [[ $i -le $I ]]; do
        for (( j = 1; j <= R; j++ )); do
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
    ((I = N * 4 + i))
    while [[ $i -le $I ]]; do
        # 1 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 1 -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 2 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 2 -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 3 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 3 -n $dens -i $i"
            python $command
            ((i += 1))
        done
        echo "Create $i istanze"
        # 4 cluster
        for (( j = 0; j < R; j++ )); do
            command="$gen_script $dim_opt -t cluster -c 4 -n $dens -i $i"
            python $command
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
        python $command
        (( x_dim += 2 ))
        (( y_dim += 2 ))
        (( i += 1 ))
        echo "Create $i istanze"
    done
}


# risolvo le istanze create tramite cplex
risolvi_cplex() {
    echo "Risolvo istanze con cplex"
    if [[ $i -eq 0 ]]; then
        $i = $1
    fi
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
}

# elimino file dei risultati
remove_results() {
    cd $res_dir
    if [[  -a $res_name ]]; then
        rm $res_name
    fi
    if [[  -a $simp_name ]]; then
        rm $simp_name
    fi
    cd ../
}

# imposta numero di problemi da generare
imposta_problemi() {
    R=$OPTARG
    (( N = R*10 - 1 ))

}

# main
while getopts ":a:c:gi:l:r:s" flag; do
    case $flag in
        a )
            crea_cartelle
            remove_results
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
            calcola_statistiche
            crea_grafici
            ;;
        c ) 
            crea_cartelle
            remove_results
            imposta_problemi $OPTARG
            crea_casuali 
            ;;
        g )
            crea_grafici
            ;;
        i )
            crea_cartelle
            remove_results
            imposta_problemi $OPTARG
            # dimensioni del pannello
            x_dim=5
            y_dim=5
            crea_circolari
            ;;
        l )
            crea_cartelle
            remove_results
            imposta_problemi $OPTARG
            # densità dei fori da creare
            dens=5
            crea_cluster
            ;;
        r )
            crea_cartelle
            remove_results
            risolvi_cplex $OPTARG
            ;;
        s )
            calcola_statistiche
            ;;
        * )
            echo "Opzione non presente, nessuna operazione da svolgere."
            ;;
    esac
done