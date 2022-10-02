from queue import Queue

class Grafo:
    def __init__(self, vertices, arestas):
        self.vertices = vertices
        self.arestas = arestas

    def converterStringInt(self):
        v_list = []
        index = []

        for i in self.vertices:
            v_list.append(i)
            index.append(v_list.index(i))

        return index, v_list

    def mapearStringInt(self, index, v_list, vertice):
        i = 0;
        for u in v_list:
            if (u == vertice):
                return index[i]
            i += 1

    def obterAdjacentesNoGrafo(grafo):
        Adjacentes = []

        for vertice in grafo.vertices:
            Adj = []

            for u,v in grafo.arestas:

                if (u == vertice):
                    Adj.append(v)
                elif (v == vertice):
                    Adj.append(u)

            Adjacentes.append(Adj)

        return Adjacentes

def busca_min(grafo, vertice):
    Q = Queue()
    distancia_dict = {k: 999999999 for k in grafo.vertices}
    Q.put(vertice)

    vertices_visitados = list()
    vertices_visitados.append(vertice)
    Adjacentes = grafo.obterAdjacentesNoGrafo()

    index, v_list = grafo.converterStringInt()

    while not Q.empty():

        vertice = Q.get()
        if vertice == vertice:
            distancia_dict[vertice] = 0

        i = grafo.mapearStringInt(index, v_list, vertice)
        for u in Adjacentes[i]:
            print(u, Adjacentes[i])
            if u not in vertices_visitados:
                if distancia_dict[u] > distancia_dict[vertice] + 1:
                    distancia_dict[u] = distancia_dict[vertice] + 1
                Q.put(u)
                vertices_visitados.append(u)

    return distancia_dict

def calcular_dist(grafo, v1, v2):

    Q = Queue()
    distancia_dict = {k: 999999999 for k in grafo.vertices}
    Q.put(v1)

    vertices_visitados = list()
    vertices_visitados.append(v1)
    Adjacentes = grafo.obterAdjacentesNoGrafo()

    index, v_list = grafo.converterStringInt()

    while not Q.empty():

        vertice = Q.get()
        if vertice == v1:
            distancia_dict[vertice] = 0
            print(distancia_dict)

        i = grafo.mapearStringInt(index, v_list, vertice)
        for u in Adjacentes[i]:
            if u not in vertices_visitados:
                if distancia_dict[u] > distancia_dict[vertice] + 1:
                    distancia_dict[u] = distancia_dict[vertice] + 1
                Q.put(u)
                vertices_visitados.append(u)

    return distancia_dict.get(v2)

if __name__ == '__main__':
    v_art = ['Bennedict Cumberbatch', 'Chris Evans', 'Chris Hemsworth', 'Elizabeth Oslen', 'Gwyneth Paltrow',
             'Jeremy Renner', 'Mark Ruffalo', 'Paul Bettany', 'Robert Downey Jr', 'Samuel L. Jackson',
             'Scarllet Johansson', 'Tom Holland']

    e_art = {('Bennedict Cumberbatch', 'Chris Hemsworth'), ('Chris Evans', 'Elizabeth Oslen'), ('Chris Evans', 'Samuel L. Jackson'),
             ('Chris Evans', 'Scarllet Johansson'), ('Chris Hemsworth', 'Jeremy Renner'), ('Chris Hemsworth', 'Mark Ruffalo'), ('Chris Hemsworth', 'Samuel L. Jackson'),
             ('Elizabeth Oslen', 'Robert Downey Jr'), ('Gwyneth Paltrow', 'Robert Downey Jr'), ('Gwyneth Paltrow', 'Scarllet Johansson'),
             ('Gwyneth Paltrow', 'Tom Holland'), ('Mark Ruffalo', 'Robert Downey Jr'), ('Paul Bettany', 'Robert Downey Jr'),
             ('Robert Downey Jr', 'Scarllet Johansson'), ('Robert Downey Jr', 'Samuel L. Jackson'), ('Robert Downey Jr', 'Tom Holland')}

    GArtistas = Grafo(v_art, e_art)
    distances = calcular_dist(GArtistas, "Bennedict Cumberbatch", "Chris Hemsworth")
    print(distances)

    distances = calcular_dist(GArtistas, "Bennedict Cumberbatch", "Elizabeth Oslen")
    print(distances)