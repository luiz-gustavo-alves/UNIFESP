/*---TAD LISTA CIRCULAR---
LUIZ GUSTAVO ALVES ASSIS DA SILVA--*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCARACTERES 50000

typedef struct no{
	char item;
	struct no *prox;
}No;

typedef struct lista{
	No *inicio;
	int tamanho;
}Lista;

No *novoNo(char item)
{
	No *aux = (No*)malloc(sizeof(No));
	aux->item = item;
	aux->prox = NULL;
	return aux;
}

Lista *iniciarLista()
{
	Lista *aux = (Lista*)malloc(sizeof(Lista));
	aux->inicio = NULL;
	aux->tamanho = 0;
	return aux;
}

No *getPos(Lista *li, int pos)
{
	No *aux = li->inicio;
	int i;
	for(i = 0; i < pos; i++)
	{
		aux = aux->prox;
	}
	return aux;
}

void inserirCaractere(Lista *li, char item, int pos)
{
	No *x = novoNo(item);
	
	if (li->tamanho == 0)
	{
		li->inicio = x;
		li->inicio->prox;		
	}
	else if(pos == 0)
	{
		x->prox = li->inicio;
		li->inicio = x;
	}
	else
	{
		No *aux = getPos(li, pos - 1);
		x->prox = aux->prox;
		aux->prox = x;
	}
	li->tamanho++;
}

void removerCaractere(Lista *li, int pos)
{
    if(pos > 0)
    {
        No *aux = getPos(li, pos - 1);
        No *x = aux->prox;
        aux->prox = aux->prox->prox;
    }
    else
    {
        No *x = li->inicio;
        li->inicio = li->inicio->prox;
    }
    li->tamanho--;
}

void printarLista(Lista *li)
{
	No *aux = li->inicio;
	while(aux != NULL)
	{
		printf("%c", aux->item);
		aux = aux->prox;
	}
}

int main()
{
	char letra, frase[MAXCARACTERES];
    gets(frase);
    
    Lista *li = iniciarLista();
    
    int i, pos = 0;
    for(i = 0; i < strlen(frase); i++)
    {
    	letra = frase[i];
    	switch(letra)
    	{
    		case'[':
    			pos = 0;
    			continue;
    		case ']':
    			pos = li->tamanho;
    			continue;
    		case'-':
    			if (pos != 0)
    			{
    				pos--;
    				removerCaractere(li, pos);
				}
				continue;
			case'<':
				if (pos != 0)
				{
					pos--;
				}
				continue;
			case'>':
				if (pos != li->tamanho)
				{
					pos++;	
				}
				continue;
			default:
				inserirCaractere(li, letra, pos);
				pos++;				
		}
	}
	printarLista(li);
	return 0;	
}
