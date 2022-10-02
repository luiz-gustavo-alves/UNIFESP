/* - - - - - - - - - - - - - - - - - - - - - - -
 *	  https://www.beecrowd.com.br/judge/pt/problems/view/1756
 *
 *    Problema 3							   
 *    Algoritmo Genético					   			   
 *					
 *    NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */
 
#include <iostream>
#include <iomanip>

#define ROW 3
#define COL 8

char cromossomo[ROW][COL];
char matrizCrossover[2][COL];

using namespace std;

void calcular_probabilidade(int qtd_bits, double prob)
{
	double P[ROW];
	double k;
	
	/* CALCULANDO P(A) E P(B) */
	for (int i = 0; i < 2; i++)
	{
		double op = 1;
		for (int j = 0; j < qtd_bits; j++)
		{
			if (cromossomo[2][j] == matrizCrossover[i][j])
			{
				k = (1 - prob);
			}
			else
			{
				k = prob;
			}	
			op = k * op;
		}
		P[i] = op;
	}
	
	/* CALCULANDO UNIÃO DE PROBABILIDADES P(A U B) */
	P[2] = P[0] * P[1];
	
	prob = P[0] + P[1] - P[2];
	cout << fixed << setprecision(7) << prob << endl;
}

void crossover(int qtd_bits, int pos_corte)
{
	int pos_gene = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < qtd_bits; j++)
		{
			if (j < pos_corte) 
			{
				matrizCrossover[i][j] = cromossomo[i][j];
			}
			matrizCrossover[i][j + pos_corte] = cromossomo[i + pos_gene][j + pos_corte];
		}
		pos_gene = -1;
	}
}

int main() 
{
	int num_testes;
	cin >> num_testes;

	string gene;
	int qtd_bits, pos_corte;
	double prob;
	
	for (int i = 0; i < num_testes; i++)
	{
		cin >> qtd_bits;
		cin >> pos_corte >> prob;
		
		for (int j = 0; j < ROW; j++)
		{
			cin >> gene;
			for (int k = 0; k < qtd_bits; k++)
			{
				cromossomo[j][k] = gene[k];
			}
		}
		crossover(qtd_bits, pos_corte);
		calcular_probabilidade(qtd_bits, prob);
	}	
	return 0;
}