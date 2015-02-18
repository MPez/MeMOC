/**
 * @author  Marco Pezzutti - 1084411
 * @file    solutore.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include <set>
#include <limits>
#include <iostream>
#include "solutore.h"

const double infinito = std::numeric_limits<double>::max();

Solutore::Solutore(const Istanza& ist, Soluzione& sol,
                   int tabuTenure, int maxIt) 
    : istanza(ist), soluzione(sol), tabuList(tabuTenure), maxIter(maxIt) {}

void Solutore::startSoluzione()
{
    // riferimenti da usare per selezionare i nodi da aggiungere o rimuovere
    int i = 0;
    int j = 0;
    // insieme dei nodi presenti nel ciclo
    std::vector<int> selezionati;
    // insiede dei nodi non ancora selezionati
    std::set<int> rimanenti;
    for (int n = 0; n < istanza.getNumNodi(); ++n)
    {
        rimanenti.insert(n);
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
    // inserisco come ultimo nodo quello di partenza per chiudere il ciclo
    selezionati.push_back(0);
    soluzione.setSoluzione(selezionati);
}

void Solutore::trovaVicino(const Soluzione& solCorrente, Mossa& mossa,
                             double& bestCosto, double& currCosto) const
{
    int size = solCorrente.getSoluzione().size();
    for (int i = 1; i <  size - 2; ++i)
    {
        for (int j = i + 1; j < size - 1; ++j)
        {
            currCosto = solCorrente.calcolaCostoVicino(istanza, i, j);
            if (currCosto < bestCosto)
            {
                mossa.to = i;
                mossa.from = j;
                bestCosto = currCosto;
                
            }
        }
    }
}

bool Solutore::controllaMossa(const Mossa& mossa) const
{
    bool tabu = false;
    for (int i = 0; i < tabuList.size(); ++i)
    {
        if (tabuList[i] == mossa)
        {
            tabu = true;
        }
    }
    return tabu;
}

void Solutore::inserisciMossaTabu(const Mossa& mossa)
{
    if (tabuList.size() == tabuList.capacity())
        {
            tabuList.pop_back();
        }
    tabuList.insert(tabuList.begin(), mossa);
}

void Solutore::tabuSearch()
{
    // genero soluzione iniziale
    startSoluzione();
    // numero iterazione corrente
    int k = 0;
    // soluzione corrente
    Soluzione* solCorrente = new Soluzione(soluzione);
    // costo soluzione corrente
    double costo = solCorrente->calcolaCosto(istanza);
    // costo migliore e corrente
    double bestCosto = infinito;
    double currCosto = 0;
    // variabile di controllo ciclo
    bool terminato = false;
    while(!terminato)
    {
        // cerco il miglior vicino
        Mossa mossa = Mossa();
        trovaVicino(*solCorrente, mossa, bestCosto, currCosto);
        // controllo che la mossa migliore non sia tabu
        bool mossaTabu = controllaMossa(mossa);
        // se la mossa è valida e migliorativa la eseguo e aggiorno la tabu list
        if (!mossaTabu)
        {
            if (bestCosto < costo)
            {
                solCorrente->invertiNodi(mossa.to, mossa.from);
            }
            inserisciMossaTabu(mossa);
        }
        if (k == maxIter)
        {
            terminato = true;
        }
        k++;
    }
    soluzione = *solCorrente;
}

