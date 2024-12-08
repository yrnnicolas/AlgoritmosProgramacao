#include<stdio.h>
#include<string.h>
#define MAXLIDOS 10

int main(void){

float valor;
float media;
float mediaMenor;
float mediaMaior;
float vetor[MAXLIDOS];
int i;
int j=0;
int k=0;
float soma;

printf("Entre os Valores: ");

do{
scanf("%f", &valor);
if(valor>=0 && i<MAXLIDOS)
    (vetor[j++] = valor);
}while(j < MAXLIDOS && valor>=0);

for(k=0;k<i;k++){
soma += vetor[k];
}
media = soma/j;

printf("A Media e: %f", media);




return 0;
}
