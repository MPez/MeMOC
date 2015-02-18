/**
 * @author  Marco Pezzutti - 1084411
 * @file    soluzione.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include "soluzione.h"

Soluzione::Soluzione() {}

Soluzione::Soluzione(const Soluzione& sol)
{
    std::vector<int> soluz = sol.getSoluzione();
    soluzione.resize(soluz.size());
    for (int i = 0; i < soluz.size(); ++i)
    {
        soluzione[i] = soluz[i];
    }
}

Soluzione& Soluzione::operator=(const Soluzione& sol)
{
    std::vector<int> soluz = sol.getSoluzione();
    for (int i = 0; i < soluz.size(); ++i)
    {
        soluzione[i] = soluz[i];
    }
    return *this;
}

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

void Soluzione::invertiNodi(int pos1, int pos2)
{
    while(pos1 <= pos2)
    {
        int temp = soluzione[pos1];
        soluzione[pos1] = soluzione[pos2];
        soluzione[pos2] = temp;
        pos1++;
        pos2--;
    }
}

double Soluzione::calcolaCosto(const Istanza& istanza) const
{
    double costo = 0.0;
    for (int i = 0; i < soluzione.size() - 1; ++i)
    {
        costo += istanza.getCosti(soluzione[i], soluzione[i + 1]);
    }
    return costo;
}

double Soluzione::calcolaCostoVicino(const Istanza& istanza, int i, int j) const
{
    double costo = calcolaCosto(istanza);
    int h = soluzione[i - 1];
    int l = soluzione[j + 1];
    i = soluzione[i];
    j = soluzione[j];
    costo = costo - istanza.getCosti(h, i) - istanza.getCosti(j, l)
        + istanza.getCosti(h, j) + istanza.getCosti(i, l);
    return costo;
}

void Soluzione::stampa() const
{
    std::cout << "Soluzione = " ;
    for (int i = 0; i < soluzione.size(); ++i)
    {
        std::cout << soluzione[i] << " ";
    }
    std::cout << "\t";
}