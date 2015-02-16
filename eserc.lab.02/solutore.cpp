/**
 * @author  Marco Pezzutti - 1084411
 * @file    solutore.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include <set>
#include "solutore.h"

Solutore::Solutore(const Istanza& ist, Soluzione& sol) 
    : istanza(ist), soluzione(sol) {}

void Solutore::startSoluzione()
{
    int N = istanza.getNumNodi();
    // riferimenti da usare per selezionare i nodi da aggiungere o rimuovere
    int i = 0;
    int j = 0;
    // insieme dei nodi presenti nel ciclo
    std::vector<int> selezionati;
    // insiede dei nodi non ancora selezionati
    std::set<int> rimanenti;
    for (int r = 0; r < N; ++r)
    {
        rimanenti.insert(r);
    }
    // calcolo la prima coppia di nodi e li inserisco nel ciclo
    istanza.maxCosto(i, j);
    selezionati.push_back(i);
    selezionati.push_back(j);
    // rimuovo i nodi selezionati dai rimanenti
    rimanenti.erase(i);
    rimanenti.erase(j);
    while(!rimanenti.empty())
    {
        // cerco nodo da inserire con costo massimo
        int r = istanza.maxCosto(selezionati, rimanenti);
        // cerco posizione dove inserire il nodo selezionato
        istanza.minCosto(r, i, j, selezionati);
        // inserisco nodo selezionato
        selezionati.insert(selezionati.begin() + j, r);
        //rimuovo nodo selezionato dai rimanenti
        rimanenti.erase(r);    
    }
    soluzione.setSoluzione(selezionati);
}

