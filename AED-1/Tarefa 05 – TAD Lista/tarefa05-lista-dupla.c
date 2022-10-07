/*---TAD LISTA DUPLA---
LUIZ GUSTAVO ALVES ASSIS DA SILVA--*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define MAXTAM 60000
 
typedef struct No
{
    char texto;
    struct No *prox;
    struct No *antes;
}No;
 
typedef struct Lista{
    No* inicio;
    int tamanho;
}Lista;
 
No *novoNo(char texto)
{
    No *aux = (No*)malloc(sizeof(No));
    aux->texto = texto;
    aux->prox = NULL;
    aux->antes = NULL;
    return aux;
}
 
Lista *novaLista()
{
    Lista *aux = (Lista*)malloc(sizeof(Lista));
    aux->inicio = NULL;
    aux->tamanho = 0;
    return aux;
}
 
No *get(Lista *li, int pos)
{
    No *aux = li->inicio;
    int i;
    for(i = 0; i < pos; i++)
    {
        aux = aux->prox;
    }
    return aux;
}
 
bool lista_vazia(Lista *li)
{
	if(li->tamanho == 0)
	{
		return true;
	}
	return false;
}
 
void inserir(Lista *li, char letra, int pos)
{
    No *x = novoNo(letra);
    
    if(lista_vazia(li))
    {
        li->inicio = x;
        x->prox = x;
        x->antes = x;
    }    
    else if(pos == 0)
    {
        x->prox = li->inicio->prox;
        x->antes = li->inicio;
        li->inicio = x;
        li->inicio->prox = x->antes;
        li->inicio->prox->antes = x->prox;
    }
    else
    {
        No *p = get(li, pos - 1);
        x->prox = p->prox;
        x->antes = p->antes;
        p->prox = x;
        p->antes = x;
    }
    li->tamanho++;
}
 
 
void remover(Lista *li, int pos)
{
    if(pos > 0)
    {
        No *aux = get(li, pos - 1);
        aux->prox = aux->prox->prox;
        aux->antes = aux->antes->antes;
        No *x = aux->prox;
    }
    else
    {
        No *x = li->inicio;
        li->inicio = li->inicio->prox;
        free(x);
    }
    li->tamanho--;
}
 
void print_lista(Lista *li)
{
    No *aux = li->inicio;
    int j = 0;
    if(aux != NULL)
    {
        printf("%c", aux->texto);
        aux = aux->prox;
        while(aux != li->inicio) 
        {
            if(j == li->tamanho - 1)
            {
                break;
            }
            printf("%c", aux->texto);
            aux = aux->prox;
            j++;
        }
    }            
}
 
int main()
{    
    char letra, frase[MAXTAM];
    gets(frase);
    
    Lista *li = novaLista();
    
    int i, pos = 0;
    for(i = 0; i < strlen(frase) ; i++)
    {
        letra = frase[i];
        switch(frase[i])
        {
            case']':
                pos = li->tamanho;
                break;
                
            case'[':
                pos = 0;
                break;    
                
            case'<':
                if(pos != 0)
                {
                	pos--;
                }           
                break;
                
            case'>':
                if(pos != li->tamanho)
                {
                    pos++;
                }
                break;
            
            case'-':
                if(pos != 0)
                {
    				pos--;
                	remover(li, pos);
                }
                break;    
                 
            default:
                inserir(li, letra, pos);    
                pos++;                            
        }
    }
    print_lista(li);
    return 0;
}
