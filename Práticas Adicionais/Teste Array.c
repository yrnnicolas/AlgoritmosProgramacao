#include<stdio.h>
#define TAM 3

int main (void){

//ENTRADA DOIS ARRANJOS
//UM ARRANJO COM NUMEROS IMPARES & OUTRO COM NUMEROS PARES
int par[TAM],impar[TAM];
int saida[TAM+TAM],i;

printf("Entre com 10 valores Pares:\n");
for(i=0;i<TAM;i++)
    scanf("%d", &par[i]);

printf("Entre com 10 valores Impares:\n");
for(i=0;i<TAM;i++)
    scanf("%d", &impar[i]);

for(i=0;i<TAM+TAM;i=i+2){
    saida[i] = impar[i/2];
    saida[i+2] = par[i/2];
}

for(i=0;i<TAM+TAM;i++)
    printf("%3d", saida[i]);

return 0;
}
