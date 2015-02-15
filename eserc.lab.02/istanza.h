/**
 * @author  Marco Pezzutti - 1084411
 * @file    istanza.h
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#ifndef ISTANZA_H
#define ISTANZA_H

#include <vector>

class Istanza
{
public:
    /**
    * costruttore
    */
    Istanza();

    /**
    * getter numero nodi
    * @return numNodi numero di nodi
    */
    int getNumNodi() const;

    /**
    * getter costo relativo ad un arco dal nodo i al nodo j
    * @param i riga della matrice dei costi
    * @param j colonna della matrice dei costi
    * @return costo dell'arco da i a j
    */
    std::vector<std::vector<double>>& getCosti(int i, int j) const;

    /**
    * cerca il costo più alto tra tutti gli archi
    * @param i nodo di partenza dell'arco
    * @param j nooo di arrivo dell'arco
    */
    void maxCosto(int& i, int& j);

    /**
    * cerca il costo più alto tra gli archi che uniscono un nodo
    * tra quelli selezionati e uno tra quelli rimanenti
    * @param selezionati nodi presenti nel ciclo
    * @param rimanenti nodi non ancora selezionati
    * @return nodo con costo più alto da inserire nel ciclo
    */
    int maxCosto(std::vector<int>& selezionati,
                    std::vector<int>& rimanenti);

    /**
    * cerca i nodi i e j tra i quali inserire a costo minimo il nodo r
    * @param r nodo da inserire nel ciclo
    * @param i nodo che deve precedere r
    * @param j nodo che deve seguire r
    * @param selezionati nodi presenti nel ciclo
    */
    void minCosto(int& r, int& i, int& j, std::vector<int>& selezionati);

    /**
    * legge il file con l'istanza del problema e 
    * inizializza la matrice dei costi
    * @param fileName nome del file relativo all'istanza
    */
    void readFile(const char* fileName);

private:
    /**
    * numero di nodi
    */
    int numNodi;

    /**
    * costi di cammino
    */ 
    std::vector<std::vector<double>> costi; 
};

#endif /* ISTANZA_H */