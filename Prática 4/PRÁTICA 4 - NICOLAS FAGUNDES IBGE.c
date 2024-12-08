#include <stdio.h>
#include <ctype.h>

/*NICOLAS FAGUNDES MENDONCA
1. Leia inicialmente o número total de inscritos;
2. Leia, em seguida num laço, para cada inscrito o gênero ('m' para masculino e 'f' para
feminino) e a idade. Determine e imprima ao final da entrada de dados:
• a porcentagem de inscritos do gênero masculino
• a idade média de todos inscritos
*/



int main(void)
{
    int num_inscritos, idade;
    float idade_media, porcentagem;
    char genero;
    int contador;
    int quantMasc = 0, quantFem = 0, soma_media = 0;

    //ENTRADA DE NUMERO TOTAL DE INSCRITOS

    printf("Entre com o numero total de inscritos: ");
    scanf("%d", &num_inscritos);


    //GERA A LISTA DO LAÇO DE REPETICAO
    for (contador = num_inscritos; contador >= 1; contador--)
    {
        //INFORMA O GENERO
        printf("\n----------------- %d ---------------------\n", contador);
        printf("Entre com o genero(m/f) do candidato numero:%d\n", contador);
        printf("Genero: ");
        scanf(" %c", &genero);

        //VERIFICA SE UTILIZA AS TECLAS PRE-DEFINIDAS
        if (genero != 'm' && genero != 'f')
        {
            printf("Erro: O genero informado nao e valido. Por favor, use 'm' para masculino ou 'f' para feminino.\n");
            continue; // PULA PARA O PROXIMO CANDIDATO
        }


        //INFORMA A IDADE
        printf("Entre a idade do candidato numero: %d\n", contador);
        printf("Idade: ");
        scanf("%d", &idade);
        printf("------------------------------------------\n\n");

        //PEGA AS IDADES
        soma_media += idade;


        // ADICIONA +1 CASO FOR M
        if (genero == 'm')
            quantMasc++;
        // COLOQUEI +1 CASO FOR F, POREM NAO FAREMOS A PORCENTAGEM DE MULHERES
        else if (genero == 'f')
            quantFem++;
    }
    //CALCULA A PORCENTAGEM MASCULINA EM HOMENS DIVIDIDO PELO NUMERO DE INSCRITOS = 100
    porcentagem = (float)quantMasc / num_inscritos * 100;


    //CALCULA A MEDIA DE INSCRITOS, PEGANDO A SOMA ACIMA DAS IDADES DIVIDINDO PELO NUMERO DE INSCRITOS INFORMADO NO INICIO DO CODIGO
    idade_media = (float)soma_media / num_inscritos;


    //SAIDAS DA PORCENTAGEM DE HOMENS & IDADE MEDIA DO TOTAL DE INSCRITOS.
    printf("A porcentagem total de Homens e: %.2f\n", porcentagem);
    printf("A Idade media dos inscritos e: %.2f", idade_media);

    return 0;
}
