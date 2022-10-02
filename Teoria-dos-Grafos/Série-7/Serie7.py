from queue import Queue
import numpy as np
import math

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

        i = 0
        for u in v_list:
            if (u == vertice):
                return index[i]
            i += 1

    def obterMatrizDeAdjacencia(self):
        index, v_list = self.converterStringInt()

        numeroDeVertices = len(self.vertices)

        # criamos uma matriz n x n com todos os elementos sendo 0
        matriz = [[0 for col in range(numeroDeVertices)] for row in range(numeroDeVertices)]

        # passamos de aresta em aresta,
        # preenchendo com o valor 1 os campos Aij e Aji da matriz,
        # onde i é o vértice que está em uma ponta da aresta e j é o que está na outra
        for u,v in self.arestas:
            i = self.mapearStringInt(index, v_list, u)
            j = self.mapearStringInt(index, v_list, v)

            matriz[i][j] = 1
            matriz[j][i] = 1

        return matriz

    def obterLista(self):
        index, v_list = self.converterStringInt()

        numeroDeVertices = len(self.vertices)
        # criamos uma lista  com n vetores como elementos
        lista = [[] for item in range(numeroDeVertices)]

        # passamos de aresta em aresta
        # e considerando que cada aresta é formada por V1 e V2,
        # adicionamos ao vetor de V1 o vértice V2 e ao de V2 o vértice V1
        for u, v in self.arestas:
            i = self.mapearStringInt(index, v_list, u)
            j = self.mapearStringInt(index, v_list, v)

            lista[i].append(v)
            lista[j].append(u)

        return lista

    def obterAdjacentesNoGrafo(self):

        Adjacentes = []

        for vertice in self.vertices:
            Adj = []

            for u,v in self.arestas:

                if (u == vertice):
                    Adj.append(v)
                elif (v == vertice):
                    Adj.append(u)

            Adjacentes.append(Adj)

        return Adjacentes

    def obterGrauDoVerticeNoGrafo(self, vertice):
        count = 0;

        for u,v in self.arestas:
            if (u == vertice):
                count += 1
            elif (v == vertice):
                count += 1

        return count

    def obterGrauDeCadaVerticeNoGrafo(self):
        Graus = [0 for row in range(len(self.vertices))]

        i = 0
        for u in self.vertices:
            Graus[i] = self.obterGrauDoVerticeNoGrafo(u)
            i += 1

        return Graus

    def BFS(self, v):
        Q = Queue()
        Q.put(v)

        vertices_visitados = list()
        vertices_visitados.append(v)

        Adjacentes = self.obterAdjacentesNoGrafo()
        index, v_list = self.converterStringInt()

        v_arv_abr = []
        e_arv_abr = set()
        while not Q.empty():

            vertice = Q.get()
            v_arv_abr.append(vertice)
            i = self.mapearStringInt(index, v_list, vertice)
            for u in Adjacentes[i]:
                if u not in vertices_visitados:
                    Q.put(u)
                    vertices_visitados.append(u)
                    e_arv_abr.add((vertice, u))

        if (len(v_arv_abr) != len(self.vertices)):
            return

        GArv_abr = Grafo(v_arv_abr, e_arv_abr)
        return GArv_abr

    def kirchoff(self):

        Graus = self.obterGrauDeCadaVerticeNoGrafo()
        matrizDeGraus = np.diag(Graus)
        matrizDeAdj = np.array(self.obterMatrizDeAdjacencia())

        matrizLaplaciana = matrizDeGraus - matrizDeAdj

        matrizLaplaciana = np.delete(matrizLaplaciana, [0, 0], 0)
        matrizLaplaciana = np.delete(matrizLaplaciana, [0, 0], 1)

        return math.floor(np.linalg.det(matrizLaplaciana))

def distanciaArvores(Arvore1, Arvore2):

    arestas_interseccao = []
    for aresta in Arvore1.arestas:
        if aresta in Arvore2.arestas or (aresta[1], aresta[0]) in Arvore2.arestas:
            arestas_interseccao.append(aresta)

    return len(Arvore1.arestas) - len(arestas_interseccao)

def arvoreCentral(Grafo):

    max_dist = 0
    vertices_visitados = list()
    for u in Grafo.vertices:
        GArv_ver_1 = Grafo.BFS(u)
        vertices_visitados.append(u)

        for v in Grafo.vertices:
            if v not in vertices_visitados:
                GArv_ver_2 = Grafo.BFS(v)

                dist = distanciaArvores(GArv_ver_1, GArv_ver_2)
                if dist > max_dist:
                    GArv_central = GArv_ver_1
                    max_dist = dist

    return GArv_central, max_dist

def imprimirLista(Grafo, lista):
    print()
    for i in range(len(lista)):
        print(Grafo.vertices[i], " -> ", lista[i])

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

    GArv_abr_art_A = GArtistas.BFS("Bennedict Cumberbatch")
    GArv_abr_lista_A = GArv_abr_art_A.obterLista()
    # imprimirLista(GArv_abr_art_A, GArv_abr_lista_A)

    GArv_abr_art_B = GArtistas.BFS("Samuel L. Jackson")
    GArv_abr_lista_B = GArv_abr_art_B.obterLista()
    # imprimirLista(GArv_abr_art_B, GArv_abr_lista_B)

    # print("Distância entre as Árvores: ", distanciaArvores(GArv_abr_art_A, GArv_abr_art_B))

    print("Numero de árvores de abrangência no Grafo: ", GArtistas.kirchoff())

    GArv_Central, max_dist = arvoreCentral(GArtistas)
    GArv_Central_Lista = GArv_Central.obterLista()
    imprimirLista(GArv_Central, GArv_Central_Lista)
    print("Distância Máxima: ", max_dist)