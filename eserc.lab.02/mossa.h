/**
 * @author  Marco Pezzutti - 1084411
 * @file    mossa.h
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#ifndef MOSSA_H
#define MOSSA_H

class Mossa
{
public:
    /**
    * costruttore
    */
    Mossa(int from=0, int to=0, double costo=0);

    /**
    * overloading operatore ==
    */
    bool operator==(const Mossa mossa) const;

    /**
    * nodo di partenza
    */
    int from;

    /**
    * nodo di arrivo
    */
    int to;

    /**
    * costo della soluzione effettuando la mossa
    */
    double costo;
};

#endif /* MOSSA_H */