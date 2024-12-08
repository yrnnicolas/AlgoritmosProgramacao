
/* Nicolas Fagundes Mendonça, 13/10/2023
Titulo: Programa que soma e faz o calculo do produto e calcula sua idade com base do ano de 2023.
Entrada: Valores Inteiros via teclado
Saida: Soma, Produto e idade */

#include <stdio.h>

int main(void)
{
 int val1, val2, val3; //Declaração da variáveis de entrada
 int soma; //Declaração da variável com o resultado
 int produto;



 printf("Valor do primeiro termo da soma:\n");
 scanf("%d", &val1);

 printf("Valor do segundo termo da soma:\n");
 scanf("%d", &val2);

 printf("Valor do terceiro termo da soma:\n");
 scanf("%d", &val3);

 soma = val1 + val2 + val3;
 printf("Resultado da soma: %d",soma);

 produto = val1 * val2 * val3;
 printf("\nResultado do produto: %d\n",produto);

 int anoNascimento;
 int anoAtual = 2023;
 int idade;

 printf("\nDigite o ano de seu Nascimento\n");
 scanf("%d", &anoNascimento);

 idade = anoAtual - anoNascimento;
 printf("\nVoce tem: %d", idade);
 printf (" anos");

 return 0;
}
