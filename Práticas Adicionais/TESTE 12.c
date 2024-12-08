#include<stdio.h>
#include<string.h>
#define TAM 30

int main(void){
char nome[TAM+1];
char destino[TAM+1];
/*
puts("Digite uma string: ");
if(fgets(nome, TAM+1, stdin)!=NULL){
nome[strlen(nome)-1]='\0';
puts(nome);
printf("Tamanho da String: %d\n",strlen(nome));
}else printf("Problema com o fgets\n");
*/


/*
printf("Digite uma string: ");
fgets(nome,TAM,stdin);
*/

/*
//FUNÇÃO STRCPY = Copia de Origem para Destino:


printf("Digite o Nome: ");
fgets(nome,TAM+1,stdin);

strcpy(destino,nome);
printf("\nNome Copiado: %s", destino);
*/

//FUNÇÃO STRCAT -- CONCATENA, JUNTA DUAS STRINGS
/*
printf("Forneca algo para Concatenar! \n");
fgets(nome,TAM+1,stdin);

strcat(destino, nome);
printf("\nVoce concatenou:%s\n", destino);
*/

//FUNCAO STRLEN -- retorna o tamanho do string sem contar o '\0'
/*
int tam; //PARA ARMAZENAR A QUANTIDADE?
printf("Digite o Tamanho da String que queira Contar: ");
fgets(nome,TAM+1,stdin);
tam = strlen(nome);
printf("\nO String %s tem comprimento de: %d",nome, tam);
*/


//FUNCAO STRCMP -- Compara os caracters de 2 strings diferentes até encontrar alguma diferenca
/*
char nome2[TAM+1];
int i;

for (i=1; i<3; i++){
    printf("Forneca um Texto: ");
    fgets(nome, TAM+1, stdin);

    printf("Forneca um segundo Texto: ");
    fgets(nome2,TAM+1,stdin);

    printf("Resultado da Comparacao de %s com %s: %d\n\n",nome,nome2, strcmp(nome,nome2));
}
*/


return 0;
}
