#!/bin/bash

# elimino file dei risultati
rm "results.txt"

# dimensione del pannello
x_dim=15
y_dim=15

# nomi script per generare pannelli e opzioni
script="generator.py"
dim_opt="-d $x_dim $y_dim"

# densità dei fori da creare
dens=10

# indice per la creazione delle istanze
i=1

# creazione problemi casuali
while [[ $i -le 100 ]]; do
    for (( j = 1; j <= 10; j++ )); do
        command="$script $dim_opt -t casuale -n $dens -i $i"
        python $command
        ((i += 1))
    done
    ((dens += 2))
done

# densità dei fori da creare
dens=5

# creazione problemi cluster
while [[ $i -le 500 ]]; do
    # 1 cluster
    for (( j = 0; j < 10; j++ )); do
        command="$script $dim_opt -t cluster -c 1 -n $dens -i $i"
        python $command
        ((i += 1))
    done
    # 2 cluster
    for (( j = 0; j < 10; j++ )); do
        command="$script $dim_opt -t cluster -c 2 -n $dens -i $i"
        python $command
        ((i += 1))
    done
    # 3 cluster
    for (( j = 0; j < 10; j++ )); do
        command="$script $dim_opt -t cluster -c 3 -n $dens -i $i"
        python $command
        ((i += 1))
    done
    # 4 cluster
    for (( j = 0; j < 10; j++ )); do
        command="$script $dim_opt -t cluster -c 4 -n $dens -i $i"
        python $command
        ((i += 1))
    done
    ((dens += 1))
done

# dimensioni del pannello
x_dim=5
y_dim=5

# creazione problemi circolari
while [[ $i -le 510 ]]; do
    command="$script -d $x_dim $y_dim -t circolare -i $i"
    python $command
    ((x_dim += 2))
    ((y_dim += 2))
done

# nome cartella istanze
ins_dir="instances/"
# nome file ed estensione
ins_name="pannello"
suff=".dat"

# risolvo le istanze create tramite cplex
for (( k = 1; k <= i; ++ )); do
    instance=$ins_dir$ins_name$i$suff
    ./main $instance $k
done

