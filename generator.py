# modulo generazione istanze
import sys
from random import randrange
from math import fabs, ceil


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
                    print("-", end='\t')
            print()
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


class Generator():

    """Generatore casuale di nodi.

    Possiede gli attributi che rappresentano la griglia,
    la quantità di nodida creare,
    la distribuzione sulla griglia: casuale, circolare, cluster
    """

    def __init__(self, griglia, distr, num_nodi=0):
        self.griglia = griglia
        self.num_nodi = num_nodi
        self.distr = distr

    def crea_nodi(self):
        if self.distr == "casuale":
            pass
        elif self.distr == "circolare":
            cx = ceil(self.griglia.x_dim / 2) - 1
            cy = ceil(self.griglia.y_dim / 2) - 1
            r = min(cx + 1, cy + 1) - 1
            num_nodi = r * 4
            print("cx = %d, cy = %d, r = %d, numero nodi = %d" %
                  (cx, cy, r, num_nodi))
            cx -= r
            nodo = Node(cx, cy, 0)
            self.griglia.insert_node(nodo)
            for i in range(1, num_nodi):
                if i / r <= 1:
                    cx += 1
                    cy += 1
                    nodo = Node(cx, cy, i)
                    print("i = %d, cx = %d, cy = %d" % (i, cx, cy))
                elif 1 < i / r <= 2:
                    cx += 1
                    cy -= 1
                    nodo = Node(cx, cy, i)
                    print("i = %d, cx = %d, cy = %d" % (i, cx, cy))
                elif 2 < i / r <= 3:
                    cx -= 1
                    cy -= 1
                    nodo = Node(cx, cy, i)
                    print("i = %d, cx = %d, cy = %d" % (i, cx, cy))
                elif 3 < i / r <= 4:
                    cx -= 1
                    cy += 1
                    nodo = Node(cx, cy, i)
                    print("i = %d, cx = %d, cy = %d" % (i, cx, cy))
                self.griglia.insert_node(nodo)
        elif self.distr == "cluster":
            pass


if __name__ == '__main__':
    x_dim = int(sys.argv[1])
    y_dim = int(sys.argv[2])
    g = Grid(x_dim, y_dim)
    gen = Generator(g, "circolare")
    gen.crea_nodi()
    g.print_grid()
    g.manhattan_distance()
    g.print_weigths()
