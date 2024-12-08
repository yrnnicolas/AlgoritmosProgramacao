#include <stdio.h>
#include<locale.h>

/* Nicolas Fagundes Mendonça -- CARTÃO: 00344411
PRÁTICA 10 -- PONTEIROS;

================================================
Elaborar um programa que leia três inteiros correspondentes ao dia, mês e ano da data de fabricação
do produto.

-- Calcule e imprime a data de validade conforme os exemplos abaixo.\

- Considerar o mês de fevereiro com 28 dias, independente da condição de ser ano bissexto ou não.
- Lembre-se que Janeiro, Março, Maio, Julho, Agosto, Outubro e Dezembro tem 31 dias,
enquanto,
- Abril, Junho, Setembro e Novembro tem 30 dias.

Validar as datas:
dias no intervalo [1-31],
meses no intervalo [1- 12]
e o ano deve ser maior que 2021.
================================================
*/


// Função para ler e validar uma data
void data_valida(int *d, int *m, int *a) {

    do {
        printf("Entre com o dia: ");
        scanf("%d", *d);
        if (*d < 1 || *d > 31){
            printf("Dia Inválido!\n");
            continue;
        }

//======================================//

        printf("Entre com o mês: ");
        scanf("%d", m);

        //Valida Mês
        if (*m < 1 || *m > 12) {
            printf("Mes invalido!\n");
            continue;
        }
        switch(*m){
            //Até 31 Dias!
        case 1: // Janeiro
        case 3: // Março
        case 5: // Maio
        case 7: // Julho
        case 8: // Agosto
        case 10: // Outubro
        case 12: // Dezembro
            if(*d < 1 || *d>31){
                printf("Número de Dias Inválido!\n");
                continue;
            }
            break;

            //Até 30 Dias!
        case 4: // Abril
        case 6: // Junho
        case 9: // Setembro
        case 11: // Novembro
            if(*d < 1 || *d > 30){
                printf("Número de Dias inválido para o Mês!, o Mês referente possui Somente 30 Dias!\n");
                continue;
            }
            break;

            //Até 28 Dias!
        case 2: //Fevereiro
            if(*d < 1 || *d > 28){
                printf("Número de Dias Inválido!, Fevereiro possui no Máximo 28 Dias!\n");
                continue;
            }
            break;

            //Default
        default:
            printf("Mês Inválido!\n");
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


// Função para ler um caractere 'S' ou 'N'
char le_s_n() {
    char resposta;
    do{
        printf("\Deseja continuar (S ou N)?: ");
        scanf(" %c", &resposta);

        resposta = toupper(resposta); //Transforma em Maiúsculo

        if(resposta != 'S' && resposta != 'N' )
            printf("Resposta invalida. ");
    } while (resposta != 'S' && resposta != 'N' );

    return resposta;
}


// Função Principal;
int main() {
    setlocale( LC_ALL, "Portuguese" );
    int dia, mes, ano;
    char continuar;

    do {
        printf("\nEntre com a data de fabricação:\n");

        // Chama a função para ler e validar a data
        data_valida(&dia, &mes, &ano);

        // Calcula a data de validade (15 dias após a data de fabricação)

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
        printf("Válido ate %d/%d/%d\n", dia, mes, ano);

        // Pergunta se o usuário deseja continuar
        continuar = le_s_n();

    } while (continuar == 'S');

    return 0;
}




