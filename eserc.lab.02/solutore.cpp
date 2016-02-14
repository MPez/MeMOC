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
    : istanza(ist), soluzione(sol), tabuList(tabuTenure), maxIter(maxIt){}

void Solutore::startSoluzione(std::string strategia)
{
    if (strategia == "shuffle")
    {
        soluzione.initSoluzione(istanza);
        soluzione.shuffleSoluzione();
    }
    else
    {
        // riferimenti da usare per selezionare i nodi da aggiungere o rimuovere
        int i = 0;
        int j = 0;
        // insieme dei nodi presenti nel ciclo
        std::vector<int> selezionati;
        // insieme dei nodi non ancora selezionati
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
}

bool Solutore::compMossa::operator()(const Mossa& a, const Mossa& b) const
{
    return a.costo < b.costo;
}

void Solutore::trovaVicini(const Soluzione& solCorrente, std::string strategia)
{
    double currCosto = 0.0;
    double bestCosto = infinito;
    mosseMigliori.clear();

    int size = solCorrente.getSoluzione().size();
    for (int i = 1; i <  size - 2; ++i)
    {
        for (int j = i + 1; j < size - 1; ++j)
        {
            currCosto = solCorrente.calcolaCostoVicino(istanza, i, j);
            // creo la mossa corrente
            Mossa mossa = Mossa(j, i, currCosto);
            // controllo che la mossa non sia tabu
            bool mossaTabu = controllaMossa(mossa);
            if(!mossaTabu)
            {
                if (strategia == "notAll")
                {
                    if (currCosto < bestCosto)
                    {
                        bestCosto = currCosto;
                        mosseMigliori.insert(mossa);
                    }
                }
                else
                {
                    mosseMigliori.insert(mossa);
                }
            }
        }
    }
}

Mossa Solutore::scegliVicino(std::string strategia) const
{
    Mossa mossa = Mossa();
    if (!mosseMigliori.empty())
    {
        if (strategia == "best")
        {
            // viene scelta la mossa migliore
            mossa = *mosseMigliori.begin();
        }
        else
        {
            // la mossa migliore viene scelta tra le numMosse migliori
            int numMosse = rand() % mosseMigliori.size();
            std::set<Mossa>::iterator it = mosseMigliori.begin();
            std::advance(it, numMosse);
            mossa = *it;
        }
    }
    return mossa;
}

bool Solutore::controllaMossa(const Mossa& mossa) const
{
    bool tabu = false;
    for (int i = 0; i < tabuList.size(); ++i)
    {
        if (tabuList[i] == mossa)
        {
            tabu = true;
            //std::cout << "TABU mossa = " << mossa.from << ", " << mossa.to << "\t";
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
    startSoluzione("");

    // numero iterazione corrente
    int k = 0;

    // soluzione corrente e migliore
    Soluzione* solCorrente = new Soluzione(soluzione);
    Soluzione* solMigliore = new Soluzione(soluzione);
    std::cout << "Soluzione di partenza" << std::endl;
    solCorrente->stampa();

    // costo soluzione migliore e corrente
    double bestCosto = solCorrente->calcolaCosto(istanza);
    std::cout << "Costo = " << bestCosto << std::endl;

    // variabile di controllo ciclo
    bool terminato = false;

    while(!terminato)
    {
        //std::cout << "\nIter = " << k << "\t";
        
        // cerco il miglior vicino
        trovaVicini(*solCorrente, "notAll");
        Mossa mossa = scegliVicino("best");

        if (!mosseMigliori.empty())
        {
            // effettuo la mossa
            solCorrente->invertiSequenza(mossa.to, mossa.from);
            // inserisco la mossa in quelle tabu
            inserisciMossaTabu(mossa);

            // aggiorno la soluzione migliore
            if (mossa.costo < bestCosto)
            {
                bestCosto = mossa.costo;
                *solMigliore = *solCorrente;
            }

            // stampo la soluzione
            //solCorrente->stampa();
            //std::cout << "costo = " << mossa.costo << "\t";
            //std::cout << "mossa = " << mossa.to << ", " << mossa.from;
        }


        // aggiorno il contatore
        if (k == maxIter)
        {
            terminato = true;
        }
        k++;
    }
    soluzione = *solMigliore;
}

