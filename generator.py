# modulo generazione istanze
import sys
from random import randrange
from math import fabs


class Grid():

    """Griglia che rappresenta un pannello sul quale vengono fatti i fori.

    Alla creazione vengono passate le dimensioni x e y
    relative a righe e colonne.
    """

    def __init__(self, x_dim, y_dim):
        self.x_dim = x_dim
        self.y_dim = y_dim
        self.grid = [[None for col in range(y_dim)] for row in range(x_dim)]
        self._nodes = []
        self._weigths = [[]]

    @property
    def nodes(self):
        return self._nodes

    @nodes.setter
    def nodes(self, nodo):
        self._nodes.append(nodo)

    @property
    def weigths(self):
        return self._weigths

    @weigths.setter
    def weigths(self, dim):
        self._weigths = [[0 for j in range(dim)] for i in range(dim)]

    def print_grid(self):
        print("Griglia di posizionamento dei nodi")
        for row in self.grid:
            for col in row:
                if col is not None:
                    print(col.num, end='\t')
                else:
                    print(col, end='\t')
            print()

    def insert_node(self, nodo):
        self.grid[nodo.x_pos][nodo.y_pos] = nodo
        self.nodes = nodo

    def manhattan_distance(self):
        self.weigths = len(self.nodes)
        for nodo in self.nodes:
            if nodo is not None:
                for nnodo in self.nodes:
                    if nnodo is not None:
                        dist = fabs(nodo.x_pos - nnodo.x_pos) + \
                            fabs(nodo.y_pos - nnodo.y_pos)
                        self.weigths[nodo.num][nnodo.num] = dist

    def print_weigths(self):
        print("Matrice delle distanze dei nodi")
        for i in self.weigths:
            for j in i:
                print(j, end='\t')
            print()


class Node():

    """Nodo che rappresenta un foro sulla griglia.

    Possiede gli attributi di posizione sulla griglia
    e il numero (dato in ordine di creazione) che lo identifica.
    """

    def __init__(self, x_pos, y_pos, num):
        self.x_pos = x_pos
        self.y_pos = y_pos
        self.num = num


if __name__ == '__main__':
    x_dim = int(sys.argv[1])
    y_dim = int(sys.argv[2])
    g = Grid(x_dim, y_dim)
    n = Node(2, 4, 0)
    n1 = Node(0, 3, 1)
    g.insert_node(n)
    g.insert_node(n1)
    g.print_grid()
    g.manhattan_distance()
    g.print_weigths()
