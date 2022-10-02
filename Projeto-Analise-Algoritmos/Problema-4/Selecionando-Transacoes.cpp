/*
 *    Problema 4
 *    Selecionando Transações
 *    Tempo Limite: 0,5 s (C/C++)
 *
 *    NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
 *    
 */
 
#include <iostream>
 
using namespace std;
 
struct Transacao
{
    int taxa, tamanho;
};
 
int maxSum(Transacao vet[], int N, int C)
{
    int tabela[C + 1] = {0};
	for (int i = 1; i < N + 1; i++) 
	{
		for (int j = C; j >= 0; j--) 
		{
			if (vet[i - 1].tamanho <= j)
			{
				tabela[j] = max(tabela[j], tabela[j - vet[i - 1].tamanho] + vet[i - 1].taxa);
			}
		}
	}
	return tabela[C];
}

int main() 
{
    int N, C;
    cin >> N >> C;
    
    Transacao *vet= new Transacao[N];
    
    for (int i = 0; i < N; i++)
    {
        cin >> vet[i].taxa >> vet[i].tamanho;
    }

    int maxTaxa = maxSum(vet, N, C);
    cout << maxTaxa; 
    
	return 0;   
}
