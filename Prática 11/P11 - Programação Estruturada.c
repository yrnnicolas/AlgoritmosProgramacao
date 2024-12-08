#include <stdio.h>
#include <math.h>

//Entrada:
void le_larg_comp_sala(int *largura, int *comprimento){

    do{
        printf("Digite a Largura da Sala: ");
        scanf("%d", largura);

    }
    while(*largura < 1 || *largura > 100);

    do{
        printf("Digite o Comprimento da Sala: ");
        scanf("%d", comprimento);

    }
    while(*comprimento < 1 || *comprimento > 100);
}

//Saída;
void calcula_lajotas(int largura, int comprimento, int *tipo1, int *tipo2){

    *tipo1 = largura*comprimento + ((largura - 1)* (comprimento - 1));

    *tipo2 = ((largura - 1)* 2) + ((comprimento - 1)*2) ;

}


int main(void){

int largura;
int comprimento;
int tipo1;
int tipo2;

 le_larg_comp_sala(&largura,&comprimento);
 calcula_lajotas(largura, comprimento, &tipo1, &tipo2);

 printf("Quantidade de Lajotas do Tipo 1: %d\n", tipo1);

 printf("Quantidade de Lajotas do Tipo 2: %d\n", tipo2);


return 0;
}
