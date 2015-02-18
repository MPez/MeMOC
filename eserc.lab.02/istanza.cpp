/**
 * @author  Marco Pezzutti - 1084411
 * @file    istanza.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include <fstream>
#include <string>
#include <limits>
#include <set>
#include <iterator>
#include <iostream>
#include "istanza.h"

const double infinito = std::numeric_limits<double>::max();

Istanza::Istanza() {}

double Istanza::getCosti(int i, int j) const
{
    return costi[i][j];
}

int Istanza::getNumNodi() const
{
    return numNodi;
}

void Istanza::maxCosto(int& i, int& j) const
{
    double max = 0;
    for (int r = 0; r < numNodi - 1; ++r)
    {
        for (int c = r + 1; c < numNodi; ++c)
        {
            if (costi[r][c] > max)
            {
                max = costi[r][c];
                i = r;
                j = c;
            }
        }
    }
}

int Istanza::maxCosto(const std::vector<int>& selezionati,
                      const std::set<int>& rimanenti) const
{
    double max = 0;
    int i = 0;
    int j = 0;
    int r = 0;
    for (std::set<int>::iterator it = rimanenti.begin();
         it != rimanenti.end(); ++it)
    {
        i = *it;
        for (int n = 0; n < selezionati.size(); ++n)
        {
            j = selezionati[n];
            if (costi[i][j] > max)
            {
                max = costi[i][j];
                r = i;
            }
        }
    }
    return r;
}

void Istanza::minCosto(int& r, int& i, int& j,
                       const std::vector<int>& selezionati) const
{
    double min = infinito;
    for (int m = 0; m < selezionati.size() - 1; ++m)
    {
        for (int n = m + 1; n < selezionati.size(); ++n)
        {
            double costo = costi[m][r] + costi[r][n] - costi[m][n];
            if(costo < min)
            {
                min = costo;
                i = m;
                j = n;
            }
        }
    }
}

void Istanza::readFile(const char* fileName)
{
   std::ifstream in(fileName);
   // lettura numero di nodi
   in >> numNodi;
   // ignora riga che contiene identificativo di ogni nodo
   for (int i = 0; i < numNodi; ++i)
   {
       int temp;
       in >> temp;
   }
   // lettura costi di cammino per ogni arco
   costi.resize(numNodi);
   for (int i = 0; i < numNodi; ++i)
   {
        costi[i].reserve(numNodi);
       for (int j = 0; j < numNodi; ++j)
       {
            double costo;
            in >> costo;
            costi[i].push_back(costo);
       }
   }
   in.close();
}

void Istanza::stampa() const
{
    std::cout << "Istanza del problema con "
        << numNodi << " nodi:" << std::endl;
    for (int i = 0; i < numNodi; ++i)
    {
        for (int j = 0; j < numNodi; ++j)
        {
            std::cout << costi[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}