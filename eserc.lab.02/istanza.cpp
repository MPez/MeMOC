/**
 * @author  Marco Pezzutti - 1084411
 * @file    istanza.cpp
 * @brief   Esercitazione di laboratorio 1
 * @date    gennaio 2014
*/

#include <fstream>
#include <string>
#include <climits>
#include "istanza.h"

Istanza::Istanza() {}

std::vector<std::vector<double>>& Istanza::getCosti(int i, int j) const
{
    return costi[i][j];
}

int Istanza::getNumNodi() const
{
    return numNodi;
}

double Istanza::maxCosto(int& i, int& j)
{
    double max = 0;
    for (int r = 0; r < numNodi; ++r)
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

int Istanza::maxCosto(std::vector<int>& selezionati,
                         std::vector<int>& rimanenti)
{
    double max = 0;
    int i = 0;
    int j = 0;
    int r = 0;
    for (int m = 0; m < rimanenti.size(); ++m)
    {
        i = rimanenti[m];
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

void Istanza::minCosto(int& r, int& i, int& j, std::vector<int>& selezionati)
{
    double min = INT_MAX;
    for (int m = 0; m < selezionati.size(); ++m)
    {
        for (int n = r + 1; n < selezionati.size(); ++n)
        {
            double costo = costi[i][r] + costi[r][j] - costi[i][j];
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
   // lettura riga che contiene identificativo di ogni nodo (da scartare)
   in.getline();
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