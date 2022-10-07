/*TAD FILA-ESTATICA
LUIZ GUSTAVO ALVES ASSIS DA SILVA*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXTAM 32775

typedef struct{
	int forca_inicial, forca_atual, indice;
}Competidor;

typedef int Tapontador;

typedef struct fila{
	Tapontador inicio, fim, tamanho;
 	Competidor dados[MAXTAM];
}Fila;

void iniciar_fila(Fila *pFila)
{
	pFila->inicio = 0;
	pFila->fim = 0;
	pFila->tamanho = 0;
}

int Fila_tamanho(Fila *pFila)
{
  return pFila->tamanho;
}

int enfileirar_fila(Fila *pFila, Competidor novo)
{
	if(pFila->tamanho == MAXTAM)
	{
		return 1;
	}
	pFila->dados[pFila->fim] = novo;
	pFila->fim = (pFila->fim + 1)%MAXTAM;
	pFila->tamanho++;
}

Competidor desenfileirar_fila(Fila *pFila, Competidor *valor)
{
	if(pFila->fim == 0)
	{
		return *valor;
	}
	*valor = pFila->dados[pFila->inicio];
	pFila->inicio = (pFila->inicio + 1 )%MAXTAM;
	pFila->tamanho--;
	return *valor;
}

int main()
{  
	Fila *pFila = (Fila *)malloc(sizeof(Fila));
	iniciar_fila(pFila);
	
	int num_competidor, tamanho_fila, forca_descanso;
	Competidor valor, competidor_1, competidor_2, competidor_final;
	
	scanf("%d %d", &num_competidor, &forca_descanso);
	tamanho_fila = pow(2, num_competidor);
	
	int i;
	
	for(i = 0; i < tamanho_fila; i++)
	{
		scanf("%d", &valor.forca_inicial);
		valor.indice = i+1;
		valor.forca_atual = valor.forca_inicial;
		enfileirar_fila(pFila, valor);
	}
	
	while (Fila_tamanho(pFila) > 1){
		
		competidor_1 = desenfileirar_fila(pFila, &valor);
		competidor_2 = desenfileirar_fila(pFila, &valor);
		
		if(competidor_1.forca_atual > competidor_2.forca_atual)
		{          
	    	competidor_final.forca_inicial = competidor_1.forca_inicial;
	      	competidor_final.forca_atual = (competidor_1.forca_atual - competidor_2.forca_atual);
	      	competidor_final.indice = competidor_1.indice;
	    }
	    else if(competidor_1.forca_atual < competidor_2.forca_atual)
		{
	      	competidor_final. forca_inicial = competidor_2.forca_inicial;
	      	competidor_final.forca_atual = (competidor_2.forca_atual - competidor_1.forca_atual);
	      	competidor_final.indice = competidor_2.indice;
	    }
	    else
		{
	      if(competidor_1.indice < competidor_2.indice)
		  {
	    	competidor_final.forca_inicial = competidor_1.forca_inicial;
	        	competidor_final.forca_atual = (competidor_1.forca_atual - competidor_2.forca_atual);
	        	competidor_final.indice = competidor_1.indice;
	      }
		  else if(competidor_1.indice > competidor_2.indice)
		  {
	        	competidor_final.forca_inicial = competidor_2.forca_inicial;
	        	competidor_final.forca_atual = (competidor_2.forca_atual - competidor_1.forca_atual);
	        	competidor_final.indice = competidor_2.indice;
	      }
	    }
	    if(competidor_final.forca_atual + forca_descanso > competidor_final.forca_inicial)
		{
	      	competidor_final.forca_atual = competidor_final.forca_inicial;
	    }
	    else
		{
	      	competidor_final.forca_atual += forca_descanso;
	    }
	    enfileirar_fila(pFila, competidor_final);
	}
	printf("%d", competidor_final.indice);
}
