/**
 * @author  Marco Pezzutti - 1084411
 * @file    main.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <sys/time.h>

#include "istanza.h"
#include "soluzione.h"
#include "solutore.h"
#include "mossa.h"

using namespace std;

int main(int argc, char const *argv[])
{
    try
    {
    if (argc < 4) throw std::runtime_error("usage: ./main fileName.dat tabuTenure maxIter"); 
        
        // creo oggetto istanza del problema e la inizializzo
        Istanza* ist = new Istanza();
        ist->readFile(argv[1]);

        // creo oggetto soluzione
        Soluzione* sol = new Soluzione();

        // creo oggetto solutore
        int tabuTenure = atoi(argv[2]);
        int maxIter = atoi(argv[3]);
        cout << "tabu tenure = " << tabuTenure << " , max iter = " << maxIter << endl;
        Solutore* solver = new Solutore(*ist, *sol, tabuTenure, maxIter);
        
        // inizializzo il timer per il conteggio del tempo
        clock_t t1,t2;
        t1 = clock();
        struct timeval  tv1, tv2;
        gettimeofday(&tv1, NULL);

        // risolvo il problema
        solver->tabuSearch();
        cout << "\nSoluzione finale" << endl;
        sol->stampa();
        
        // prendo il tempo di fine calcolo
        t2 = clock();
        gettimeofday(&tv2, NULL);

        // calcolo costo soluzione
        double costo = sol->calcolaCosto(*ist);

        // stampo messaggi informativi
        cout << "\nCosto soluzione = " << costo << endl;
        std::cout << (double)(tv2.tv_sec+tv2.tv_usec*1e-6 - (tv1.tv_sec+tv1.tv_usec*1e-6)) << " seconds (user time)\n";
        std::cout << (double)(t2-t1) / CLOCKS_PER_SEC << " seconds (CPU time)\n";
    }
    catch(std::exception& e)
    {
        std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}