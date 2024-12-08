#include<stdio.h>


//Exercício IF 1
int main(void){
int quantidade;
int estoque;


printf("Entre com a Quantidade de Itens em ESTOQUE: ");
scanf("%d", &estoque);

printf("\n============\n");

 printf("Entre com a quantidade a serem fornecidos: ");
 scanf("%d", &quantidade);

 estoque=estoque - quantidade;

 if(estoque <= 0)
    printf("Pedido nao possui estoque suficiente.");
    else printf("Pedido realizado com sucesso.");

return 0;
}

