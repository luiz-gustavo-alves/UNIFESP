/* TAD ÁRVORE BINÁRIA POR PARÊNTESES ANINHADOS----
----LUIZ GUSTAVO ALVES ASSIS DA SILVA */

#include <stdio.h>
#include <stdlib.h>

typedef struct noArvore{
	struct noArvore *esquerda, *direita;
	int item;
}No;

No *noRaiz()
{
	return NULL;
}

No *valorMin(No *Arvore)
{
	if (Arvore != NULL)
	{
		No *x = Arvore;
		while (x->esquerda != NULL)
		{
			x = Arvore->esquerda;
		}
		return x;
	}
	return NULL;
}

No *pesquisaBinaria(No *Arvore, int item)
{
	if (Arvore != NULL)
	{
		if (item == Arvore->item)
		{
			return Arvore;
		}
		else if (item < Arvore->item)
		{
			return pesquisaBinaria(Arvore->esquerda, item);
		}
		else if (item > Arvore->item)
		{
			return pesquisaBinaria(Arvore->direita, item);
		}
	}
	return NULL;
}

No *inserirNo(No *Arvore, int item)
{
	if (Arvore == NULL)
	{
		No *x = (No*)malloc(sizeof(No));
		x->item = item;
		x->esquerda = NULL;
		x->direita = NULL;
		return x;
	}
	else
	{
		if (item < Arvore->item)
		{
			Arvore->esquerda = inserirNo(Arvore->esquerda, item);
		}
		else if (item > Arvore->item)
		{
			Arvore->direita = inserirNo(Arvore->direita, item);
		}
		else if (item == Arvore->item)
		{
			return NULL;
		}
	}
}

No *removerNo(No *Arvore, int item)
{
	if (Arvore != NULL)
	{
		if (item < Arvore->item)
		{
			Arvore->esquerda = removerNo(Arvore->esquerda, item);
		}
		else if (item > Arvore->item)
		{
			Arvore->direita = removerNo(Arvore->direita, item);
		}
		else if (item == Arvore->item)
		{
			if (Arvore->esquerda == NULL && Arvore->direita == NULL)
			{
				free(Arvore);
				return NULL;
			}
			else if (Arvore->esquerda != NULL && Arvore->direita == NULL)
			{
				No *aux = Arvore->esquerda;
				free(Arvore);
				return aux;
			}
			else if (Arvore->esquerda == NULL && Arvore->direita != NULL)
			{
				No *aux = Arvore->direita;
				free(Arvore);
				return aux;
			}
			else if (Arvore->esquerda != NULL && Arvore->direita != NULL);
			{
				No *aux = valorMin(Arvore->direita);
				int itemAux = aux->item;
				Arvore = removerNo(Arvore, itemAux);
				Arvore->item = itemAux;
			}
		}
		return Arvore;
	}
	return NULL;
}

void printArvore(No *Arvore)
{
	if (Arvore != NULL)
	{
		printf("(C%d", Arvore->item);
		printArvore(Arvore->esquerda);
		printArvore(Arvore->direita);
		printf(")");
	}
	else if (Arvore == NULL)
	{
		printf("()");
	}
}

void liberarArvore(No *Arvore)
{
	if (Arvore != NULL)
	{
		liberarArvore(Arvore->esquerda);
		liberarArvore(Arvore->direita);
		free(Arvore);
	}
}

int main()
{
	No *Arvore = noRaiz(); 
	
	int num_itens;
	scanf("%d", &num_itens);
	
	int item;
	for (int i = 0; i < num_itens; i++)
	{
		scanf("%d", &item);
		Arvore = inserirNo(Arvore, item);
	}
	scanf("%d", &item);
	
	if (pesquisaBinaria(Arvore, item) == NULL)
	{
		Arvore = inserirNo(Arvore, item);
	}
	else
	{
		Arvore = removerNo(Arvore, item);
	}
	printArvore(Arvore);
	liberarArvore(Arvore);
	return 0;
}
