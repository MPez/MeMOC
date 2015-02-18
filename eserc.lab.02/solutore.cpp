/**
 * @author  Marco Pezzutti - 1084411
 * @file    solutore.cpp
 * @brief   Esercitazione di laboratorio 2
 * @date    febbraio 2014
*/

#include "solutore.h"

const double infinito = std::numeric_limits<double>::max();

Solutore::Solutore(const Istanza& ist, Soluzione& sol,
                   int tabuTenure, int maxIt) 
    : istanza(ist), soluzione(sol), tabuList(tabuTenure), maxIter(maxIt) {}

void Solutore::startSoluzione()
{
    // riferimenti da usare per selezionare i nodi da aggiungere o rimuovere
    int i = 0;
    int j = 0;
    // insieme dei nodi presenti nel ciclo
    std::vector<int> selezionati;
    // insiede dei nodi non ancora selezionati
    std::set<int> rimanenti;
    for (int n = 0; n < istanza.getNumNodi(); ++n)
    {
        rimanenti.insert(n);
    }
    // calcolo la prima coppia di nodi e li inserisco nel ciclo
    istanza.maxCosto(i, j);
    selezionati.push_back(i);
    selezionati.push_back(j);
    // rimuovo i nodi selezionati dai rimanenti
    rimanenti.erase(i);
    rimanenti.erase(j);
    while(!rimanenti.empty())
    {
        // cerco nodo da inserire con costo massimo
        int r = istanza.maxCosto(selezionati, rimanenti);
        // cerco posizione dove inserire il nodo selezionato
        istanza.minCosto(r, i, j, selezionati);
        // inserisco nodo selezionato
        selezionati.insert(selezionati.begin() + j, r);
        //rimuovo nodo selezionato dai rimanenti
        rimanenti.erase(r);
    }
    // inserisco come ultimo nodo quello di partenza per chiudere il ciclo
    selezionati.push_back(selezionati.front());
    soluzione.setSoluzione(selezionati);
}

bool Solutore::compMossa::operator()(const Mossa& a, const Mossa& b) const
{
    return a.costo < b.costo;
}

void Solutore::trovaVicino(const Soluzione& solCorrente, Mossa& mossa,
                             double& bestCosto, double& currCosto) const
{
    // insieme di mosse ordinate in ordine crescente di costo
    std::set<Mossa, compMossa> mosseMigliori;

    int size = solCorrente.getSoluzione().size();
    for (int i = 1; i <  size - 2; ++i)
    {
        for (int j = i + 1; j < size - 1; ++j)
        {
            currCosto = solCorrente.calcolaCostoVicino(istanza, i, j);
            if (currCosto < bestCosto)
            {
                mossa.to = i;
                mossa.from = j;
                mossa.costo = currCosto;
                bestCosto = currCosto;
                mosseMigliori.insert(mossa);
            }
        }
    }
    if (!mosseMigliori.empty())
    {
        // la mossa migliore viene scelta tra le numMosse migliori
        int numMosse = rand() % mosseMigliori.size();
        std::set<Mossa>::iterator it = mosseMigliori.begin();
        std::advance(it, numMosse);
        mossa = *it;
        bestCosto = mossa.costo;
    }
}

bool Solutore::controllaMossa(const Mossa& mossa) const
{
    bool tabu = false;
    for (int i = 0; i < tabuList.size(); ++i)
    {
        if (tabuList[i] == mossa)
        {
            tabu = true;
            std::cout << "TABU " << mossa.from << ", " << mossa.to << std::endl;
        }
    }
    return tabu;
}

void Solutore::inserisciMossaTabu(const Mossa& mossa)
{
    if (tabuList.size() == tabuList.capacity())
        {
            tabuList.pop_back();
        }
    tabuList.insert(tabuList.begin(), mossa);
}

void Solutore::tabuSearch()
{
    srand(time(NULL));
    // genero soluzione iniziale
    startSoluzione();
    // numero iterazione corrente
    int k = 0;
    // soluzione corrente
    Soluzione* solCorrente = new Soluzione(soluzione);
    std::cout << "Soluzione di partenza" << std::endl;
    solCorrente->stampa();
    // costo soluzione corrente
    double costo = solCorrente->calcolaCosto(istanza);
    std::cout << "Costo = " << costo << std::endl << std::endl;
    // costo migliore e corrente
    double bestCosto = infinito;
    double currCosto = 0.0;
    // variabile di controllo ciclo
    bool terminato = false;
    while(!terminato)
    {
        // cerco il miglior vicino
        Mossa mossa = Mossa();
        trovaVicino(*solCorrente, mossa, bestCosto, currCosto);
        // controllo che la mossa migliore non sia tabu
        std::cout << "Iter = " << k << "\t";
        bool mossaTabu = controllaMossa(mossa);
        // se la mossa è valida e migliorativa la eseguo e aggiorno la tabu list
        if (!mossaTabu)
        {
            if (bestCosto < costo)
            {
                costo = bestCosto;
                solCorrente->invertiNodi(mossa.to, mossa.from);
                solCorrente->stampa();
                std::cout << "costo = " << costo << "\t";
                std::cout << "mossa = " << mossa.to 
                    << ", " << mossa.from << std::endl;
            }
            inserisciMossaTabu(mossa);
        }
        if (k == maxIter)
        {
            terminato = true;
        }
        k++;
    }
    soluzione = *solCorrente;
}

