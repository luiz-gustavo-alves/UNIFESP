'''

#
#   AULA 9
#   APRENDIZADO SUPERVISIONADO
#   LINGUAGEM DE PROGRAMAÇÃO: Python
#
#   NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
#

'''

# BIBLIOTECAS UTILIZADAS

import pandas as pd
import numpy as np
import math
from sklearn.preprocessing import normalize

def pre_processamento(data):

    x = data.drop([data.columns[-1]], axis = 1)
    y = data[data.columns[-1]]

    return x, y

def split(x, y, test_size, random_state):

    x_test = x.sample(frac = test_size, random_state = random_state)
    y_test = y[x_test.index]

    x_train = x.drop(x_test.index)
    y_train = y.drop(y_test.index)

    return x_train, x_test, y_train, y_test

def distancia_euclidiana(x_teste, x_train):

    dist = 0
    for i in range(len(x_teste)):
        dist += pow((x_teste[i] - x_train[i]), 2)
    return math.sqrt(dist)

def KNN(x_teste, x_train, y_train):

    dist_min = math.inf
    for i in range(len(x_train)):
        dist_atual = distancia_euclidiana(x_teste, x_train[i])

        if dist_atual < dist_min:
            dist_min = dist_atual
            classe = y_train[i]

    return classe

def priori(y):

    prior = []
    for classe in np.unique(y):
        prior.append(sum(y == classe) / len(y))

    return prior

def probabilidade_condicional(x, y):

    probabilidade_media = {}
    probabilidade_var = {}

    for atributo in x:
        probabilidade_media[atributo] = {}
        probabilidade_var[atributo] = {}

        for classe in np.unique(y):
            media = x[atributo][y[y == classe].index.values.tolist()].mean()
            var = x[atributo][y[y == classe].index.values.tolist()].var()
            probabilidade_media[atributo][classe] = media
            probabilidade_var[atributo][classe] = var

    return probabilidade_media, probabilidade_var

def distribuicao_normal(media, var, valor_atributo):
    return (1 / math.sqrt(2 * math.pi * var)) * np.exp(-(valor_atributo - media)**2 / (2*var))

def naive_bayes_gaussiano(X, y):

    Y_pred = []
    prior = priori(y)
    probabilidade_media, probabilidade_var = probabilidade_condicional(X, y)
    tabela = np.array(X)
    for linha in tabela:
        resultado = {}

        for classe in np.unique(y):
            probabilidade = 1
            indice_prior = 0

            for atributo, valor_atributo in zip(X, linha):
                media = probabilidade_media[atributo][classe]
                var = probabilidade_var[atributo][classe]
                probabilidade *= distribuicao_normal(media, var, valor_atributo)

            resultado[classe] = probabilidade * prior[indice_prior]
            indice_prior += 1

        classe = max(resultado, key = resultado.get)
        Y_pred.append(classe)

    return Y_pred

if __name__ == '__main__':

    data = pd.read_csv('Iris.csv')
    X, y = pre_processamento(data)

    x_train, x_test, y_train, y_test = split(X, y, test_size = 0.7, random_state = 21)

    print("Selecione a opção: 1 - KNN | 2 - Naive Bayes")
    input_op = int(input())

    if (input_op == 1): # EXECUTAR ALGORITMO KNN

        print("Insere o seguinte parâmetro: k")
        k = int(input())
        acertos = 0

        x_train = normalize(x_train, axis=0)
        x_test = normalize(x_test, axis=0)

        y_train = [coluna for coluna in y_train]
        y_test = [coluna for coluna in y_test]

        for i in range(len(x_test)):
            KVizinhos = [0] * k

            for j in range(k):
                KVizinhos[j] = KNN(x_test[i], x_train, y_train)

            if (max(set(KVizinhos))) == y_test[i]:
                acertos += 1

        print('Acertos: ', acertos,'Precisão: ', acertos / len(y_test))

    elif(input_op == 2): # EXECUTAR ALGORITMO NAIVE BAYES

        y_pred = naive_bayes_gaussiano(x_test, y_test)

        acertos = sum(y_pred == y_test)
        print('Acertos: ', acertos,'Precisão: ', acertos / len(y_test))