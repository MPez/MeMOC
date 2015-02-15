/**
 * @author  Marco Pezzutti - 1084411
 * @file    solutore.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include "solutore.h"

Solutore::Solutore(const Istanza& ist, Soluzione sol) 
    : istanza(ist), soluzione(sol) {}

void Solutore::startSoluzione()
{
    int N = istanza->getNumNodi();
    // nodi 
    int i = 0;
    int j = 0;
    // nodi presenti nel ciclo
    std::vector<int> selezionati;
    // nodi non ancora selezionati
    std::vector<char> rimanenti(N);
    for (int r = 0; r < N; ++r)
    {
        rimanenti[r] = r;
    }
    // calcolo prima coppia di nodi e li inserisco nel ciclo
    istanza->maxCosto(i, j);
    selezionati.push_back(i);
    selezionati.push_back(j);
    // rimuovo i nodi selezionati dai rimanenti
    rimanenti.erase(rimanenti.at(i));
    rimanenti.erase(rimanenti.at(j));
    while(!rimanenti.empty())
    {
        // cerco nodo da inserire con costo massimo
        int r = istanza->maxCosto(selezionati, rimanenti);
        // cerco posizione dove inserire il nodo selezionato
        istanza->minCosto(r, i, j, selezionati);
        // inserisco nodo selezionato
        selezionati.insert(selezionati.at(j), r);
        //rimuovo nodo selezionato dai rimanenti
        for (int n = 0; n < rimanenti.size(); ++n)
        {
            if(rimanenti[n] = r)
            {
                rimanenti.erase(rimanenti.at(n));
            }
        }
    }
    soluzione.setSoluzione(selezionati);
}

