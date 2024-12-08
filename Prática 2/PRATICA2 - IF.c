#include<stdio.h>
#include<math.h>

int main(void){
int total;
int segundos;
int dia;
int hora;
int min;

printf("Entre com o total de segundos: ");
scanf("%d", &total);

dia = total / (24*3600);
total %= (24*3600);
hora = total /3600;
total %=3600;
min = total / 60;
segundos = total %60;


 printf("%d Dia(s) %d hora(s) %d min(s) %d sec(s)\n", dia, hora, min, segundos);
return 0;
}
