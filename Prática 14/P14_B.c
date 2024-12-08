#include <stdio.h>
#include <string.h>

#define MAX_PARTIDAS 5

typedef struct str_partida {
    char nome1[30], nome2[30];
    int set1, set2;
    int minutos;
} TIPO_PARTIDA;

int lerPartida(TIPO_PARTIDA partidas[], const char *arquivo) {
    int numPartidas = 0;
    FILE *arq = fopen(arquivo, "r");

    if (!arq) {
        perror("Erro na abertura no Ler Partidas\n");
        return -1; // Retorna um valor que indica erro
    }

    while (!feof(arq) && numPartidas < MAX_PARTIDAS) {
        if (fscanf(arq, "%s %d %d %s %d", partidas[numPartidas].nome1, &partidas[numPartidas].set1,
                   &partidas[numPartidas].set2, partidas[numPartidas].nome2, &partidas[numPartidas].minutos) == 5) {
            numPartidas++;
        }
    }

    fclose(arq);
    return numPartidas; // Retorna o número de partidas lidas com sucesso
}

void escreverSaida(const TIPO_PARTIDA partida[], int numPartidas) {
    FILE *saida = fopen("saida.txt", "w");

    if (!saida) {
        printf("Erro no Escrever saida\n");
        return;
    }

    for (int i = 0; i < numPartidas; i++) {
        fprintf(saida, "Partida %d. Vencedor: %s. Tempo de jogo: %02dh:%02dmin\n", i + 1,
                (partida[i].set1 > partida[i].set2) ? partida[i].nome1 : partida[i].nome2,
                partida[i].minutos / 60, partida[i].minutos % 60);
    }

    fclose(saida);
}

int main() {
    TIPO_PARTIDA partidas[MAX_PARTIDAS];
    int numPartidas = lerPartida(partidas, "tenis.txt");

    if (numPartidas > 0) {
        escreverSaida(partidas, numPartidas);
        printf("Processamento concluido. Resultado disponivel no saida.txt\n");
    } else {
        printf("Nenhuma partida encontrada\n");
    }


    return 0;
}
