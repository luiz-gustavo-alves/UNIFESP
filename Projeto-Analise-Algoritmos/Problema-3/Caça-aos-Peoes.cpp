/*
 *    Problema 3
 *    Caça aos peões
 *    Tempo Limite: 0,5 s (C/C++)
 *
 *    NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
 *    
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define DIMENSAO 8
#define NUM_CELULAS DIMENSAO * DIMENSAO
 
#define REI 1
#define VIVO 2
#define MORTO 3
 
typedef struct posicao{
    int status[DIMENSAO];
    int x, y;
    int statusCavalo;
    int passos = 0;
} Posicao;
 
typedef struct {
    Posicao fila[NUM_CELULAS * DIMENSAO];
    int fim = 0;
    int ini = 0;
    int tamanho = 0;
} Fila;
 
Posicao get(Fila *f)
{
    return f->fila[f->ini];
}
 
void enfileira(Fila *f, Posicao p, int passos)
{
    if (f->fim + 1 == f->ini || (f->fim + 1 == NUM_CELULAS && !f->ini)) 
    {
        return;
    }
    
    passos++;
    p.passos = passos;
    f->fila[f->fim] = p;
    f->fim++;
    
    if (f->fim == NUM_CELULAS)
    {
        f->fim = 0;
    }
    
    f->tamanho++;
}
 
void desenfileira(Fila *f)
{
    if (f->ini == NUM_CELULAS) 
    {
        f->ini = 0;
    }
    
    f->ini++;
    f->tamanho--;
}
 
bool filaVazia(Fila f)
{
    return f.tamanho == 0;
}
 
bool mesmaPosicao(Posicao p, int x, int y)
{
    if (x == p.x && y == p.y)
    {
        return true;
    }
    return false;
}
 
bool atualizarMovimentoPeao(Posicao t, Posicao *p, int *posPeao, int qtdPosicoes)
{
    t.passos = p->passos;
    
    int count = 0;
    for (int k = 0; k < qtdPosicoes; k = k + 2) 
    {
        if (t.status[count] == MORTO)
        {
            count++;
            continue;
        }
        
        int x = posPeao[k] + t.passos;
        int y = posPeao[k + 1];
        
        if (mesmaPosicao(t, x, y))             
        {
            /* CAVALO COMEU O PEÃO */
            t.status[count] = MORTO;
            count++;
            continue;
        }
        
        if (t.status[count] == REI)
        {
            /* REI COMEU O CAVALO */
            t.statusCavalo = MORTO;
            return false;
        }
        
        x = posPeao[k] + 1;
        
        if (mesmaPosicao(t, x, y))             
        {
            /* PEÃO COMEU O CAVALO */
            t.statusCavalo = MORTO;
            return false;
        }
        
        if (x == 7)
        {
            t.status[count] = REI;
        }
        count++;
    }
    *p = t;
    return true;
}
 
bool vitoria(Posicao *p, int qtdPosicoes) 
{
    if (p->statusCavalo != VIVO)
    {
        return false;
    }
    
    qtdPosicoes = qtdPosicoes / 2;
    for (int k = 0; k < qtdPosicoes; k++)
    {
        if (p->status[k] == MORTO)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
 
int main() 
{    
    int *posPeao;
    Posicao p;
    
    int qtdPeao;
    scanf("%d", &qtdPeao);
    
    int qtdPosicoes;
    if (qtdPeao == 1)
    {
        qtdPosicoes = 2;
    }
    else
    {
        qtdPosicoes = qtdPeao * 2;
    }
    
    posPeao = new int(qtdPosicoes);
    
    int count = 0;
    int pos, i, j;
    for (int k = 0; k < qtdPosicoes; k = k + 2)
    {
        scanf("%d", &pos);
        
        i = floor( (pos - 1) / 8);        
        j = (pos - 1) % 8;
        
        if (i == 7)    
        {
            /* VERIFICANDO SE A POSIÇÃO INICIAL DO PEÃO ESTÁ EM (56-63) */
            p.status[count] = REI;
        }    
        else
        {
            p.status[count] = VIVO;
        }
        posPeao[k] = i;
        posPeao[k + 1] = j;
        count++;                        
    }
    
    int posCavalo;
    scanf("%d", &posCavalo);
    
    i = floor( (posCavalo - 1) / 8);
    j = (posCavalo - 1) % 8;
    
    p.statusCavalo = VIVO;
    p.x = i;
    p.y = j;
    
    /* ALGORITMO BFS */
    
    int x = p.x;
    int y = p.y;
    
    Fila f;
    enfileira(&f, p, 0);
    
    int X[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int Y[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
    
    bool visitado[DIMENSAO][DIMENSAO] = { {false} };
    
    Posicao t;
    while (!filaVazia(f))
    {     
        t = get(&f);
        desenfileira(&f);
        
        int x_cavalo = t.x;
        int y_cavalo = t.y;
        
        visitado[x_cavalo][y_cavalo] = true;
        
        for (int k = 0; k < DIMENSAO; k++)
        {
            x = x_cavalo + X[k];
            y = y_cavalo + Y[k];
             
            if (x >= 0 && y >= 0 && x < DIMENSAO && y < DIMENSAO && !visitado[x][y])
            {    
                t.x = x;
                t.y = y;
                
                if (atualizarMovimentoPeao(t, &p, posPeao, qtdPosicoes))
                {
                    if (vitoria(&p, qtdPosicoes))
                    {
                        printf("%d", p.passos + 1);
                        return 0;
                    }
                    int passos = p.passos;
                    enfileira(&f, p, passos);
                }
            }
        }
        
        if (!filaVazia(f))
        {
            p = get(&f);
        }
        else
        {
            printf("impossible");
        }
    }
    return 0;
}