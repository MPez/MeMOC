/**
 * @author  Marco Pezzutti - 1084411
 * @file    mossa.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include "mossa.h"

 Mossa::Mossa() {}

 bool Mossa::operator==(const Mossa mossa) const
 {
    return (from == mossa.from) && (to == mossa.to);
 }