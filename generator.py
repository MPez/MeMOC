# modulo generazione istanze
import argparse
from random import randrange
from math import fabs, floor


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
        self._x_pos = x_pos
        self._y_pos = y_pos
        self._num = num

    @property
    def x_pos(self):
        return self._x_pos

    @property
    def y_pos(self):
        return self._y_pos

    @property
    def num(self):
        return self._num


class Generator():

    """Generatore casuale di nodi.

    Possiede gli attributi che rappresentano la griglia,
    la quantità di nodida creare,
    la distribuzione sulla griglia: casuale, circolare, cluster
    """

    def __init__(self, griglia, distr, num_nodi=0, cluster=1):
        self.griglia = griglia
        self.num_nodi = num_nodi
        self.distr = distr
        self.cluster = cluster

    def crea_nodi(self):
        if self.distr == "casuale":
            i = 0
            while i < self.num_nodi:
                x = randrange(self.griglia.x_dim)
                y = randrange(self.griglia.y_dim)
                if self.griglia.grid[x][y] is None:
                    self.griglia.insert_node(Node(x, y, i))
                    i += 1
        elif self.distr == "circolare":
            cx = floor(self.griglia.x_dim / 2)
            cy = floor(self.griglia.y_dim / 2)
            r = min(cx, cy)
            num_nodi = r * 4
            cx -= r
            self.griglia.insert_node(Node(cx, cy, 0))
            for i in range(1, num_nodi):
                if i / r <= 1:
                    cx += 1
                    cy += 1
                elif i / r <= 2:
                    cx += 1
                    cy -= 1
                elif i / r <= 3:
                    cx -= 1
                    cy -= 1
                elif i / r <= 4:
                    cx -= 1
                    cy += 1
                self.griglia.insert_node(Node(cx, cy, i))
        elif self.distr == "cluster":
            dx = floor(self.griglia.x_dim / 2)
            dy = floor(self.griglia.y_dim / 2)
            if self.cluster == 1:
                i = 0
                while i < self.num_nodi:
                    x = randrange(dx)
                    y = randrange(dy)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
            elif self.cluster == 2:
                i = 0
                while i < self.num_nodi / 2:
                    x = randrange(dx)
                    y = randrange(dy)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
                while i < self.num_nodi:
                    x = randrange(self.griglia.x_dim - dx, self.griglia.x_dim)
                    y = randrange(self.griglia.y_dim - dy, self.griglia.y_dim)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
            elif self.cluster == 3:
                i = 0
                while i < self.num_nodi / 3:
                    x = randrange(dx)
                    y = randrange(dy)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
                while i < (self.num_nodi / 3) * 2:
                    x = randrange(dx)
                    y = randrange(self.griglia.y_dim - dy, self.griglia.y_dim)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
                while i < self.num_nodi:
                    x = randrange(self.griglia.x_dim - dx, self.griglia.x_dim)
                    y = randrange(dy)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
            else:
                i = 0
                while i < self.num_nodi / 4:
                    x = randrange(dx)
                    y = randrange(dy)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
                while i < (self.num_nodi / 4) * 2:
                    x = randrange(dx)
                    y = randrange(self.griglia.y_dim - dy, self.griglia.y_dim)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
                while i < (self.num_nodi / 4) * 3:
                    x = randrange(self.griglia.x_dim - dx, self.griglia.x_dim)
                    y = randrange(dy)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1
                while i < self.num_nodi:
                    x = randrange(self.griglia.x_dim - dx, self.griglia.x_dim)
                    y = randrange(self.griglia.y_dim - dy, self.griglia.y_dim)
                    if self.griglia.grid[x][y] is None:
                        self.griglia.insert_node(Node(x, y, i))
                        i += 1


def main(x_dim, y_dim, distr, num_nodi, verbose, cluster):
    griglia = Grid(x_dim, y_dim)
    gen = Generator(griglia, distr, num_nodi, cluster)
    gen.crea_nodi()
    if verbose >= 1:
        griglia.print_grid()
    griglia.manhattan_distance()
    if verbose >= 2:
        griglia.print_weigths()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description="Generatore di istanze pannelli forati")
    parser.add_argument("-d", "--dim",
                        type=int,
                        nargs=2,
                        required=True,
                        dest="dim",
                        metavar=("x_dim", "y_dim"),
                        help="Dimensioni x e y del pannello")
    parser.add_argument("-t", "--type",
                        choices=["casuale", "circolare", "cluster"],
                        required=True,
                        dest="distr",
                        help="Tipo di distribuzione dei fori nel pannello")
    parser.add_argument("-n", "--num",
                        type=int,
                        default=0,
                        dest="num_nodi",
                        help="Numero di fori da posizionare nel pannello")
    parser.add_argument("-c", "--cluster",
                        type=int,
                        dest="cluster",
                        choices=[1, 2, 3, 4],
                        help="Numero di cluster dove posizionare i fori")
    parser.add_argument("-v", "--verbose",
                        dest="verbose",
                        action="count",
                        default=0,
                        help="Visualizza griglia di posizionamento " +
                        "e matrice delle distanze dei nodi")
    opt = parser.parse_args()
    main(opt.dim[0], opt.dim[1], opt.distr,
         opt.num_nodi, opt.verbose, opt.cluster)
