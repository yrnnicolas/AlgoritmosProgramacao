#include <stdio.h>

/*
NICOLAS FAGUNDES MENDONCA - 06/11/2023

Escreva um programa em C que lê do usuário o número de termos que o usuário deseja aproximar PI
e imprime na tela o valor de PI calculado de acordo com a fórmula acima e o número de termos
definido pelo usuário. O número mínimo de termos é 5 (caso seja informado menos do que 5
termos, encerre o programa com mensagem de erro!). Os valores abaixo servem para você avaliar
seu programa. Observe como a aproximação para π melhora com o aumento do número de termos.
*/

int main(void){
//DEFININDO AS VARIAVEIS
int num_termos;
double pi_aproximado = 0.0;

//ENTRADA
printf("Entre com o numero de termos para calculo de PI: ");
scanf("%d", &num_termos);

//MINIMO DE 5 TERMOS, SE NAO ERRO
if (num_termos < 5){
    printf("Numero de termos invalido! entre com o minimo de 5 termos");
return 0;
}

 // CALCULA A APROXIMACAO DE PI USANDO A SERIE DE LEIBNIZ
    for (int i = 0; i < num_termos; i++) {
        if (i % 2 == 0) {
            pi_aproximado += 1.0 / (2 * i + 1);
        } else {
            pi_aproximado -= 1.0 / (2 * i + 1);
        }
    }

    pi_aproximado *= 4;

    // IMPRIME O VALOR DE PI
    printf("\nValor de PI com %d termos: %.6f\n", num_termos, pi_aproximado);

return 0;
}
