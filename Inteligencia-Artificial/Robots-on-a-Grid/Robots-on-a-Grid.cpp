/* - - - - - - - - - - - - - - - - - - - - - - -
 *
 *	  https://www.udebug.com/URI/3247	
 *
 *    Problema 1							   
 *    Robôs em uma grade					   
 *    Tempo Limite: 1 s (C++)		   
 *					
 *    NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA   
 */
 
#include <iostream>
#include <string>
#include <queue>

#define INT_MAX 2147483647

using namespace std;

const long long mod = INT_MAX;
long long dp[1004][1004];

string grade[1004];

bool BFS(int num_linhas)
{
	queue<pair<int, int> > fila;
	fila.push(make_pair(0, 0));
	
	/* FLAG PARA VERIFICAR POSIÇÕES JÁ VISITADAS */
	bool visitado[num_linhas][num_linhas] = { {false} };
	visitado[0][0] = true;
	
	/* VALORES PARA DIREITA, ESQUERDA, BAIXO, CIMA (RESPECTIVAMENTE) */
	int coluna[] = {1, -1, 0, 0};
	int linha[] = {0, 0, 1, -1};
	
	while (!fila.empty())
	{
		pair<int, int> coordenada = fila.front();
		fila.pop();	
		
		/* VERIFICAR SOLUÇÃO */
		if (coordenada.first == num_linhas - 1 && coordenada.second == num_linhas - 1)
			return true;
			
		/* ITERARANDO EM CADA DIREÇÃO */	
		for (int i = 0; i < 4; i++)
		{
			int x = coordenada.first + coluna[i];
			int y = coordenada.second + linha[i];
			
			if (x >= 0 && x < num_linhas && y >= 0 && y < num_linhas && !visitado[x][y] && grade[x][y] == '.')
			{					
				visitado[x][y] = true;
				fila.push(make_pair(x, y));
			}	
		}	
	}
	return false;
}

int countCaminhos(int num_linhas)
{
	dp[0][0] = 1;
	
	for (int i = 0; i < num_linhas; i++)
	{
		for (int j = 0; j < num_linhas; j++)
		{
			if (i == 0 && j == 0)
				continue;
				
			dp[i][j] = 0;
			
			if (grade[i][j] == '.')
			{
				if (j - 1 >= 0)
					dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;	
					
				if (i - 1 >= 0)
					dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
			}	
		}
	}
	return dp[num_linhas - 1][num_linhas - 1];
} 
 
int main()
{
	int num_linhas;
	cin >> num_linhas;
	
	string str;
	for (int i = 0; i < num_linhas; i++)
	{
		getline(cin >> ws, str);
		grade[i] = str;
	}
	
	int num_caminhos = countCaminhos(num_linhas);
	if (num_caminhos > 0)
	{
		cout << num_caminhos;
	}
	else
	{
		bool flag = BFS(num_linhas);
		
		if (flag)
			cout << "THE GAME IS A LIE";
		
		else
			cout << "INCONCEIVABLE";
	}
	return 0;
}
