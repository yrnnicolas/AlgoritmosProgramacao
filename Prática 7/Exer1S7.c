#include<stdio.h>
#include<string.h>
#define COMPRIMENTO 60

int main(void){

char string[COMPRIMENTO+1];
char stringSem[COMPRIMENTO];
int qtdVogais = 0;
int i=0;
int j=0;

puts("Entre com uma string: ");
if(fgets(string, COMPRIMENTO, stdin) != NULL){
//verifica se conseguiu ler
// acrescenta o finalizador de string
string[strlen(string)-1] = '\0';
printf("Tamanho da string %d\n", strlen(string));
}else printf("Problema com o fgets!\n");

for(i=0; i<strlen(string);i++){
  if((string[i]=='a')||
    (string[i]=='i')||
    (string[i]=='e')||
    (string[i]=='o')||
    (string[i]=='u')||
    (string[i]=='A')||
    (string[i]=='E')||
    (string[i]=='I')||
    (string[i]=='O')||
    (string[i]=='U'))
		{
		qtdVogais=qtdVogais+1;
		}
}

/*for(i=0;i<strlen(string);i++){
    if(string[i]==' ')continue;
        stringSem[j] = string[i];
        j++;
}*/

for(i=0;i<strlen(string);i++){
    if(string[i]!=' '){ //Se for diferente de Espaço em branco copia.
        stringSem[j] = string[i];
        j++;
    }
}
stringSem[j]='\0';

printf("Numero de Vogais: %d\n",qtdVogais);
printf("Nome sem Espacos: %s",stringSem);


return 0;
}
