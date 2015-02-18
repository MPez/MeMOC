/**
 * @author  Marco Pezzutti - 1084411
 * @file    solutore.h
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#ifndef SOLUTORE_H
#define SOLUTORE_H

#include <vector>
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
    * tabu list
    */
    std::vector<Mossa> tabuList;

    /**
    * massimo numero di iterazioni per tabu search
    */
    int maxIter;

    /**
    * determina la soluzione di partenza mediante farthest insertion
    */
    void startSoluzione();

    /**
    * cerca il miglor vicino
    * @param solCorrente soluzione corrente
    * @param mossa mossa per ottenere al miglior vicino
    + @param bestCosto miglor costo di soluzione trovato
    + @param currCosto costo corrente
    */
    void trovaVicino(const Soluzione& solCorrente, Mossa& mossa,
                       double& bestCosto, double& currCosto) const;

    /**
    * controlla se una mossa è presente nella tabu list
    * @param mossa mossa da controllare
    * @param true se la mossa è tabu, false altrimenti
    */
    bool controllaMossa(const Mossa& mossa) const;

    /**
    * aggiunge una mossa alla tabu list e rimuove la meno recente se necessario
    * @param mossa mossa da aggiungere
    */
    void inserisciMossaTabu(const Mossa& mossa);
};

#endif /* SOLUTORE_H */