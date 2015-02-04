/**
 * @author  Marco Pezzutti - 1084411
 * @file    pannello.cpp
 * @brief   Esercitazione di laboratorio 1
 * @date    gennaio 2014
*/

#include <fstream>
#include <string>
#include "pannello.h"
#include "cpxmacro.h"

Pannello::Pannello() {}

std::vector<double> Pannello::getC()
{
    return C;
}

int Pannello::getN()
{
    return N;
}

std::vector<int> Pannello::getNameN()
{
    return nameN;
}

void Pannello::readFile(const char* fileName)
{
   std::ifstream in(fileName);
   // lettura numero di nodi
   in >> N;
   // lettura identificativo di ogni nodo
   for (int i = 0; i < N; ++i)
   {
        int val;
        in >> val;
        nameN.push_back(val);
   }
   // lettura costi di cammino per ogni arco
   for (int i = 0; i < N; ++i)
   {
       for (int j = 0; j < N; ++j)
       {
            double costo;
            in >> costo;
            if(costo == 0)
            {
                costo = CPX_INFBOUND;
            }
            C.push_back(costo);
       }
   }
   in.close();
}