# Marco Pezzutti - 1084411
# Esercitazione di laboratorio 1
# modulo elaborazione risultati per creazione statistiche

from statistics import mean, stdev


class Data():

    """Classe che calcola statistiche sui risultati trovati.

    Si usa per leggere i dati forniti da cplex per calcolare i dati statistici
    e scrivere file di testo per gnuplot con cui si realizzano i grafici."""

    def __init__(self):
        self.data_stat = []
        self.circ_data = []
        self.tabu_temp = []
        self.tabu_stat = []
        self.max_costo = []

    def read_data(self, data_file):
        nodi = []
        tempi = []
        costi = []
        f_in = open(data_file, "r")
        for line in f_in:
            nodo, tempo, costo = line.split()
            # se lista vuota o stesso numero di nodi
            if len(nodi) == 0 or nodi[0] == int(nodo):
                nodi.append(int(nodo))
                tempi.append(float(tempo))
                costi.append(int(costo))
            # se una sola istanza per numero di nodi
            elif len(nodi) == 1:
                self.circ_data.append([nodi.pop(), tempi.pop(), costi.pop()])
                nodi.append(int(nodo))
                tempi.append(float(tempo))
                costi.append(int(costo))
            # se cambia il numero di nodi
            else:
                self.data_stat.append([nodi[0], mean(tempi), stdev(tempi), mean(costi)])
                # pulisco le liste
                nodi.clear()
                tempi.clear()
                costi.clear()
                # inserisco nuovo elemento
                nodi.append(int(nodo))
                tempi.append(float(tempo))
                costi.append(int(costo))
        if len(nodi) == 1:
            self.circ_data.append([nodi.pop(), tempi.pop(), costi.pop()])
        else:
            self.data_stat.append([nodi[0], mean(tempi), stdev(tempi), mean(costi)])
        f_in.close()

    def read_data_tabu(self, tabu_file):
        istanze = []
        nodi = []
        tempi = []
        costi = []
        tabu_tenure = []
        f_in = open(tabu_file, "r")
        # prima passata, medie su stessa istanza
        for line in f_in:
            istanza, nodo, tempo, costo, tabu_ten, max_it = line.split()
            # se lista vuota o stessa istanza
            if len(istanze) == 0 or istanze[0] == int(istanza):
                istanze.append(int(istanza))
                nodi.append(int(nodo))
                tempi.append(float(tempo))
                costi.append(int(costo))
                tabu_tenure.append(int(tabu_ten))
            # se cambia istanza
            else:
                self.tabu_temp.append([nodi[0], mean(tempi), mean(costi), tabu_tenure[0]])
                # pulisco le liste
                istanze.clear()
                nodi.clear()
                tempi.clear()
                costi.clear()
                tabu_tenure.clear()
                # inserisco nuovo elemento
                istanze.append(int(istanza))
                nodi.append(int(nodo))
                tempi.append(float(tempo))
                costi.append(int(costo))
                tabu_tenure.append(int(tabu_ten))
        self.tabu_temp.append(
            [nodi[0], mean(tempi), mean(costi), tabu_tenure[0]])
        # pulisco le liste
        nodi.clear()
        tempi.clear()
        costi.clear()
        tabu_tenure.clear()
        # seconda passata, medie su stesso numero di nodi
        for nodo, media_tempi, media_costi, tabu_ten in self.tabu_temp:
            # se lista vuota o stesso numero di nodi
            if len(nodi) == 0 or nodi[0] == nodo:
                nodi.append(nodo)
                tempi.append(media_tempi)
                costi.append(media_costi)
                self.update_max_costo(int(media_costi), int(nodo), int(tabu_ten))
                tabu_tenure.append(tabu_ten)
            else:
                self.tabu_stat.append([nodi[0], mean(tempi), stdev(tempi), mean(costi), stdev(costi), tabu_tenure[0]])
                # pulisco le liste
                nodi.clear()
                tempi.clear()
                costi.clear()
                tabu_tenure.clear()
                # inserisco nuovo elemento
                nodi.append(nodo)
                tempi.append(media_tempi)
                costi.append(media_costi)
                self.update_max_costo(int(media_costi), int(nodo), int(tabu_ten))
                tabu_tenure.append(tabu_ten)
        self.tabu_stat.append([nodi[0], mean(tempi), stdev(tempi), mean(costi), stdev(costi), tabu_tenure[0]])
        f_in.close()

    def update_max_costo(self, costo, nodi, tenure):
        if (nodi, tenure) not in [(nodo, ten) for nodo, cost, ten in self.max_costo]:
                self.max_costo.append([nodi, costo, tenure])
        else:
            for n, c, t in self.max_costo:
                if n == nodi and t == tenure:
                    self.max_costo[self.max_costo.index([n, c, t])][1] = max(c, costo)

    def write_data(self, stat_file, circ_file):
        # stampa statistiche per casuali e cluster
        f_out = open(stat_file, "w")
        for nodi, media, dev, costo in self.data_stat:
            f_out.write(str(nodi) + "\t" + str(media) + "\t" +
                        str(dev) + "\t" + str(costo) + "\n")
        f_out.close()
        # stampa statistiche per circolari
        f_out = open(circ_file, "w")
        for nodi, tempo, costo in self.circ_data:
            f_out.write(str(nodi) + "\t" + str(tempo) + "\t" +
                        str(costo) + "\n")
        f_out.close()

    def write_data_tabu(self, tabu_stat_file):
        f_out = open(tabu_stat_file, "w")
        for nodi, media_tempi, dev_tempi, media_costi, dev_costi, tabu_ten in self.tabu_stat:
            f_out.write(str(nodi) + "\t" +
                        str(media_tempi) + "\t" + str(dev_tempi) + "\t" +
                        str(media_costi) + "\t" + str(dev_costi) + "\t" +
                        str(tabu_ten) + "\n")
        f_out.close()

    def compare(self, stat_file, tabu_stat_file, compare_file):
        cplex_in = open(stat_file, "r")
        tabu_in = open(tabu_stat_file, "r")
        comp_out = open(compare_file, "w")
        cplex_cost = []
        tabu_cost = []
        for line in cplex_in:
            nodi, tempo, dev, costo = line.split()
            cplex_cost.append([nodi, float(costo)])
        for line in tabu_in:
            nodi, media_tempo, dev_tempo, media_costo, dev_costo, tabu_ten = line.split()
            tabu_cost.append([nodi, float(media_costo), tabu_ten])
        i = 0
        while i < len(tabu_cost):
            j = 0
            while j < 50:
                avg_value = (tabu_cost[i][1] - cplex_cost[j][1]) / cplex_cost[j][1] * 100
                max_value = [costo for nodo, costo, tenure
                                   in self.max_costo if int(nodo) == int(tabu_cost[i][0])
                                                     and int(tenure) == int(tabu_cost[i][2])]   
                max_percent = (max_value[0] - cplex_cost[j][1]) / cplex_cost[j][1] * 100
                comp_out.write(tabu_cost[i][0] + "\t" + str(avg_value) + "\t" +
                               tabu_cost[i][2] + "\t" +
                               str(max_percent) + "\n")
                i += 1
                j += 1
        cplex_in.close()
        tabu_in.close()
        comp_out.close()


def main():
    # file per risultati cplex
    data_file = "results/CPXsimple_results.txt"
    stat_file = "results/CPXplot_results.txt"
    circ_file = "results/CPXplot_circular.txt"
    # file per risultati tabu search
    tabu_file = "results/TABUsimple_results.txt"
    tabu_stat_file = "results/TABUplot_results.txt"
    # file per comparazione cplex e tabu search
    compare_file = "results/compare.txt"
    # creo oggetto data, leggo, elaboro i dati e li scrivo
    data = Data()
    data.read_data(data_file)
    data.write_data(stat_file, circ_file)
    data.read_data_tabu(tabu_file)
    data.write_data_tabu(tabu_stat_file)
    data.compare(stat_file, tabu_stat_file, compare_file)

if __name__ == '__main__':
    main()
