#include<stdio.h>

int main(void){
int valor, dezenas, unidades;

printf("Entre com o Valor: ");
scanf(" %d", &valor);
if (valor< 20 || valor>39){
printf("Valor Fora do Intervalo");
return 1;
}

dezenas = valor / 10;
unidades = valor % 10;

int soma = dezenas + unidades;
printf("Soma dos Algarismos: %d\n", soma);

printf("Por EXTENSO: ");
switch(dezenas){
case 2: printf("Vinte");
break;
case 3: printf("Trinta");
break;
default:
    break;
}

if (dezenas != 0 && unidades !=0){
    printf(" e ");
}

switch (unidades){
case 1:
    printf("Um");
    break;
    case 2:
    printf("Dois");
    break;
    case 3:
    printf("Tres");
    break;
    case 4:
    printf("Quatro");
    break;
    case 5:
    printf("Cinco");
    break;
    case 6:
    printf("Seis");
    break;
    case 7:
    printf("Sete");
    break;
    case 8:
    printf("Oito");
    break;
    case 9:
    printf("Nove");
    break;
    default:
        break;
}
printf("\n");

return 0;
}
