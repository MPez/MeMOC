# Marco Pezzutti - 1084411
# Esercitazione di laboratorio 1
# modulo elaborazione risultati per creazione statistiche

from statistics import mean, stdev


class Data():

    """Classe che calcola statistiche sui risultati trovati.

    Si usa per leggere i dati forniti da cplex per calcolare i dati statistici
    e scrivere file di testo per gnuplot con cui si realizzano i grafici."""

    def __init__(self, data_file, stat_file, circular_file):
        self.data_file = data_file
        self.stat_file = stat_file
        self.circ_file = circular_file
        self.data_stat = []
        self.circ_data = []

    def read_data(self):
        nodi = []
        tempi = []
        f_in = open(self.data_file, "r")
        for line in f_in:
            nodo, tempo = line.split()
            # se lista vuota o stesso numero di nodi
            if len(nodi) == 0 or nodi[0] == int(nodo):
                nodi.append(int(nodo))
                tempi.append(float(tempo))
            # se una sola istanza per numero di nodi
            elif len(nodi) == 1:
                self.circ_data.append([nodi.pop(), tempi.pop()])
                nodi.append(int(nodo))
                tempi.append(float(tempo))
            # se cambia il numero di nodi
            else:
                self.data_stat.append([nodi[0], mean(tempi), stdev(tempi)])
                nodi.clear()
                tempi.clear()
                nodi.append(int(nodo))
                tempi.append(float(tempo))
        if len(nodi) == 1:
            self.circ_data.append([nodi.pop(), tempi.pop()])
        else:
            self.data_stat.append([nodi[0], mean(tempi), stdev(tempi)])
        f_in.close()

    def write_data(self):
        # stampa statistiche per casuali e cluster
        f_out = open(self.stat_file, "w")
        for nodi, media, dev in self.data_stat:
            f_out.write(str(nodi) + "\t" + str(media) + "\t" + str(dev) + "\n")
        f_out.close()
        # stampa statistiche per circolari
        f_out = open(self.circ_file, "w")
        for nodi, tempo in self.circ_data:
            f_out.write(str(nodi) + "\t" + str(tempo) + "\n")
        f_out.close()


def main():
    data = Data("results/simple_results.txt",
                "results/plot_results.txt",
                "results/plot_circular.txt")
    data.read_data()
    data.write_data()

if __name__ == '__main__':
    main()
