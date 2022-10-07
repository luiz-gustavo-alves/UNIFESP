/*TAD FILA-DINAMICA
LUIZ GUSTAVO ALVES ASSIS DA SILVA*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
  int forca_inicial, forca_atual, indice;
}Competidor;

typedef struct SCelula *Tapontador;

typedef struct SCelula{
  Competidor dados;
  Tapontador prox, frente, atras;
  int tamanho;
}Fila;

void iniciar_fila(Fila *pFila)
{
  pFila->frente = NULL;
  pFila->atras = pFila->frente;
  pFila->tamanho = 0;
}

int Fila_vazia(Fila *pFila)
{
  return (pFila->frente == NULL);
}

int Fila_tamanho(Fila *pFila)
{
  return (pFila->tamanho);
}

int enfileirar_fila(Fila *pFila, Competidor x)
{
  Tapontador pInformacao;
  
  pInformacao = (Tapontador) malloc(sizeof(Fila));
  pInformacao->dados = x;
  pInformacao->prox = NULL;

  if(Fila_vazia(pFila))
  {
    pFila->frente = pInformacao;
  }
  else
  {
    pFila->atras->prox = pInformacao;
  }
  
  pFila->atras = pInformacao;
  pFila->tamanho++;
  return 1;
}

Competidor desenfileirar_fila(Fila *pFila, Competidor aux)
{
  Tapontador pAux;
  
  pAux = pFila ->frente;
  pFila->frente = pAux->prox;
  aux = pAux->dados;
  free(pAux);
  pFila->tamanho--;
  
  return aux;
}

int main() 
{
	Fila *pFila = (Fila *)malloc(sizeof(Fila));
  	iniciar_fila(pFila);

  	int num_competidor, forca_descanso, tamanho_fila; 
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
    
    	competidor_1 = desenfileirar_fila(pFila, valor);
    	competidor_2 = desenfileirar_fila(pFila, valor);

    	if(competidor_1.forca_atual > competidor_2.forca_atual)
		{          
      		competidor_final.forca_inicial = competidor_1.forca_inicial;
      		competidor_final.forca_atual = (competidor_1.forca_atual - competidor_2.forca_atual);
      		competidor_final.indice = competidor_1.indice;
    	}	
    	else if(competidor_1.forca_atual < competidor_2.forca_atual)
		{
      		competidor_final.forca_inicial = competidor_2.forca_inicial;
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
	}	
  printf("%d", competidor_final.indice);
  return 0;
}
