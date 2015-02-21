/**
 * @author  Marco Pezzutti - 1084411
 * @file    main.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include <iostream>
#include <fstream>
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
        if (argc < 5)
        {
            throw runtime_error("usage: ./main fileName.dat numIstanza tabuTenure maxIter"); 
        }
        
        int numIstanza = atoi(argv[2]);
        int tabuTenure = atoi(argv[3]);
        int maxIter = atoi(argv[4]);
        
        cout << "Istanza n. " << numIstanza << ", tabu tenure = " << tabuTenure 
            << " , max iter = " << maxIter << endl;
        
        // creo oggetto istanza del problema e la inizializzo
        Istanza* ist = new Istanza();
        ist->readFile(argv[1]);
        
        // creo oggetto soluzione
        Soluzione* sol = new Soluzione();

        // creo oggetto solutore
        Solutore* solver = new Solutore(*ist, *sol, tabuTenure, maxIter);
        
        // inizializzo il timer per il conteggio del tempo
        clock_t t1,t2;
        t1 = clock();
        struct timeval  tv1, tv2;
        gettimeofday(&tv1, NULL);

        // risolvo il problema
        solver->tabuSearch();

        // prendo il tempo di fine calcolo
        t2 = clock();
        gettimeofday(&tv2, NULL);

        // stampo la soluzione
        cout << "Soluzione finale" << endl;
        sol->stampa();

        // calcolo costo soluzione
        double costo = sol->calcolaCosto(*ist);

        // stampo messaggi informativi
        cout << "Costo = " << costo << endl;
        cout << (double)(tv2.tv_sec+tv2.tv_usec*1e-6 - (tv1.tv_sec+tv1.tv_usec*1e-6)) << " seconds (user time)\n";
        cout << (double)(t2-t1) / CLOCKS_PER_SEC << " seconds (CPU time)\n";

        // creo file dei risultati
        ofstream out("../results/TABUresults.txt", ofstream::app);
        out << "Istanza n. " << numIstanza << " composta da " 
            << ist->getNumNodi() << " nodi, tabu tenure = " << tabuTenure 
            << ", numero iterazioni = " << maxIter << "\n";
        out << "Soluzione " << costo << " trovata in:\n";
        out << (double)(tv2.tv_sec+tv2.tv_usec*1e-6 - (tv1.tv_sec+tv1.tv_usec*1e-6)) << " seconds (user time)\n";
        out << (double)(t2-t1) / CLOCKS_PER_SEC << " seconds (CPU time)\n\n";
        out.close();

        // creo file risultati per gnuplot
        ofstream out2("../results/TABUsimple_results.txt", ofstream::app);
        out2 << numIstanza << "\t" << ist->getNumNodi() << "\t" 
            << (double)(t2-t1) / CLOCKS_PER_SEC << "\t"
            << costo << "\t" << tabuTenure << "\t" << maxIter << endl;
        out2.close();

    }
    catch(std::exception& e)
    {
        cout << ">>>EXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}