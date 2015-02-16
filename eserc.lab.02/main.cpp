/**
 * @author  Marco Pezzutti - 1084411
 * @file    main.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include "istanza.h"
#include "soluzione.h"
#include "solutore.h"

int main(int argc, char const *argv[])
{
    // creo l'istanza del problema e la inizializzo
    Istanza* ist = new Istanza();
    ist->readFile(argv[1]);
    ist->stampa();
    // creo la soluzione
    Soluzione* sol = new Soluzione();
    // creo il solutore
    Solutore* solver = new Solutore(*ist, *sol);
    // risolvo il problema
    solver->startSoluzione();
    sol->stampa();

    return 0;
}