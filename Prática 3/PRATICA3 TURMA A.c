#include<stdio.h>

int main(void){
char resposta1;
char resposta2;

printf("Entre com as Jogadas:  ");
scanf(" %c %c", &resposta1, &resposta2);

//Verifica as jogadas
if((resposta1 == 'r' || resposta1 == 'R') && (resposta2 == 's' || resposta2 == 'S')){
    printf("Jogador 1 Venceu, Pedra vence Tesoura");}
else if((resposta1 == 'p' || resposta1 =='P') && (resposta2 == 'r' || resposta2 == 'R')){
    printf("Jogador 1 Venceu, Papel vence Pedra");}
else if((resposta1 == 's' || resposta1 == 'S') && (resposta2 == 'p' || resposta2 == 'P')){
    printf("Jogador 1 Venceu, Tesoura corta Papel");}

else if ((resposta2 == 'r' || resposta2 == 'R') && (resposta1 == 's' || resposta1 == 'S')){
    printf("Jogador 2 Venceu, Pedra vence Tesoura");}
else if((resposta2 == 'p' || resposta2 =='P') && (resposta1 == 'r' || resposta1 == 'R')){
    printf("Jogador 2 Venceu, Papel vence Pedra");}
else if((resposta2 == 's' || resposta2 == 'S') && (resposta1 == 'p' || resposta1 == 'P')){
    printf("Jogador 2 Venceu, Tesoura corta Papel");}

else if(resposta1 == resposta2){
    printf("EMPATE!");}

else printf("Entre com um Comando Válido");



return 0;
}
