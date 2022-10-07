/*---TAD MATRIZ DE ADJACÊNCIA---
LUIZ GUSTAVO ALVES ASSIS DA SILVA--*/

#include <stdio.h>
#include <stdlib.h>

#define MAXVERTICES 100

typedef struct matriz{
	int incide_arresta;
	int arresta;
}Matriz;

typedef struct grafo{
	Matriz adjacencia[MAXVERTICES][MAXVERTICES];
	int NVertice;
}Grafo;

typedef struct no{
	int NArresta;
	struct no *prox;
}No;

typedef struct lista{
	No *inicio;
	int tamanho;
}Lista;

Grafo *iniciar_grafo(Grafo *pGrafo, int num_vertice)
{
	if(num_vertice > MAXVERTICES)
	{
		return NULL;
	}
	
	Grafo *aux = (Grafo*)malloc(sizeof(Grafo));
	aux->NVertice = num_vertice;
	
	int i, j;
	for(i = 1; i <= aux->NVertice; i++)
	{
		for(j = 1; j <= aux->NVertice; j++)
		{
			aux->adjacencia[i][j].incide_arresta = 0;
		}
	}
	return aux;	
}

int verificar_arresta(Grafo *pGrafo, int u, int v)
{
	return pGrafo->adjacencia[u][v].incide_arresta;
}

void inserir_arresta(Grafo *pGrafo, int u, int v)
{
	pGrafo->adjacencia[u][v].incide_arresta = 1;
	pGrafo->adjacencia[u][v].arresta = v;
}

No *novoNo(int num_arresta)
{
	No *aux = (No*)malloc(sizeof(No));
	aux->NArresta = num_arresta;
	aux->prox = NULL;
	return aux;
}

Lista *novaLista()
{
	Lista *aux = (Lista*)malloc(sizeof(Lista));
	aux->inicio = NULL;
	aux->tamanho = 0;
	return aux;
}

int inserir_lista(Lista *li, int num_arresta)
{
	No *x = novoNo(num_arresta);
	
	if(li->tamanho == 0)
	{
		li->inicio = x;
		li->inicio->prox;
	}
	else
	{
		x->prox = li->inicio;
		li->inicio->prox = x;
	}
	li->tamanho++;
}

void printar_lista(Lista *li)
{
    No *aux = li->inicio;
    
    int i = 0;
	while(i != li->tamanho)
	{
		printf(" %d", aux->NArresta);
		aux = aux->prox;
		i++;
	}       
}

void liberar_lista(Lista *li)
{
	free(li);
}

void printar_grafo(Grafo *pGrafo)
{
	Lista *li;
	
	int i, j, count_entrada, count_saida;
	for(i = 1; i <= pGrafo->NVertice; i++)
	{
		printf("%d ", i);
		
		li = novaLista();
		count_entrada = 0;
		count_saida = 0;
	
		for(j = 1; j <= pGrafo->NVertice; j++)
		{
			if(verificar_arresta(pGrafo, j, i) == 1)
			{
				count_entrada++;
			}
			if(verificar_arresta(pGrafo, i, j) == 1)
			{
				int num_arresta = j;
				inserir_lista(li, num_arresta);
				count_saida++;
			}
		}
		printf("%d", count_entrada);
		printf(" %d", count_saida);
		
		if(count_saida != 0)
		{
			printar_lista(li);
		}
		if(i != pGrafo->NVertice)
		{
			printf("\n");
		}
		liberar_lista(li);	
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
