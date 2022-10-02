'''
#
#   AULA 7
#   ALGORITMOS BIOINSPIRADOS (PSO - ACO)
#   LINGUAGEM DE PROGRAMAÇÃO: Python
#
#   NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
#

'''

# BIBLIOTECAS USADAS:
import math

class Grafo:
    def __init__(self, vertices, arestas, pesos):
        self.vertices = vertices
        self.arestas = arestas
        self.pesos = pesos

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

    def obterMatrizDeAdjacencia(self):
        index, v_list = self.converterStringInt()
        numeroDeVertices = len(self.vertices)

        matriz = [[0 for col in range(numeroDeVertices)] for row in range(numeroDeVertices)]

        k = 0
        for i in self.vertices:
            m = 0
            for j in self.vertices:
                u = self.mapearStringInt(index, v_list, i)
                v = self.mapearStringInt(index, v_list, j)
                matriz[u][v] = self.pesos[k][m]
                m += 1
            k += 1

        return matriz

    def obterAdjacentesNaMatrizDeAdjacencia(self, matriz, vertice, vertice_visitado):
        Adjacentes = []
        index, v_list = self.converterStringInt()
        index_vertice = self.mapearStringInt(index, v_list, vertice)

        for i in range(len(matriz)):

            if matriz[index_vertice][i] != 0:
                j = self.mapearStringInt(v_list, index, i)
                exist_count = vertice_visitado.count(j)

                if exist_count == 0:
                    Adjacentes.append(j)

        return Adjacentes

    def somatorio(self, Adjacentes, vertice, alfa, beta, tau):
        index, v_list = self.converterStringInt()
        pos = self.mapearStringInt(index, v_list, vertice)
        sum = 0

        for i in Adjacentes:
            j = self.mapearStringInt(index, v_list, i)
            eta = self.pesos[pos][j]
            sum += ((alfa * tau) * (beta * (1 / eta)))

        return sum, pos;

    def calcProbabilidade(self, Adjacentes, alfa, beta, tau, sum, pos):
        index, v_list = self.converterStringInt()
        temp = - 1

        for j in Adjacentes:
            k = self.mapearStringInt(index, v_list, j)
            eta = self.pesos[pos][k]

            P = ((alfa * tau) * (beta * (1 / eta))) / sum
            if (P > temp):
                temp = P
                vertice = j

        return vertice

    def atualizarFeromonio(self, matriz, vertice, feromonio, Adjacentes, ro):
        index, v_list = self.converterStringInt()
        i = self.mapearStringInt(index, v_list, vertice)

        for j in range(len(feromonio)):
            if (i != j):

                k = self.mapearStringInt(v_list, index, j)
                exist_count = Adjacentes.count(k)
                if exist_count != 0:
                    feromonio[i][j] = ((1 - ro) * feromonio[i][j]) + ro * (1 / matriz[i][j])

    def ACO(self, matriz, vertice, feromonio, alfa, beta, tau, ro):
        index, v_list = self.converterStringInt()
        vertice_visitado = list()

        solucao = list()
        solucao.append(vertice)

        for i in range(len(matriz) - 1):
            Adjacentes = self.obterAdjacentesNaMatrizDeAdjacencia(matriz, vertice, vertice_visitado)
            vertice_visitado.append(vertice)
            self.atualizarFeromonio(matriz, vertice, feromonio, Adjacentes, ro)

            sum, pos = self.somatorio(Adjacentes, vertice, alfa, beta, tau)
            vertice = self.calcProbabilidade(Adjacentes, alfa, beta, tau, sum, pos)
            solucao.append(vertice)

        return solucao

def eq2(X, f):
    temp = -1
    for i in range(len(X)):
        x = X[i]
        Pbest = eval(f)
        if (Pbest > temp):
            temp = Pbest
            Gbest = X[i]

    Pbest = temp
    return Pbest, Gbest

def eq1(X, Y, w, c1, c2, r1, r2, f, Pbest, Gbest):

    V = []
    for i in range(len(Y)):
        v = w * Y[i] + (c1 * r1) * (Pbest - X[i]) + (c2 * r2) * (Gbest - X[i])
        V.append(X[i] + v)

    return eq2(V, f)

if __name__ == "__main__":

    print("Selecione opcao: 1 - PSO | 2 - ACO")
    input_op = int(input())

    if (input_op == 1): # EXECUTAR PSO

        print("Insere os seguintes parâmetros: iteracoes | w | c1 | c2 | r1 | r2")
        iteracoes = int(input())
        w = float(input())
        c1 = float(input())
        c2 = float(input())
        r1 = float(input())
        r2 = float(input())

        print("Insere os seguintes parâmetros: x | y")
        X = list(map(float, input().split()))
        Y = list(map(float, input().split()))

        print("Insere os seguintes parâmetros: f")
        f = input()

        Pbest, Gbest = eq2(X, f)
        print("Iteração  1  - Pbest: {:.5}".format(Pbest), " - Gbest: {:.5}".format(Gbest))

        for i in range(1, iteracoes):
            newPbest, newGbest = eq1(X, Y, w, c1, c2, r1, r2, f, Pbest, Gbest)

            Pbest = newPbest
            Gbest = newGbest

            print("Iteração ", i + 1, " - Pbest: {:.5}".format(Pbest), " - Gbest: {:.5}".format(Gbest))

    elif(input_op == 2): # EXECUTAR ACO
        print("Insere os seguintes parâmetros: alfa | beta | tau | ro")
        alfa = float(input())
        beta = float(input())
        tau = float(input())
        ro = float(input())

        print("Insere os seguintes parâmetros: vertices | pesos | fermonio")
        v = list((input().split()))
        w_not_ord = list(map(int, input().split()))
        frm_not_ord = list(map(int, input().split()))

        # FORMATANDO GRAFO E MATRIZ FEROMONIO
        e = list()
        w = list()
        frm = list()

        k = 0
        for i in range(len(v)):
            elem_w = []
            elem_frm = []
            for j in range(len(v)):

                if i != j:
                    e.append((v[i], v[j]))

                elem_w.append(w_not_ord[k])
                elem_frm.append(frm_not_ord[k])
                k += 1

            w.append(elem_w)
            frm.append(elem_frm)

        g = Grafo(v, e, w)
        matriz = g.obterMatrizDeAdjacencia()

        print("Insere os seguintes parâmetros: vertice inicial")
        vertice = input()

        solucao = g.ACO(matriz, vertice, frm, alfa, beta, tau, ro)
        print("Caminho da Solucao: ", solucao)
        print("Feromonio: ")
        for i in range(len(frm)):
            print(frm[i])