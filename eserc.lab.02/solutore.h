/**
 * @author  Marco Pezzutti - 1084411
 * @file    solutore.h
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#ifndef SOLUTORE_H
#define SOLUTORE_H

#include <set>
#include <limits>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "soluzione.h"
#include "istanza.h"
#include "mossa.h"

class Solutore
{
public:
    /**
    * costruttore
    */
    Solutore(const Istanza& ist, Soluzione& sol, int tabuTenure, int maxIt);

    /**
    * risolve il problema tramite l'euristica tabu search
    */
    void tabuSearch();

    /**
    * oggetto funzione (funtore) per comparare due mosse
    */
    struct compMossa
    {
        bool operator()(const Mossa& a, const Mossa& b) const;
    };
    
private:
    /**
    * istanza del problema
    */
    const Istanza& istanza;

    /**
    * soluzione del problema
    */
    Soluzione& soluzione;

    /**
    * vettore delle mosse tabu
    */
    std::vector<Mossa> tabuList;

    /**
    * insieme di mosse ordinate in ordine crescente di costo
    */
    std::set<Mossa, compMossa> mosseMigliori;

    /**
    * massimo numero di iterazioni per tabu search
    */
    int maxIter;

    /**
    * determina la soluzione di partenza mediante farthest insertion
    * @param strategia strategia di creazione soluzione di partenza
    */
    void startSoluzione(std::string strategia);

    /**
    * cerca tutti i vicini che non sono tabu
    * @param solCorrente soluzione corrente
    */
    void trovaVicini(const Soluzione& solCorrente, std::string strategia);

    /**
    * sceglie il vicino sul quale spostarsi
    * @param strategia strategia di selezione miglior vicino
    * @return la mossa da eseguire per ottenere il vicino
    */
    Mossa scegliVicino(std::string strategia) const;

    /**
    * controlla se una mossa è presente nella tabu list
    * @param mossa mossa da controllare
    * @return true se la mossa è tabu, false altrimenti
    */
    bool controllaMossa(const Mossa& mossa) const;

    /**
    * aggiunge una mossa alla tabu list e rimuove la meno recente se necessario
    * @param mossa mossa da aggiungere
    */
    void inserisciMossaTabu(const Mossa& mossa);
};

#endif /* SOLUTORE_H */