// Marcelo Walter - Jan 2024
// Programa exemplo arq binarios - Aula 24
// Cadastro atletas
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct{
    char nome[40];
    float altura;
    int idade;
}ATLETA;

/*
 *
 */
void escreve_arq_atletas(FILE *fp){
    ATLETA a;
    
    printf("Entre com o nome do atleta: ");
    scanf("%s", a.nome);
    printf("Entre com a altura do atleta: ");
    scanf("%f", &a.altura);
    printf("Entre com a idade do atleta: ");
    scanf("%d", &a.idade);
    if (fwrite(&a, sizeof(ATLETA),1,fp)!= 1)
        printf("Erro no escrita!\n");
}
/*
 *
 */
int menu(void){
    int op;
    
    printf("Entre com a sua opcao:\n");
    printf("1 - Escreve arquivo atletas\n");
    printf("2 - Lista arquivo atletas\n");
    printf("3 - Imprime altura de atleta\n");
    printf("4 - Insere novo atleta no final\n");
    printf("5 - Sair\n");
    scanf("%d", &op);
    return op;
}
/*
 *
 */
void lista_arquivo(FILE *fp){
    ATLETA a;
    
    rewind(fp);
    while(!feof(fp)){
        if (fread(&a, sizeof(ATLETA),1,fp)==1){
            printf("Nome: %s\n", a.nome);
            printf("Altura: %.2f\n", a.altura);
            printf("Idade: %d\n", a.idade);
        }
    }
    
}

/*
 *
 */
void imprime_altura(FILE *fp){
    char nome[40];
    int achei=0;
    ATLETA a;
    
    rewind(fp);
    printf("Entre com o nome do atleta: ");
    scanf("%s", nome);
    while(!feof(fp)){
        if (fread(&a, sizeof(ATLETA),1,fp)==1){
            if (strcmp(nome, a.nome)==0){
                printf("Altura de %s eh %f\n", a.nome, a.altura);
                achei=1;
            }
        }
    }
    if (!achei)
        printf("Atleta nao encontrado!\n");
        
}

/*
 *
 */
int main(void){
    
    FILE *parq;
    char resp;
    int cont=0,op,sair=0;
    
    
    parq=fopen("/Users/marcelow/atletas.bin", "rb+");
    if (parq != NULL){
        do{
            op=menu();
            switch(op){
                case 1: do{
                            escreve_arq_atletas(parq);
                            cont++;
                            printf("Deseja cadastrar mais um (S/N)? ");
                            scanf(" %c", &resp);
                        }while(resp!='N');
                        printf("%d atletas cadastrados!\n", cont);
                    break;
                case 2: printf("Entrou no case 2\n");
                               lista_arquivo(parq);
                               break;
                case 3: imprime_altura(parq);
                    break;
                case 4: escreve_arq_atletas(parq);
                        break;
                case 5: sair=1;
                    break;
                default: printf("Opcao invalida!\n");
            }
        }while(!sair);
    }else
        printf("Erro na abertura p escrita!\n");
    
}
