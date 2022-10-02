/*
 *    Problema 1
 *    Ado��o de tecnologia
 *    Tempo Limite: 1,0 s (C/C++)
 *
 *    JUDGE: luizgustavo149115
 *    NOME: LUIZ GUSTAVO ALVES ASSIS DA SILVA
 *    RA: 149115    
 *    
 */
 
 #include <stdio.h>
 #include <math.h>
 
void count_dias(int qtdIniUsuarios, int qtdFinalUsuarios, int count, int media, int somatorioParcial, bool convergencia)
{
    if (convergencia)
    {
        int countParcial = ceil((qtdIniUsuarios - qtdFinalUsuarios) / media);
        int qtdUsuarios = (countParcial - count) * media;
        
        qtdUsuarios += somatorioParcial;
        while (qtdUsuarios < qtdFinalUsuarios - qtdIniUsuarios)
        {
            qtdUsuarios += media;
            countParcial++;
        }
        printf("%d", countParcial);
    }
    else
    {
        printf("%d", count);
    }
}

bool flag_convergencia(int *qtdNovosUsuarios, int media)
{
	/*
     * 	FUN��O QUE VERIFICA SE TODOS OS N�MEROS DO ARRAY S�O IGUAIS
     *	CASO VERDADEIRO, A FLAG DE CONVERGENCIA � ATIVADA.
     */
     
    bool convergencia = false;
     
	int count = 0;
    for (int i = 0; i < 30; i++)
    {
        if (media == qtdNovosUsuarios[i])
        {
            count++;
        }
        else
        {
        	break;
		}      
    }
    
    if (count == 30)
    {
        convergencia = true;
    }
    return convergencia;
} 
 
void verificar_convergencia(int *qtdNovosUsuarios, int qtdIniUsuarios, int qtdFinalUsuarios, float somatorioUsuarios)
{
	bool convergencia = false; // FLAG PARA VERIFICAR CONVERG�NCIA NO SOMAT�RIO DA M�DIA
	
    int count = 0, dia = 1, somatorioParcial = 0, qtdUsuarios = qtdIniUsuarios, media;
    while (qtdUsuarios < qtdFinalUsuarios && !convergencia)
    {    
        if (dia == 31)
        {
            dia = 1;
        }
        
        media = ceil(somatorioUsuarios / 30);
        
        qtdUsuarios += media;
        somatorioParcial += media;
        
        somatorioUsuarios -= qtdNovosUsuarios[dia - 1];
        qtdNovosUsuarios[dia - 1] = media;
        somatorioUsuarios += media;
        	
		convergencia = flag_convergencia(qtdNovosUsuarios, media); 
		
        dia++;
        count++;
    }
    count_dias(qtdIniUsuarios, qtdFinalUsuarios, count, media, somatorioParcial, convergencia);    
}
 
void inserir_dados(int *qtdNovosUsuarios, float &somatorioUsuarios)
{
    for (int i = 0; i < 30; i++)
    {
        scanf("%d", &qtdNovosUsuarios[i]);
        somatorioUsuarios += qtdNovosUsuarios[i];
    }
}
 
int main()
{
    int qtdIniUsuarios, qtdFinalUsuarios, qtdNovosUsuarios[30];
    scanf("%d %d", &qtdIniUsuarios, &qtdFinalUsuarios);
    
    float somatorioUsuarios = 0;
    inserir_dados(qtdNovosUsuarios, somatorioUsuarios);
    
    verificar_convergencia(qtdNovosUsuarios, qtdIniUsuarios, qtdFinalUsuarios, somatorioUsuarios);
    return 0;
}
