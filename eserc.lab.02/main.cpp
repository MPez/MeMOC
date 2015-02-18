/**
 * @author  Marco Pezzutti - 1084411
 * @file    main.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include <iostream>
#include <cstdlib>
#include "istanza.h"
#include "soluzione.h"
#include "solutore.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // creo oggetto istanza del problema e la inizializzo
    Istanza* ist = new Istanza();
    ist->readFile(argv[1]);
    ist->stampa();
    // creo oggetto soluzione
    Soluzione* sol = new Soluzione();
    // creo oggetto solutore
    int tabuTenure = atoi(argv[2]);
    int maxIter = atoi(argv[3]);
    cout << "tabu tenure = " << tabuTenure << " , max iter = " << maxIter << endl;
    Solutore* solver = new Solutore(*ist, *sol, tabuTenure, maxIter);
    // risolvo il problema
    solver->tabuSearch();
    sol->stampa();
    // calcolo costo soluzione
    double costo = sol->calcolaCosto(*ist);
    cout << "Costo soluzione = " << costo << endl;

    return 0;
}