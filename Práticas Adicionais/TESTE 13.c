#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MIN 1
#define MAX 3
#define TAM 30
#define NNOTAS 5
#define NALUNOS 3
#define TAM_TURMA 10
#define TAM_NOME 30
int main(void){

//COMANDO RAND -- NUMEROS ALEATÓRIOS! <BIBLIOTECA stdlib.h
//USAR A SEMENTE; srand(time(NULL))
srand(time(NULL));
/*int indice;
for(indice=0;indice<3;indice++){
    printf("%d ",rand()%(MAX - MIN +1));
}
*/
/*
//JOGO DE PEDRA PAPEL OU TESOURA COM A MAQUINA MALUCA
int resposta;
char continuar;
do{
   printf("\nEntre com Alguma Jogada:\n");
   printf("1 - Pedra\n");
   printf("2 - Papel\n");
   printf("3 - Tesoura\n");

//OBTEM A ESCOLHA DO USUARIO
printf("Sua Jogada: ");
scanf("%d",&resposta);

//ESCOLHA DA MAQUINA
int maquina = rand()%(MAX - MIN +1);

//EMPATE
if(resposta == maquina){
    printf("Empate\n");
}else if((resposta ==1 && maquina== 3)||
         (resposta ==2 && maquina== 1)||
         (resposta ==3 && maquina== 2)){
         printf("O Humano Venceu!\n");
         } else{
             printf("A Maquina Venceu!\n");
             }

         printf("Voce deseja continuar? (N/n para sair): ");
         scanf(" %c", &continuar);


}while(continuar !='N'&& continuar != 'n');
*/

//ARRANJOS DE DUAS DIMENSÕES
/*
float notas[NALUNOS][NNOTAS];
int nmr=0;
int aluno,nota;
float soma, media;

for(aluno=0;aluno<NALUNOS;aluno++){
    printf("Entre com as %d notas do Aluno: %d.| ",NNOTAS, nmr=nmr+1);
    for(nota=0;nota<NNOTAS;nota++)
        scanf("%f", &notas[aluno][nota]);
}

//Calcula media
soma = 0;
for(aluno = 0; aluno<NALUNOS;aluno=aluno+1)
    soma = soma + notas[aluno][0];
media = soma / NALUNOS;

printf("Media da primeira nota: %f\n", media);
//
*/

//VER O MAIOR ELEMENTO DE CADA COLUNA

/*
int coluna, maior,linha;
for(coluna= 0;coluna<TCOLUNA;coluna++){
    maior = matriz[0][coluna]; // inicia o PRIMEIRO elemento de cada coluna. pois coluna++

for(linha = 1; linha<TLINHA; linha++)
if (maior < matriz[linha][coluna])
    maior = matriz[linha][coluna];

    printf("Maior da Coluna %d e o %d", coluna, maior);
}
*/

/*Ler os nomes dos alunos de uma turma, suas
notas finais (valor real entre 0 e 10), e frequência total (inteiro
entre 0 e 45). Depois, imprimir os nomes e o conceito final, de
acordo com a seguinte conversão:*/

char nome[TAM_TURMA][TAM_NOME];
float nota[TAM_TURMA];
int freq[TAM_TURMA];
char tela[TAM_TURMA+10];
int tam,i;
printf("Entre com numero de alunos da Turma: ");
scanf("%d", &tam);
getchar();

//leitura dos nomes notas e frequencia
for(i=0;i<tam;i++){
    printf("Entre com o nome do aluno %d ", i=i+1);
    fgets(nome[i],TAM_NOME,stdin);
    nome[i][strlen(nome[i])-1] = '\0';

    printf("Entre com a nota do aluno %d: ", i=i+1);
    scanf("%f", &nota[i]);

    printf("Entre com a Frequencia do Aluno %d: ", i=i+1);
    scanf("%f",&freq[i]);
    getchar();
}
printf("\n");

for(i<0; i<tam; i=i+1){
    strcpy(tela,nome[i]);
    if (freq[i]<.75*45)
        strcat(tela, ": conceito FF");
    else
        if (nota[i]>8.4)
        strcat(tela, ": conceito A");
    else
        if(nota[i]>7.4)
        strcat(tela, ": conceito B");
    else
        if (nota[i]>5.9)
    strcat(tela, ": conceito C");
    else
        (tela, ": conceito D");
    puts(tela);

}

return 0;
}
