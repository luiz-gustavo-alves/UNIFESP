/*---TAD LISTA DE ADJACÊNCIA---
LUIZ GUSTAVO ALVES ASSIS DA SILVA--*/

#include <stdio.h>
#include <stdlib.h>

#define MAXVERTICES 100

typedef struct no{
	int arresta;
	struct no *prox;
}No;

No *cabeca, *calda = NULL;

typedef struct grafo{
	No **Lista;
	int NVertice;
}Grafo;

No *novoNo(int num_arresta)
{
	No *aux = (No*)malloc(sizeof(No));
	aux->arresta = num_arresta;
	aux->prox = NULL;
	return aux;
}

Grafo *iniciar_grafo(Grafo *pGrafo, int num_vertice)
{
	if(num_vertice > MAXVERTICES)
	{
		return NULL;
	}
	Grafo *aux = (Grafo*)malloc(sizeof(Grafo));
	aux->NVertice = num_vertice;
	
	aux->Lista = malloc(num_vertice * sizeof(No));
	
	int i;
	for(i = 1; i <= aux->NVertice; i++)
	{
		aux->Lista[i] = NULL;
	}
	return aux;
}

void inserir_arresta(Grafo *pGrafo, int u, int v)
{
	No *aux = novoNo(v);
	aux->prox = pGrafo->Lista[u];
	pGrafo->Lista[u] = aux;
}

void ordernar_lista()
{
	int aux;
	
	No *atual = cabeca, *indice = NULL;
	while(atual != NULL)
	{
		indice = atual->prox;
		while(indice != NULL)
		{
			// Compara se a arresta atual é maior que a arresta do índice //
			if(atual->arresta > indice->arresta)
			{
				aux = atual->arresta;
				atual->arresta = indice->arresta;
				indice->arresta = aux;
			}
			indice = indice->prox;
		}
		atual = atual->prox;
	}
}

void printar_grafo(Grafo *pGrafo)
{
	int i, j, count_entrada, count_saida;
	for(i = 1; i <= pGrafo->NVertice; i++)
	{
		printf("%d ", i);
		
		count_entrada = 0;
		count_saida = 0;
		// Conta o grau de entrada do vertice //
		for(j = 1; j <= pGrafo->NVertice; j++)
		{
			No *x = pGrafo->Lista[j];
			while(x)
			{
				if(x->arresta == i)
				{
					count_entrada++;
					break;
				}
				x = x->prox;
			}
		}
		printf("%d", count_entrada);
		
		// Conta o grau de saida do vertice //
		No *x = pGrafo->Lista[i];
		while(x)
		{
			if(cabeca == NULL)
			{
				cabeca = x;
				calda = x;
			}
			else
			{
				calda->prox = x;
				calda = x;
			}
			count_saida++;
			x = x->prox;
		}
		printf(" %d", count_saida);
		
		if(count_saida != 0)
		{
			ordernar_lista();
			
			No *atual = cabeca;
			while(atual)
			{
				printf(" %d", atual->arresta);
				atual = atual->prox;
			}
		}
		cabeca = NULL;
		calda = NULL;
		printf("\n");
	}
}

int main()
{
	int num_pacotes, num_dependencias;
	scanf("%d %d", &num_pacotes, &num_dependencias);
	
	Grafo *pGrafo = iniciar_grafo(pGrafo, num_pacotes);
	
	int u, v, i = 0;
	while(i != num_dependencias)
	{
		scanf("%d %d", &u, &v);
		inserir_arresta(pGrafo, u, v);
		i++;
	}
	printar_grafo(pGrafo);
	return 0;
}
