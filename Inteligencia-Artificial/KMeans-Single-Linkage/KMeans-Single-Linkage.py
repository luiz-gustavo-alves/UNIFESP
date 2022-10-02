'''

#
#   AULA 11
#   APRENDIZADO NÃO SUPERVISIONADO
#   LINGUAGEM DE PROGRAMAÇÃO: Python
#
#   NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
#

'''

# BIBLIOTECAS UTILIZADAS

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.cluster import AgglomerativeClustering

def executar_algoritmos(data):

    k = len(data['Classe'].unique())

    labels_k_means, centroids = K_means(data, k)
    labels_single = single_linkage(data, k)
    plotar_graficos(data, labels_k_means, labels_single, centroids)

def K_means(data, k):

    kmeans = KMeans(n_clusters = k, random_state = 0)
    labels = kmeans.fit_predict(data)
    centroids = kmeans.cluster_centers_
    return labels, centroids

def single_linkage(data, k):

    sk = AgglomerativeClustering(n_clusters = k, linkage = 'single')
    labels = sk.fit_predict(data)
    return labels

def plotar_graficos(data, labels_k_means, labels_single, centroids):

    colors = ['#58EF14', '#6AD5E4', '#DB0739', '#949D10', '#7A0177', '#FCFC53', '#3707DC', '#2979D9', '#69D926',
              '#83FAD2', '#922E95', '#5257FD', '#0AA4FB', '#E38B52', '#F0E494', '#E70FD4', '#15C6E6', '#312D9C',
              '#A72F1D', '#B45BC7', '#010C68', '#35FE8F', '#F3F63D', '#B388E3', '#A97DE9', '#E9211F', '#9204EB',
              '#F4F943', '#9694C5', '#BFDA1C', '#2E2724', '#220B59', '#C8D630', '#E20ED9']

    u_labels = np.unique(labels_k_means)
    figure, axis = plt.subplots(1, 2)

    for i, color in zip(u_labels, colors):
        label_k = data[labels_k_means == i]
        label_single = data[labels_single == i]

        axis[0].scatter(label_k.iloc[:, 0] , label_k.iloc[:, 1], label = i, color = color)
        axis[1].scatter(label_single.iloc[:, 0] , label_single.iloc[:, 1], label = i, color = color)

    axis[0].scatter(centroids[:, 0] , centroids[:, 1] , s = 80, color = 'k')
    axis[0].legend(fontsize = 8)
    axis[1].legend(fontsize = 8)
    axis[0].set_title("K-Means")
    axis[1].set_title("Single Linkage")

    plt.show()

def menu():
    valid_input = ['1', '2', '3', '4']

    while True:
        print("Selecione a opção: 1 - Aggregation | 2 - D31 | 3 - Path Based | 4 - Flame | 5 - Sair do programa")
        input_op = input()

        if (input_op == "1"): # LER DATASET: AGGREGATION
            data = pd.read_csv("Aggregation.txt", sep = "\t", header = None, names=["Atr1", "Atr2", "Classe"])

        elif (input_op == "2"): # LER DATASET: D31
            data = pd.read_csv("D31.txt", sep = "\t", header = None, names=["Atr1", "Atr2", "Classe"])

        elif (input_op == "3"): # LER DATASET: PATHBASED
            data = pd.read_csv("pathbased.txt", sep = "\t", header = None, names=["Atr1", "Atr2", "Classe"])

        elif (input_op == "4"): # LER DATASET: FLAME
            data = pd.read_csv("flame.txt", sep = "\t", header = None, names=["Atr1", "Atr2", "Classe"])

        if (input_op in valid_input):
            executar_algoritmos(data)
        else:
            return

if __name__ == '__main__':
    menu()