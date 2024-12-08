#include <stdio.h>
#include <string.h>

void inverterStringRecursivo(char str[], int inicio, int fim) {
    if (inicio < fim) {
        // Troca os caracteres nos índices inicio e fim
        char temp = str[inicio];
        str[inicio] = str[fim];
        str[fim] = temp;

        // Chamada recursiva para os caracteres internos
        inverterStringRecursivo(str, inicio + 1, fim - 1);
    }
}

int maior_valor(int v[], int n) {
    // Caso base: se há apenas um elemento, retorne esse elemento
    if (n == 1) {
        return v[0];
    } else {
        // Chamada recursiva para encontrar o maior valor no restante do array
        int max_resto = maior_valor(v + 1, n - 1);

        // Compare o maior valor no restante com o primeiro elemento e retorne o maior
        return (v[0] > max_resto) ? v[0] : max_resto;
    }
}

int main() {
    char inputString[100];
    int vetor[10];

    // Parte 1: Inverter uma string
    printf("Entre com uma string: ");
    scanf("%s", inputString);

    int length = strlen(inputString);
    inverterStringRecursivo(inputString, 0, length - 1);
    printf("String invertida: %s\n", inputString);

    // Parte 2: Encontrar o maior valor em um array de inteiros
    printf("Entre com os 10 elementos: ");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &vetor[i]);
    }

    int maior = maior_valor(vetor, 10);
    printf("O maior elemento eh %d\n", maior);

    return 0;
}
