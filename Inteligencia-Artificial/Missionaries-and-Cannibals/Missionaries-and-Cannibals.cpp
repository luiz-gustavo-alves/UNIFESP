/* - - - - - - - - - - - - - - - - - - - - - - -
 *
 *    Problema 2							   
 *    Missionários e Canibais					   			   
 *					
 *    NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */
 
#include <iostream>
#include <string>
#include <queue>
#include <list>

using namespace std;

int num_estados;

typedef struct {
	int canibal_esq;
	int canibal_dir;
	int missio_esq;
	int missio_dir;
	string barco;
} Estado;

void arvoreSolucao(Estado estadoVisitado[], int qtd_estados)
{
	cout << "ESPACO TOTAL DE ESTADOS:\n(BARCO - CANIBAL ESQUERDA - MISSIONARIO ESQUERDA - CANIBAL DIREITA - MISSIONARIO DIREITA)" << endl << endl;
	for (int i = 0; i < qtd_estados; i++)
	{
		cout << estadoVisitado[i].barco << " " << estadoVisitado[i].canibal_esq << " " << estadoVisitado[i].missio_esq << 
			" " << estadoVisitado[i].canibal_dir << " " << estadoVisitado[i].missio_dir << endl;	
	}
}

bool visitado(Estado e, Estado estadoVisitado[], int qtd_estados)
{	
	/* ITERANDO EM CADA ESTADO VISITADO */
	for (int i = 0; i < qtd_estados; i++)
	{
		if ((e.canibal_esq == estadoVisitado[i].canibal_esq) && (e.canibal_dir == estadoVisitado[i].canibal_dir)
			 && (e.missio_esq == estadoVisitado[i].missio_esq) && (e.missio_dir == estadoVisitado[i].missio_dir) 
			 && (e.barco == estadoVisitado[i].barco))
			return true;
	}
	return false;
}

bool solucao(Estado e, string lado)
{
	if (lado == "esquerda") 
		return (e.canibal_dir == num_estados) && (e.missio_dir == num_estados); 
		
	else if (lado == "direita") 
		return (e.canibal_esq == num_estados) && (e.missio_esq == num_estados);
}

bool posValida(Estado e)
{
	/* VERIFICAR SE A QUANTIDADE DE MISSIONARIOS É IGUAL A 0*/
	if (e.missio_esq == 0 || e.missio_dir == 0 )
	{
		/* VERIFICAR SE A QUANTIDADE DE CANIBAIS NÃO EXCEDEU OS LIMITES DO JOGO */
		if ((e.canibal_esq >= 0 && e.canibal_esq <= num_estados) && (e.canibal_dir >= 0 && e.canibal_dir <= num_estados))
			return true;	
	}
	
	/* VERIFICAR SE A QUANTIDADE DE CANIBAIS É MAIOR QUE A DE MISSIONARIOS*/
	if (e.canibal_esq <= e.missio_esq && e.canibal_dir <= e.missio_dir)
	{
		/* VERIFICAR SE A QUANTIDADE DE CANIBAIS E MISSIONARIOS NÃO EXCEDEU OS LIMITES DO JOGO */
		if ((e.canibal_esq >= 0 && e.canibal_esq <= num_estados) && (e.canibal_dir >= 0 && e.canibal_dir <= num_estados) 
			&& (e.missio_esq >= 0 && e.missio_esq <= num_estados) && (e.missio_dir >= 0 && e.missio_dir <= num_estados))
			return true;
	}
	return false;
}

Estado BFS(Estado e, string lado)
{
	/* INICIAR FILA DE ESTADOS */
	queue<Estado> fila;
	fila.push(e);
	
	/* ARRAY DE ESTADOS PARA VERIFICAR ESTADOS JÁ VISITADAS */
	Estado estadoVisitado[1000];
	estadoVisitado[0] = e;
	
	/* VALORES DE DESLOCAMENTO DE CANIBAIS E MISSIONARIOS - (CAPACIDADE DO BARCO É IGUAL A 2) */
	int e_canibal[] = {1, 2, 0, 0, 1};
	int e_missio[] = {0, 0, 1, 2, 1};
	
	int qtd_estados = 1;
	while (!fila.empty())
	{
		Estado filho = fila.front();
		fila.pop();		
			
		/* ITERARANDO EM CADA DIREÇÃO */	
		for (int i = 0; i < 5; i++)
		{
			Estado novoFilho;
			string barco;
			
			/* BARCO ESTÁ NO LADO ESQUERDO DO RIO */
			if (filho.barco == "esquerda")
			{
				novoFilho.canibal_esq = filho.canibal_esq - e_canibal[i];
				novoFilho.canibal_dir = filho.canibal_dir + e_canibal[i];
				novoFilho.missio_esq = filho.missio_esq - e_missio[i];
				novoFilho.missio_dir = filho.missio_dir + e_missio[i];
				novoFilho.barco = "direita";
			}
			
			/* BARCO ESTÁ NO LADO DIREITO DO RIO */
			else if (filho.barco == "direita")
			{
				novoFilho.canibal_esq = filho.canibal_esq + e_canibal[i];
				novoFilho.canibal_dir = filho.canibal_dir - e_canibal[i];
				novoFilho.missio_esq = filho.missio_esq + e_missio[i];
				novoFilho.missio_dir = filho.missio_dir - e_missio[i];
				novoFilho.barco = "esquerda";
			}
			
			/* CHECANDO VALIDADE DE MOVIMENTO */
			if (posValida(novoFilho) && !visitado(novoFilho, estadoVisitado, qtd_estados))
			{		
				/* VERIFICAR SOLUÇÃO */
				if (solucao(novoFilho, lado)) 
				{
					cout << "\nSOLUCAO ENCONTRADA!!" << endl << endl;
					arvoreSolucao(estadoVisitado, qtd_estados);
					return novoFilho;
				}
					
				/* ATRIBUIR NOVO FILHO A FILA DE ESTADOS */
				estadoVisitado[qtd_estados] = novoFilho;
				fila.push(novoFilho);
				qtd_estados++;
			}	
		}	
	}	
	Estado morto;
	morto.canibal_esq = 0;
	morto.canibal_dir = 0;
	morto.missio_esq = 0;
	morto.missio_dir = 0;
	morto.barco = "NULL";
	
	cout << "\nSOLUCAO NAO ENCONTRADA.." << endl;
	return morto;
}

Estado iniciar(string lado)
{
	Estado e;
	
	if (lado == "esquerda")
	{
		e.canibal_esq = num_estados;
		e.canibal_dir = 0;
		e.missio_esq = num_estados;
		e.missio_dir = 0;
	}
	else if (lado == "direita")
	{
		e.canibal_esq = 0;
		e.canibal_dir = num_estados;
		e.missio_esq = 0;
		e.missio_dir = num_estados;
	}
	e.barco = lado;
	return e;
}

int main()
{
	cout << "INSIRA A QUANTIDADE DE CANIBAIS E MISSIONARIOS - (EXEMPLO: 3): ";
	cin >> num_estados;
	
	string lado;
	cout << "INFORME O LADO DO RIO - (EXEMPLO: direita): ";
	getline(cin >> ws, lado);
	
	Estado e = iniciar(lado);
	
	Estado final = BFS(e, lado);
	cout << final.barco << " " << final.canibal_esq << " " <<  final.missio_esq << " " << final.canibal_dir << " " << final.missio_dir;
	return 0;
}
