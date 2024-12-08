#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){

int matriz;
int MINIMAX = 31;
int indice=0;
int maior=0;
int j=0; //COLUNHA
int i=0; //LINHA
int k;
int m[9][9];
srand(time(NULL));
//int r = min + (rand() % (max - min + 1));

printf("Entre com a dimensao da Matriz: ");

do{
    scanf ("%d", &matriz);
    if ((matriz <3) || (matriz>9)){
        printf("Valor Informado incorreto: Entre com Outro Valor: \n");
    }
}while((matriz <3) || (matriz>9));

for(i=0;i<matriz;i++){
    for(j=0;j<matriz;j++){
        m[i][j] = 1 + (rand() % (30 - 1 + 1));
        printf("%d ", m[i][j]);
        if (maior<m[i][j]){
            maior = m[i][j];
            indice = i;
        }
    }
    printf("\n");
}

for(k=0;k<matriz;k++){
    if (MINIMAX>m[indice][k]){
        MINIMAX=m[indice][k];
    }
}
printf("O menor Elemento e:\n%d", MINIMAX);

return 0;
}
