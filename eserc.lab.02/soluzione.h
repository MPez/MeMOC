/**
 * @author  Marco Pezzutti - 1084411
 * @file    soluzione.h
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#ifndef SOLUZIONE_H
#define SOLUZIONE_H

#include <vector>
#include "istanza.h"

class Soluzione
{
public:
    /**
    * costruttore
    */
    Soluzione();

    /**
    * getter soluzione corrente
    * @return soluzione corrente
    */
    std::vector<int> getSoluzione() const;

    /**
    * setter soluzione
    */
    void setSoluzione(std::vector<int> sol);

    /**
    * inizializza la soluzione con nodi in ordine crescente
    * @param istanza istanza del problema
    */
    void initSoluzione(const Istanza& istanza);

    /**
    * scambia posizione di due nodi
    * @param nodo1 primo nodo da scambiare
    * @param nodo2 secondo nodo da scambiare
    */
    void scambiaNodi(int pos1, int pos2);
    
private:
    /**
    * sequenza di nodi (path representation) che identifica la soluzione
    */
    std::vector<int> soluzione;
};

 #endif /* SOLUZIONE_H */