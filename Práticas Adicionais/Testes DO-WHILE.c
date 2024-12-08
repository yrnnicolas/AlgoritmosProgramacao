/* Programa que calcula estatisticas sobre preferencia de clubes, salario e cidadede
origem para um grupo de torcedores
Entradas: clube de preferencia, salario e cidade de origem de varias pessoas
Saidas: número de torcedores por clube, media salarial dos torcedores de cada
time, numero de pessoas nascidas na capital que não torcem por nenhum dos dois
primeiros clubes, e número de pessoas entrevistadas.
*/
#include <stdio.h>
#include <ctype.h> // para o toupper
int main()
{
//Entradas
    float salario;
    int clube,cidade;
//Saidas
    int NumGremio, NumInter, NumOutros, NumPoaOutros, NumTotal;
    float TotSalGremio, TotSalInter;
    char resposta;
//Inicializa variaveis de acumulacao
    NumGremio = 0;
    NumInter = 0;
    NumOutros = 0;
    NumPoaOutros = 0;
    TotSalGremio = 0;
    TotSalInter = 0;
// Leitura dos dados das pessoas entrevistadas
    do
    {
        printf("Clube (1-Gremio; 2-Internacional; 3-Outros): ");
        scanf("%d", &clube);
        printf("Salario : ");
        scanf("%f", &salario);
        printf("Cidade : (1-Porto Alegre; 2-Outras) ");
        scanf("%d", &cidade);
        switch (clube)  // Realiza a acumulacao das variáveis
        {
        case 1 :
            NumGremio += 1;
            TotSalGremio += salario;
            break;
        case 2 :
            NumInter += 1;
            TotSalInter += salario;
            break;
        case 3 :
            NumOutros += 1;
            if (cidade == 1)
                NumPoaOutros += 1;
            break;
        default:
            printf("Clube informado invalido!");
        }
        do  // verifica se usuario quer entrar mais dados
        {
            printf("Entrar outro dado? (S/N) ");
            scanf(" %c", &resposta);
            resposta = toupper (resposta);
        }
        while (resposta != 'S' && resposta != 'N');
    }
    while (resposta == 'S');
//Acumula total de entrevistados
    NumTotal = NumGremio + NumInter + NumOutros;
//Saidas
    printf("\n\n-------------------------");
    printf("Resumo dos dados\n");
    printf("-------------------------\n\n");
    printf("Torcedores:\n");
    printf ("Gremio: %d \n",NumGremio) ;
    printf ("Inter: %d \n", NumInter ) ;
    printf ("Outros: %d \n",NumOutros ) ;
    printf("\nMedia Salarial:\n");
    printf ("Gremio: R$%4.2f \n",TotSalGremio / NumGremio);
    printf ("Inter: R$%4.2f \n", TotSalInter / NumInter);
    printf ("\nPortoalegrenses que nao torcem para inter ou gremio: %d\n", NumPoaOutros);
            printf ("Numero total de entrevistados: %d\n\n", NumTotal);
            return 0;
}
