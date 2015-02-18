/**
 * @author  Marco Pezzutti - 1084411
 * @file    soluzione.h
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#ifndef SOLUZIONE_H
#define SOLUZIONE_H

#include <vector>
#include <iostream>

#include "istanza.h"

class Soluzione
{
public:
    /**
    * costruttore
    */
    Soluzione();

    /**
    * costruttore di copia
    */
    Soluzione(const Soluzione& sol);

    /**
    * overloading operatore =
    */
    Soluzione& operator=(const Soluzione& sol);

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
    * inverte la sottosequenza di nodi tra le due posizioni
    * @param pos1 posizione di partenza della sequenza
    * @param pos1 posizione di arrivo della sequenza
    */
    void invertiNodi(int pos1, int pos2);

    /**
    * calcola il costo della soluzione
    * @param istanza istanza del problema
    * @return costo della soluzione
    */
    double calcolaCosto(const Istanza& istanza) const;

    /**
    * calcola il costo di un vicino
    * @param istanza istanza del problema
    * @param i posizione nodo di inizio sottosequenza da scambiare
    * @param j posizione nodo di fine sottosequenza da scambiare
    * @return costo del vicino
    */
    double calcolaCostoVicino(const Istanza& istanza, int i, int j) const;

    /**
    * stampa la soluzione corrente
    */
    void stampa() const;

private:
    /**
    * sequenza di nodi (path representation) che identifica la soluzione
    */
    std::vector<int> soluzione;
};

 #endif /* SOLUZIONE_H */