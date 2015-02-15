/**
 * @author  Marco Pezzutti - 1084411
 * @file    solutore.h
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#ifndef SOLUTORE_H
#define SOLUTORE_H

#include "soluzione.h"

class Solutore
{
public:
    /**
    * costruttore
    */
    Solutore(const Istanza& ist, Soluzione& sol);

    /**
    * determina la soluzione di partenza mediante farthest insertion
    */
    void startSoluzione();
    
private:
    /**
    * istanza del problema
    */
    const Istanza& istanza;
    /**
    * soluzione del problema
    */
    Soluzione& soluzione;
};

#endif /* SOLUTORE_H */