#include <stdio.h>

#define MAX_CARROS 3

typedef struct carro{
    int cod;
    char modelo[45];
    char marca[45];
    float preco;
    int ano;
}CARRO;

//===============================================================//
// Imprime menu na tela, faz valida��o e retorna a op��o desejada
int menu(void)
{
    int opcao;
    printf("\n1 - Cadastro de carro\n");
    printf("2 - Consulta de carro\n");
    printf("3 - Preco medio dos carros\n");
    printf("4 - Imprime estoque revenda\n");
    printf("5 - Fim\n");
    printf("\nEntre com a Opcao: ");
    scanf("%d", &opcao);

    while (opcao < 1 || opcao > 5)
    {
        printf("Opcao invalida. Tente novamente: ");
        scanf("%d", &opcao);
    }

    return opcao;
}

//===============================================================//
// Le informa��es e cadastra um carro c recebido por refer�ncia
void cadastraCarro(CARRO *c){
    printf("\nEntre com o Codigo: ");
    scanf("%d",&c->cod);
    fflush(stdin);

    printf("\nEntre com a Marca: ");
    fgets(c->marca,44,stdin);
    c->marca[strlen(c->marca)-1]='\0';
    fflush(stdin);

    printf("\nEntre com o Modelo: ");
    fgets(c->modelo,44,stdin);
    c->modelo[strlen(c->modelo)-1]='\0';
    fflush(stdin);

    printf("\nEntre com o Ano: ");
    scanf("%d",&c->ano);

    printf("\nEntre com o Valor: ");
    scanf("%f",&c->preco);
}


//===============================================================//
// imprime as informa��es de um determinado carro c na tela na op��o consulta de
// carro. Esta fun��o dever� ser usada tamb�m para a impress�o de toda o estoque
// da revenda
void print_carro(CARRO c){
    printf("\nCodigo: %d\n", c.cod);
    printf("Marca: %s\n", c.marca);
    printf("Modelo: %s\n", c.modelo);
    printf("Ano: %d\n", c.ano);
    printf("Preco: %.2f\n", c.preco);
}


//===============================================================//
// calcula o preco m�dio de todos os carros cadastrados. A vari�vel ncarros � o n�mero atual de carros da revenda
float calcMediaPreco(CARRO carros[], int ncarros){
    int i;
    if (ncarros == 0){
        printf("\nNenhum Carro Encontrado.\n");
        return 0;
    }

    float somaPrecos = 0;

    for(i=0; i<ncarros; i++){
        somaPrecos += carros[i].preco;
    }
    return somaPrecos / ncarros;

}


//===============================================================//
// Procura um carro com o c�digo fornecido entre todos os cadastrados.
//Caso n�o exista o carro, retorna -1 no campo cod do carro retornado.
//A vari�vel ncarros � o n�mero atual de carros da revenda
CARRO procuraCarro(CARRO carros[], int ncarros, int cod){

    for (int i = 0; i < ncarros; i++) {
        if (carros[i].cod == cod) {
            return carros[i];
        }
    }

}


//===============================================================//
int main (void){
    CARRO revenda[3];
    int ncarros = 0;

    while (1)
    {
        int opcao = menu();

        switch (opcao)
        {
        case 1:
            if (ncarros < 3)
            {
                cadastraCarro(&revenda[ncarros]);
                ncarros++;
                printf("\nCarro cadastrado com sucesso!\n");
            }
            else
            {
                printf("Numero maximo de carros atingido.\n");
            }
            break;

        case 2:
            if (ncarros > 0)
            {
                int codigo;
                printf("Digite o codigo do carro: ");
                scanf("%d", &codigo);

                CARRO carroConsulta = procuraCarro(revenda, ncarros, codigo);
                if (carroConsulta.cod != -1)
                {
                    printf("\nInformacoes do Carro:\n");
                    print_carro(carroConsulta);
                }
                else
                {
                    printf("\nCarro nao encontrado.\n");
                }
            }
            else
            {
                printf("Nao ha carros cadastrados.\n");
            }
            break;

        case 3:
            if (ncarros > 0)
            {
                float media = calcMediaPreco(revenda, ncarros);
                printf("Preco medio dos carros: %.2f\n", media);
            }
            else
            {
                printf("Nao ha carros cadastrados.\n");
            }
            break;

        case 4:
            if (ncarros > 0)
            {
                printf("\nEstoque da revenda:\n");
                for (int i = 0; i < ncarros; i++)
                {
                    print_carro(revenda[i]);
                }
            }
            else
            {
                printf("Nao ha carros cadastrados.\n");
            }
            break;

        case 5:
            printf("Encerrando o programa.\n");
            return 0;
        }
    }

    return 0;
}
