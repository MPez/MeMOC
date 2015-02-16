/**
 * @author  Marco Pezzutti - 1084411
 * @file    soluzione.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include <vector>
#include "soluzione.h"

Soluzione::Soluzione() {}

std::vector<int> Soluzione::getSoluzione() const
{
    return soluzione;
}

void Soluzione::setSoluzione(std::vector<int> sol)
{
    soluzione.resize(sol.size());
    for (int i = 0; i < sol.size(); ++i)
    {
        soluzione[i] = sol[i];
    }
}

void Soluzione::initSoluzione(const Istanza& istanza)
{
    soluzione.resize(istanza.getNumNodi() + 1);
    for (int i = 0; i < soluzione.size() - 1; ++i)
    {
        soluzione[i] = i;
    }
    soluzione.push_back(0);
}

void Soluzione::scambiaNodi(int pos1, int pos2)
{
    int temp = soluzione[pos1];
    soluzione[pos1] = soluzione[pos2];
    soluzione[pos2] = temp;
}