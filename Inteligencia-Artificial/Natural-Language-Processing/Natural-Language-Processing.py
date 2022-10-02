'''

#
#   AULA 12
#   PROCESSAMENTO DE LINGUAGEM NATURAL (PLN)
#   LINGUAGEM DE PROGRAMAÇÃO: Python
#
#   NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
#

'''

# BIBLIOTECAS UTILIZADAS

import pandas as pd
import numpy as np
import csv

stop_words = open("stopwords.txt", "r")
stop_words_linhas = stop_words.readlines()
lst_stop_words = []

for linha in stop_words_linhas:
    lst_stop_words.append(linha.strip())

def caractere_invalido(linha):

    caracteres_escpeciais = ['!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.',
                             '/', ':', ';', '<', '=', '>', '@', '[', ']', '|', '{', '}', '~', '?',
                             '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '^', '\\', '`']

    for caractere in caracteres_escpeciais:
        linha = linha.replace(caractere, ' ')

    return linha

def processamento_texto(texto):

    lst_data = []

    for linha in texto:
        palavras = caractere_invalido(linha.decode(errors='ignore')).split()

        for palavra in palavras:
            if palavra.lower() not in lst_stop_words:
                lst_data.append(palavra.lower())

    palavra_count = {}

    for palavra in lst_data:
        if palavra not in palavra_count.keys():
            palavra_count[palavra] = 1
        else:
            palavra_count[palavra] += 1

    return palavra_count

def termo_freq(text_unique, data):

    text = {}

    for palavra in text_unique:
        if palavra not in data:
            text[palavra] = 0
        else:
            text[palavra] = data[palavra]

    return text

def gerar_BOW(data1, data2):

    text = list(data1.keys()) + list(data2.keys())
    text_unique = list(np.unique(text))
    text_unique.insert(len(text_unique), 'ROTULO')

    t1 = termo_freq(text_unique, data1)
    t1['ROTULO'] = 1

    t2 = termo_freq(text_unique, data2)
    t2['ROTULO'] = 2

    BOW = open('BOW.csv', mode='w', newline='')
    with BOW as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=text_unique)

        writer.writeheader()
        writer.writerow(t1)
        writer.writerow(t2)

    return text_unique

if __name__ == '__main__':

    t1 = open("soc.religion.christian.txt", "rb")
    data1 = processamento_texto(t1)

    t2 = open("talk.politics.guns.txt", "rb")
    data2 = processamento_texto(t2)

    gerar_BOW(data1, data2)
    BOW = pd.read_csv("BOW.csv")
    print(BOW)