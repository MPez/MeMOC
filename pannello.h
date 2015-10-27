/**
 * @author  Marco Pezzutti - 1084411
 * @file    pannello.h
 * @brief   Esercitazione di laboratorio 1
 * @date    gennaio 2015
*/

#ifndef PANNELLO_H
#define PANNELLO_H

#include <vector>

class Pannello
{
public:
    Pannello();

    int getN();
    std::vector<double> getC();
    std::vector<int> getNameN();

    void readFile(const char* fileName);

private:
    int N; /**< numero di nodi */
    std::vector<int> nameN; /**< nome dei nodi*/
    std::vector<double> C; /**< costi di cammino */ 
};

#endif /* PANNELLO_H */