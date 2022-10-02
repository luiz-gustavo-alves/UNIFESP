/*
 *    Problema 2
 *    Intercalação de Vetores
 *    Tempo Limite: 1,0 s (C)
 *
 *    NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
 *    
 */
 
#include <stdio.h>
#include <stdlib.h>
 
#define INF 2147483647
 
typedef struct {
    int termos;
    int head;
} NumTermos;
 
void intercalacaoPrimeirosTermos(int k, int num_intercalacao, int **vet, NumTermos *vet_num_termos)
{
    int n = 1;
    while (n < num_intercalacao)
    {
        int min = INF, next_head = 0, i;
        for (i = 0; i < k; i++)
        {
            if (vet[i][vet_num_termos[i].head] < min && vet_num_termos[i].head != vet_num_termos[i].termos)
            {
                min = vet[i][vet_num_termos[i].head];
                next_head = i;
            }
        }
        vet_num_termos[next_head].head++;
        n++;
    }
}
 
void somaPrimeirosTermos(int k, int **vet, NumTermos *vet_num_termos)
{
    long long soma = 0;
    
    int i;
    for (i = 0; i < k; i++)
    {
        if (vet_num_termos[i].head == vet_num_termos[i].termos)
        {
            continue;
        }
        soma += vet[i][vet_num_termos[i].head];
    }
    printf("%lld", soma);
}
 
int main()
{
    int k, num_intercalacao;
    scanf("%d %d", &k, &num_intercalacao);
    
    int **vet = (int**)malloc(k * sizeof(int*));
    
    NumTermos vet_num_termos[k];
    int num_termos = 0;
    
    int i, j;
    for (i = 0; i < k; i++)
    {
        scanf("%d", &num_termos);
        if (num_termos == 0)
        {
            vet[i] = (int*) malloc(1 * sizeof(int));
            {
                vet[i][0] = 0;
            }
        }
        else
        {
            vet[i] = (int*) malloc(num_termos * sizeof(int));
            for (j = 0; j < num_termos; j++)
            {
                scanf("%d", &vet[i][j]);    
            }
        }
        vet_num_termos[i].head = 0;
        vet_num_termos[i].termos = num_termos;
    }
    intercalacaoPrimeirosTermos(k, num_intercalacao, vet, vet_num_termos);
    somaPrimeirosTermos(k, vet, vet_num_termos);
    return 0;
}
