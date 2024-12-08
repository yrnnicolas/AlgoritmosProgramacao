#include <stdio.h>
#include<locale.h>

/* Nicolas Fagundes Mendon�a -- CART�O: 00344411
PR�TICA 10 -- PONTEIROS;

================================================
Elaborar um programa que leia tr�s inteiros correspondentes ao dia, m�s e ano da data de fabrica��o
do produto.

-- Calcule e imprime a data de validade conforme os exemplos abaixo.\

- Considerar o m�s de fevereiro com 28 dias, independente da condi��o de ser ano bissexto ou n�o.
- Lembre-se que Janeiro, Mar�o, Maio, Julho, Agosto, Outubro e Dezembro tem 31 dias,
enquanto,
- Abril, Junho, Setembro e Novembro tem 30 dias.

Validar as datas:
dias no intervalo [1-31],
meses no intervalo [1- 12]
e o ano deve ser maior que 2021.
================================================
*/


// Fun��o para ler e validar uma data
void data_valida(int *d, int *m, int *a) {

    do {
        printf("Entre com o dia: ");
        scanf("%d", *d);
        if (*d < 1 || *d > 31){
            printf("Dia Inv�lido!\n");
            continue;
        }

//======================================//

        printf("Entre com o m�s: ");
        scanf("%d", m);

        //Valida M�s
        if (*m < 1 || *m > 12) {
            printf("Mes invalido!\n");
            continue;
        }
        switch(*m){
            //At� 31 Dias!
        case 1: // Janeiro
        case 3: // Mar�o
        case 5: // Maio
        case 7: // Julho
        case 8: // Agosto
        case 10: // Outubro
        case 12: // Dezembro
            if(*d < 1 || *d>31){
                printf("N�mero de Dias Inv�lido!\n");
                continue;
            }
            break;

            //At� 30 Dias!
        case 4: // Abril
        case 6: // Junho
        case 9: // Setembro
        case 11: // Novembro
            if(*d < 1 || *d > 30){
                printf("N�mero de Dias inv�lido para o M�s!, o M�s referente possui Somente 30 Dias!\n");
                continue;
            }
            break;

            //At� 28 Dias!
        case 2: //Fevereiro
            if(*d < 1 || *d > 28){
                printf("N�mero de Dias Inv�lido!, Fevereiro possui no M�ximo 28 Dias!\n");
                continue;
            }
            break;

            //Default
        default:
            printf("M�s Inv�lido!\n");
            continue;
        }

//======================================//

        printf("Entre com o ano: ");
        scanf("%d", a);

        if (*a < 2022) {
            printf("Ano invalido!\n");
            continue;
        }

        break;

    } while (1);
}


// Fun��o para ler um caractere 'S' ou 'N'
char le_s_n() {
    char resposta;
    do{
        printf("\Deseja continuar (S ou N)?: ");
        scanf(" %c", &resposta);

        resposta = toupper(resposta); //Transforma em Mai�sculo

        if(resposta != 'S' && resposta != 'N' )
            printf("Resposta invalida. ");
    } while (resposta != 'S' && resposta != 'N' );

    return resposta;
}


// Fun��o Principal;
int main() {
    setlocale( LC_ALL, "Portuguese" );
    int dia, mes, ano;
    char continuar;

    do {
        printf("\nEntre com a data de fabrica��o:\n");

        // Chama a fun��o para ler e validar a data
        data_valida(&dia, &mes, &ano);

        // Calcula a data de validade (15 dias ap�s a data de fabrica��o)

        dia += 15;
        if (mes == 2 && dia >= 28) {
        dia -= 28, mes++;
        }
        else if(dia >= 31){
        dia -=31, mes++;
        }

            if (mes >= 12) {
                mes = 1;
                ano++;
            }


        // Imprime a data de validade
        printf("V�lido ate %d/%d/%d\n", dia, mes, ano);

        // Pergunta se o usu�rio deseja continuar
        continuar = le_s_n();

    } while (continuar == 'S');

    return 0;
}




