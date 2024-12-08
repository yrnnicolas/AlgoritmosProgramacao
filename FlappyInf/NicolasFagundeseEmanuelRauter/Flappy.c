//ALGORITMOS PROGRAMAÇÃO
//PROFESSOR: MARCELO WALTER
//COMPONENTES: NICOLAS FAGUNDES MENDONÇA 00344411 | EMANUEL RUSCHEL RAUTER 578247

#include <raylib.h>
#include <stdio.h>
#include <string.h>
//Definição de constantes
#define screenWidth 1200
#define screenHeight 800
#define max_obstaculos 4
#define top5 5
#define gravidade 1.5
#define fonte 70

//Definição de variáveis universais
int score_threshold ;
int gap ;
int inc_gap ;
int dif_alt_maxima ;
int inc_dif_alt_maxima ;
int vel_obstaculos ;
int inc_vel_obstaculos ;

typedef struct //Definição da estrutura do Flappy Bird
{
    char Nome[11]; //Nome do jogador, será pedido caso ele fique entre os 5 melhores placares
    Vector2 posicao; //Vetor posicional. Contém posição {x,y} do jogador
    int Pontuacao; //Pontuação, marca a pontuação do jogador
    Vector2 velocidade; //Vetor de velocidade do jogador. Contém a velocidade X e Y do jogador
    Vector2 aceleracao; //Vetor de aceleração do jogador. Contém a aceleração X e Y do jogador
    Vector2 dimensao; //Vetor do tamanho do jogador. Contém a dimensão X e Y do jogador
    float pulo; //Define a força do pulo do jogador
    Texture2D textura; //Textura do Flappy Bird
} FLAPPY;

typedef struct //Definição da estrutura dos obstáculos
{
    Vector2 cima; //Define as posições do cano de cima
    Vector2 baixo; //Define as posições do cano de baixo
    int altura; //Define a altura do cano
    int largura; //Define a largura do cano
    int velocidade; //Define a Velocidade do cano
    Texture2D textura; //Define a textura do cano
} OBSTACULO;

typedef struct //Definição da estrutura dos sons
{
    Sound flap; //Som batida de asa
    Sound hit; //Som de acertar o cano
    Sound point; //Som de pontuar
    Sound menu; //Som de erro no menu
    Sound game_over; //Som de game over
    Sound parabens; //Som de novo highscore
    Sound menu_tema; //Som do menu
    Sound ranqueado; //Som do ranking
    Sound jogo; //Som do jogo
    Sound dif; //Som da dificuldade
} SONS;

typedef struct //Definição da estrutura do Jogador
{
    char nome[11]; //Nome do Jogador
    int pontos; //Pontuação do jogador
} JOGADOR;

void setup()  //Função da criação da tela de jogo
{
    InitWindow(screenWidth, screenHeight, "Flappy.inf"); //Cria janela do jogo 1200x800 com nome de Flappy.inf
    SetTargetFPS(30); //Define a quantidade de FPS desejados
    ToggleFullscreen(); //Ativa tela cheia
    InitAudioDevice(); //Inicia o dispositivo de áudio do computador
}

void cria_flappy(FLAPPY *f) //Função de criação do FlappyBird
{
    f->posicao = (Vector2)
    {
        250, 400
    }; //Definição da Posição incial
    f->velocidade = (Vector2)
    {
        0, 0
    }; //Definição da Velocidade inicial
    f->aceleracao = (Vector2)
    {
        0, gravidade
    }; //Definição da aceleração inicial
    f->dimensao = (Vector2)
    {
        80, 72
    }; //Definição do Tamanho inicial
    f->pulo = 20; //Definição da força do pulo
    f->textura = LoadTexture("./Texturas/flappy.png"); //Carregamento da textura do Flappy
    f->Pontuacao = 0; //Definição da pontuação incial
}

void cria_primeiro_obstaculo(OBSTACULO o[max_obstaculos], int *i)  //Cria o primeiro obstáculo para depois os outros serem gerados a partir desse
{
    o[*i].baixo.x = screenWidth;//Canos de cima e de baixo começam na direita da tela
    o[*i].cima.x =screenWidth;
    o[*i].altura = GetRandomValue(0, screenHeight-gap); //Altura do cano será um número aleatório entre 0 e a altura da tela menos o gap
    o[*i].largura = 80; //Definição da largura dos canos
    o[*i].cima.y = 0; //Cano de cima sempre começa no topo da tela
    o[*i].baixo.y = o[*i].altura + gap; //Cano de baixo começa na altura do cao de cima mais o gap
    o[*i].velocidade = vel_obstaculos; //Definição da velocidade dos canos
    o[*i].textura = LoadTexture("./Texturas/obstaculo.png"); //Carregamento da textura dos canos
    *i++; // Soma 1 ao contador
}
void cria_obstaculo(OBSTACULO o[max_obstaculos], int *i)  //Função de criação de obstáculos
{
    int altura_anterior = o[*i].altura; //Salva a altura do cano anterior ao ser gerado
    int altura_menor, altura_maior; //Variáveis para criar o cano usando a diferença de altura máxima
    altura_menor = altura_anterior - dif_alt_maxima; //A menor altura possível é a subtração da altura do cano anterior com a diferença máxima de altura
    if(altura_menor < 0)  //Se a altura mínima sair da tela, defini-la como 0
    {
        altura_menor = 0;
    }
    altura_maior = altura_anterior + dif_alt_maxima; //A maior altura possível é a soma da altura do cano anterior com a diferença máxima de altura
    if(altura_maior > screenHeight - gap)  //Se a altura máxima sair da tela, defini-la como a subtração da altura da tela pelo gap
    {
        altura_maior = screenHeight - gap;
    }
    if(screenWidth - o[*i].cima.x >= 400)  //Função para o ciclo de canos, a cada 400 pixels que o úlitmo cano gerado se mover, será gerado um novo cano.
    {
        *i = (*i + 1) % max_obstaculos; // A função de resto garante a rotação correta entre os números 0, 1, 2 e 3 para numeração do array
        o[*i].baixo.x = screenWidth;//Canos de cima e de baixo começam na direita da tela
        o[*i].cima.x =screenWidth;
        o[*i].altura = GetRandomValue(altura_menor, altura_maior); //Altura do cano será um número aleatório entre a menor altura possível e a maior altura possível
        o[*i].largura = 80; //Definição da largura dos canos
        o[*i].cima.y = 0; //Cano de cima sempre começa no topo da tela
        o[*i].baixo.y = o[*i].altura + gap; //Cano de baixo começa na altura do cao de cima mais o gap
        o[*i].velocidade = vel_obstaculos; //Definição da velocidade dos canos
        o[*i].textura = LoadTexture("./Texturas/obstaculo.png"); //Carregamento da textura dos canos
    }
}

void carrega_sons(SONS *s) //Carrega os sons usados no jogo
{
    s->flap = LoadSound("./Sons/flap.mp3");
    s->hit = LoadSound("./Sons/hit.mp3");
    s->point = LoadSound("./Sons/point.mp3");
    s->game_over = LoadSound("./Sons/game_over.mp3");
    s->parabens = LoadSound("./Sons/parabens.mp3");
    s->jogo = LoadSound("./Sons/jogo.mp3");
}
void desenha_flappy(FLAPPY f)  //Função que desenha o Flappy Bird
{
    DrawTextureEx(f.textura, (Vector2)
    {
        f.posicao.x-10,f.posicao.y-10
    }, 0, 5, WHITE); //Desenho do Flappy
}

void desenha_score(FLAPPY f)  //Função que desenha a pontuação
{
    DrawText(TextFormat("Score: %08d", f.Pontuacao), 50, 10, 40, BLACK); //Desenho do score
}

void desenha_background(Texture2D fundo)  //Função que desenha o fundo
{
    DrawTextureEx(fundo, (Vector2)
    {
        0,0
    }, 0, 1.2, WHITE ); //Desenho do fundo
}

void desenha_obstaculo(OBSTACULO o[max_obstaculos])  //Função que desenha os obstáculos
{
    int i; //contador
    for(i=0; i<max_obstaculos; i++)  //loop onde todos obstáculos gerados serão desenhados
    {
        DrawTexturePro(o[i].textura, (Rectangle)
        {
            0, 0, 28, 151
        }, (Rectangle)
        {
            o[i].cima.x, o[i].cima.y, o[i].largura, o[i].altura
        }, (Vector2)
        {
            0,0
        }, 0, WHITE); //Desenho do Obstáculo superior
        DrawTexturePro(o[i].textura, (Rectangle)
        {
            0, 0, 28, 151
        }, (Rectangle)
        {
            o[i].baixo.x, o[i].baixo.y, o[i].largura, screenHeight - (o[i].altura+gap)
        }, (Vector2)
        {
            o[i].largura, screenHeight - (o[i].altura+gap)
        }, 180, WHITE); //Desenho do obstáculo inferior
    }
}

void move_flappy(FLAPPY *f, SONS som)  //Função que move o FlappyBird
{
    f->velocidade.y += f->aceleracao.y; //A velocidade vertical será igual a soma desta com a gravidade
    f->posicao.y += f->velocidade.y; //A posição vertical será igual a soma desta com a velocidade vertical
    f->Pontuacao++; //Soma-se 1 à pontuação do jogador
    if(IsKeyPressed(KEY_SPACE)) //Se Espaço for pressionado:
    {
        f->velocidade.y = -f->pulo; //A velocidade vertical será igual ao negativo do pulo
        PlaySound(som.flap); //Toca o som de bater a asa
    }
}

void move_obstaculo (OBSTACULO o[max_obstaculos])  //Função que move os obstáculos
{
    int i; //Contador
    for(i=0; i<max_obstaculos; i++)  //Loop que move todos os obstáculos criados
    {
        o[i].cima.x -= o[i].velocidade; //A posição horizontal de ambos canos serão igauis a subtração de suas posições originais pelas suas velocidades horizontais
        o[i].baixo.x -= o[i].velocidade;
    }
}

int verifica_colisao (FLAPPY f, OBSTACULO o[], int i, SONS som)  //Função que verifica colisão
{
    Rectangle player = {f.posicao.x, f.posicao.y+6, f.dimensao.x-5, f.dimensao.y-10}; //É criado um retângulo para o player e ambos canos
    Rectangle cano_cima = {o[i].cima.x, o[i].cima.y, o[i].largura, o[i].altura};
    Rectangle cano_baixo = {o[i].baixo.x, o[i].baixo.y, o[i].largura, screenHeight - (o[i].altura+gap)};
    if(CheckCollisionRecs (player, cano_cima) || CheckCollisionRecs (player, cano_baixo))  //Caso o player colida com qualquer um dos canos, o programa retorn verdadeiro
    {
        PlaySound(som.hit); //Toca o som de acertar o cano
        return 1;
    }
    else  //Senão, retorna falso
    {
        return 0;
    }
}

void aumento_dificuldade(FLAPPY f, OBSTACULO o[max_obstaculos], SONS som)  //Função que aumenta a dificuldade de acordo com a pontuação
{
    int i; //Contador
    if(gap > 100)  //Se gap for maior que 100
    {
        gap -= inc_gap; //Diminui o gap de acordo com as variáveis universais
    }
    if(vel_obstaculos < 100)  //Se a velocidade for menor que 100
    {
        vel_obstaculos += inc_vel_obstaculos; //Aumenta a velocidade de acordo com as variáveis universais
        for(i=0; i<max_obstaculos; i++)
        {
            o[i].velocidade = vel_obstaculos; //Aplica a nova velocidade a todos obstáculos
        }
    }
    if(dif_alt_maxima < 900)  //Se a diferença de altura máxima for menor que 900
    {
        dif_alt_maxima += inc_dif_alt_maxima;  //Aumenta a diferença de altura máxima de acordo com as variáveis universais
    }
    DrawText(TextFormat("Score: %08d", f.Pontuacao), 50, 10, 40, WHITE); // Score pisca branco para indicar o aumento da dificuldade
    PlaySound(som.point); //Toca o som de pontuação
}

int Dificuldade() //Função que cria o menu de dificuldade
{
    FILE *dificuldade_arq; //Declaração de variáveis
    char nome_arq[21]={NULL}, nome_comp_arq[50];
    int tecla, num_letras=0, validacao=0;
    SONS som;
    som.dif = LoadSound("./Sons/dificuldade.mp3"); //Carrega música da dificuldade
    while(!(IsKeyDown(KEY_TAB))) //Enquanto TAB não é pressionado
    {
        if(!IsSoundPlaying(som.dif)){ //Toca música da dificuldade
            PlaySound(som.dif);
        }
        while(!(IsKeyPressed(KEY_ENTER)) && !(IsKeyPressed(KEY_TAB)))  //Enquanto nem o ENTER e nem o TAB estiverem apertados, rodar o loop
        {
            tecla = GetCharPressed(); //Variável inteira recebe o valor numérico da tecla pressionada
            while(tecla>0)  //Enquanto alguma tecla estiver pressionada
            {
                if(num_letras < 20)  //Se o limite de caracteres não foi atingido
                {
                    nome_arq[num_letras] = (char)tecla; //Espaço atual da palavra é equivalente a tecla digitada
                    nome_arq[num_letras+1] = '\0'; //Próximo espaço recebe o sinal de fim de string
                    num_letras++; //Soma-se um ao contador de espaços
                }
                tecla = GetCharPressed(); //Tecla recebe o valor de outra tecla pressionada
            }
            if(IsKeyPressed(KEY_BACKSPACE))  //Se BACKSPACE for apertado
            {
                num_letras--; //Diminui o contador de espaços em um
                if(num_letras<0)  //Se ele ficar negativo
                {
                    num_letras = 0; //O fazer valer 0
                }
                nome_arq[num_letras] = '\0'; //Colocar o marcador de fim de string no espaço ocupado pelo marcador
            }
            BeginDrawing();  // Começa o desenho
            ClearBackground(LIGHTGRAY); //Limpa o background e aplica a cor LIGHTGRAY
            DrawText("<- Pressione TAB para retornar ao menu", 50, 50, 30, BLACK); //Texto de como sair
            DrawText("Insira nome do arquivo da dificuldade", 100, 200, 50, BLUE); //Texto para explicar entrada
            DrawRectangle(240, 290, 860, 120, WHITE);
            DrawText(nome_arq, 250, 300, 100, BLACK); //Texto da palavra sendo digitada
            EndDrawing(); //Fim do desenho
        }
        sprintf(nome_comp_arq, "./Dificuldade/%s", nome_arq); //Depois que se aperta ENTER, se cria uma string com o nome do arquivo dentro do camino para achá-lo
        if(!(dificuldade_arq = fopen(nome_comp_arq, "r")))  //Se o arquivo não for encontrado, piscar ele vermelho
        {
            BeginDrawing();
            DrawText(nome_arq, 250, 300, 100, RED);
            EndDrawing();
        }
        else  //Se ele for encontrado
        {
            BeginDrawing();
            DrawText(nome_arq, 250, 300, 100, GREEN); //Piscar o nome dele verde
            EndDrawing();
            fscanf(dificuldade_arq, "%d %d %d %d %d %d %d", &score_threshold, &gap, &inc_gap, &dif_alt_maxima, &inc_dif_alt_maxima, &vel_obstaculos, &inc_vel_obstaculos); //Scanear as variáveis globais
            fclose(dificuldade_arq); //Fechar o arquivo
            validacao = 1; //Validação vira 1
        }

    }
    StopSound(som.dif); //Para música da dificuldade
    return validacao; //Retorna com a validação se foi ou não escolhida uma dificuldade
}

void le_jogador(JOGADOR jogador[top5])  //Aplica conteúdo de uma bin a um array de jogadores
{
    FILE *placar; //Declaração de variável
    placar = fopen("./Ranking/top5.bin", "rb"); //Abre arquivo
    fread(jogador, sizeof(JOGADOR), 5, placar); //Lê e salva conteúdo na estrutura JOGADOR
    fclose(placar); //Fecha arquivo
}

void Ranking() //Desenha o Ranking
{
    JOGADOR ranque[top5]; //Declaração de variável
    SONS som;
    som.ranqueado = LoadSound("./Sons/ranking.mp3"); //Carrega música do rank
    le_jogador(ranque); //Aplica conteúdo do top5.bin aos jogadores
    while(!IsKeyPressed(KEY_TAB))  //Enquanto TAB não é pressionado
    {
        if(!IsSoundPlaying(som.ranqueado)){ //Toca música do rank
            PlaySound(som.ranqueado);
        }
        BeginDrawing(); //Ínicio do desenho
        ClearBackground(BLUE);
        DrawText("<- Pressione TAB para retornar ao menu", 50, 50, 30, BLACK); //Texto que explica como sair
        DrawText("Top 5 Jogadores:", 400, 100, 50, YELLOW); //Placar com o nome dos 5 melhores jogadores e seus placares
        DrawText(TextFormat("1- %-20s | %08d", ranque[0].nome, ranque[0].pontos), 200, 200, 50, YELLOW);
        DrawText(TextFormat("2- %-20s | %08d", ranque[1].nome, ranque[1].pontos), 200, 300, 50, YELLOW);
        DrawText(TextFormat("3- %-20s | %08d", ranque[2].nome, ranque[2].pontos), 200, 400, 50, YELLOW);
        DrawText(TextFormat("4- %-20s | %08d", ranque[3].nome, ranque[3].pontos), 200, 500, 50, YELLOW);
        DrawText(TextFormat("5- %-20s | %08d", ranque[4].nome, ranque[4].pontos), 200, 600, 50, YELLOW);

        EndDrawing(); //Fim do desenho

    }
    StopSound(som.ranqueado); //Para música do rank
}

void novo_score(JOGADOR jogador[top5], FLAPPY player)  //Função que pede o nome do jogador que conseguiu novo placar top 5 e grava ele no arquivo bin
{
    int posicao, i, tecla, num_letras=0; //Declaração de variáveis
    FILE *arq_rank;
    sprintf(player.Nome,"");
    le_jogador(jogador); //Função para aplicar conteúdo do bin nos jogadores
    while(!(IsKeyPressed(KEY_ENTER)))  //Enquanto enter não foi pressionado
    {
        tecla = GetCharPressed(); //Repete-se o mesmo processo do menu de Dificuldade, só com menos letras dessa vez
        while(tecla>0)
        {
            if(num_letras < 10)
            {
                player.Nome[num_letras] = (char)tecla;
                player.Nome[num_letras+1] = '\0';
                num_letras++;
            }
            tecla = GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE))
        {
            num_letras--;
            if(num_letras<0)
            {
                num_letras = 0;
            }
            player.Nome[num_letras] = '\0';
        }
        BeginDrawing();  //Inicio do desenho
        ClearBackground(PINK); //Limpa o background e desenha um fundo branco
        DrawText("Novo highscore!", 450, 200, 50, BLACK);  //Texto de novo highscore obtido
        DrawText("Digite seu nome(10 caracteres):", 200, 300, 50, BLUE); //Texto de explicação de entrada
        DrawRectangle(340, 440, 710, 120, WHITE);
        DrawText(player.Nome, 350, 450, 100, BLACK); //Texto que mostra o que o jogador está editando
        EndDrawing(); //Fim do desenho
    }
    for(i = top5-1; i>= 0; i--)  //Contador para a posição do novo highscore
    {
        if(player.Pontuacao > jogador[i].pontos)  //Se a pontuação do player for maior do que a do jogador i
        {
            posicao = i; // A posição do player será i
        }
    }
    for(i=top5-1; i>posicao; i--)  //Contador para Ordenamento de valores
    {
        strcpy(jogador[i].nome, jogador[i-1].nome); //Jogador na posição i recebe o nome do jogador acima dele
        jogador[i].pontos = jogador[i-1].pontos; //Jogador na posição i receb ospontos do jogador acima dele
    }
    strcpy(jogador[posicao].nome, player.Nome); //Nome e pontuação do player são aplicados na sua posição do ranking
    jogador[posicao].pontos = player.Pontuacao;
    arq_rank = fopen("./Ranking/top5.bin", "wb"); //Abertura do arquivo
    fwrite(jogador, sizeof(JOGADOR), 5, arq_rank); //São gravados os dados
    fclose(arq_rank); //Fechamento do arquivo
}

void iniciarJogo()  //Função do jogo em si
{
    Texture2D fundo; //Definição de variáveis
    FLAPPY player;
    JOGADOR jogador[top5];
    OBSTACULO obs[max_obstaculos]; // Declaração do array de obstáculos
    SONS som;
    int contador = 0, i=0, hold=0, temp_gap = gap, temp_vel = vel_obstaculos, temp_alt = dif_alt_maxima, validacao=0; //Contadores
    bool game_over=false, reiniciar=false; //Váriaveis de fim de jogo
    le_jogador(jogador);
    fundo = LoadTexture("./Texturas/fundo.png"); //Carregamento da textura do fundo
    for(i=0; i<max_obstaculos; i++)
    {
        obs[i].textura = LoadTexture("./Texturas/obstaculo.png");
    }
    cria_flappy(&player); //Cria o jogador
    carrega_sons(&som);
    cria_primeiro_obstaculo(obs, &contador); //Cria o primeiro obstáculo
//Começo do jogo
    while(!IsKeyPressed(KEY_TAB)) //O jogo roda enquanto TAB não for apertado
    {
        if(!game_over)  //Enquanto não ocorrer a condição de game over
        {
            if(!IsSoundPlaying(som.jogo)){
            PlaySound(som.jogo); //Toca música do jogo
        }
            validacao=0; //Permite que a função novo_score ocorra
            //Movimentar o player
            move_flappy(&player, som);
            //Movimentar os obstáculos
            move_obstaculo(obs);

            cria_obstaculo(obs, &contador); //Criar um novo obstáculo

            for(i=0; i<max_obstaculos; i++)  //Faz um loop para verificar se o player colidiu com qualquer um dos obstáculos na tela
            {
                if(verifica_colisao(player, obs, i, som)|| player.posicao.y+player.dimensao.y<0 || player.posicao.y>800)  //Se ocorrer uma colisão
                {
                    StopSound(som.jogo); //Para música do jogo
                    game_over = true; //Dar game over
                    PlaySound(som.game_over);
                }
            }
        }
        //Se a condição de game over tiver ocorrido
        else
        {
            for (i = 0; i < max_obstaculos; i++)   //Leva todos obstáculos para depois da tela para limpá-la
            {
                obs[i].cima.x = -80;
                obs[i].baixo.x = -80;
            }
            if(!validacao && player.Pontuacao > jogador[4].pontos)  //Se o player tiver pontuação maior que o quinto do ranking e ele ainda não tiver colocado o nome
            {
                novo_score(jogador, player); //Acontece a funçãonovo_score
                validacao = 1; //A função novo_score só irá acontecer denovo se o player recomeçar o jogo
                PlaySound(som.parabens); //Toca som de parabéns
            }
            if(IsKeyDown(KEY_R))  //Se espaço for pressionado novamente
            {
                if(hold == 1)
                {
                    reiniciar = true; //Marcar como true a condição de recomeço
                }
                hold = 1;
            }
            if(reiniciar)  //Se a condiçao de recomeço for verdadeira
            {
                int gap = temp_gap; //Restaura os valores de gap, velocidade e diferença de altura a seus originais
                int vel_obstaculos = temp_vel;
                int dif_alt_maxima = temp_alt;
                cria_flappy(&player); //Criar novo Flappy com pontuação zerada
                contador = 0; //contador reinicia
                cria_primeiro_obstaculo(obs, &contador); //Criar novo obstáculo
                game_over = false; //Zerar condições de game over e recomeço
                reiniciar = false;
            }
        }
        //Desenho
        BeginDrawing();
        //Limpar fundo
        ClearBackground(WHITE);
        //Se a condição de game over não tiver ocorrido
        if(!game_over)
        {
            desenha_background(fundo); //Desenha o background
            desenha_flappy(player); //Desenha o jogador
            desenha_obstaculo(obs); //Desenha os obstáculos
            desenha_score(player); //Desenha a pontuação
            if(player.Pontuacao % score_threshold == 0 && player.Pontuacao != 0)  //Se a pontuação do player chegar no threshold
            {
                aumento_dificuldade(player, obs, som); //Aumentar a dificuldade
            }
        }
        //Se a condição de game over tiver ocorrido
        else
        {
            DrawText("Fim de Jogo!", 350, 100, 100, RED);  //Desenha texto de fim de jogo
            DrawText(TextFormat("Score: %08d", player.Pontuacao), 350, 200, 70, BLACK); //Desenha o placar final
            DrawText("Pressione R para jogar novamente", 175, 500, 50, GREEN); //Desenha instrução para reiniciar
            DrawText("Pressione TAB para retornar ao menu", 150, 600, 50, BLACK);//Desenha instrução para voltar ao menu
        }
        //Fim do desenho
        EndDrawing();
    }
    //Descarrega todas texturas
    UnloadTexture(fundo);
    UnloadTexture(player.textura);
    for(i=0; i<max_obstaculos; i++)
    {
        UnloadTexture(obs[i].textura);
    }
}

int menu_desenha_e_valida()
{
    char opcao[50]; //Definição de variável
    sprintf(opcao, "1. Jogar"); //faz uma string com o nome da opção
    Rectangle Jogar = (Rectangle) // Faz um retângulo usando como parâmetro a string
    {
        ((screenWidth - MeasureText(opcao, fonte))/2) - 100, //coord x
        365, //coord y
        MeasureText(opcao,fonte), //largura
        fonte //altura
    };
    sprintf(opcao, "2. Dificuldade"); //Repete-se o mesmo com as outras 3 opções
    Rectangle Dificuldade = (Rectangle)
    {
        (screenWidth - MeasureText(opcao, fonte))/2,
        465,
        MeasureText(opcao,fonte),
        fonte
    };
    sprintf(opcao, "3. Top Scores"); //Repete-se o processo
    Rectangle TopScore = (Rectangle)
    {
        (screenWidth - MeasureText(opcao, fonte))/2,
        565,
        MeasureText(opcao,fonte),
        fonte
    };
    sprintf(opcao, "4. Sair"); //Repete-se
    Rectangle Sair = (Rectangle)
    {
        ((screenWidth - MeasureText(opcao, fonte))/2) - 100,
        665,
        MeasureText(opcao,fonte),
        fonte
    };

//Desenho das opções
    DrawRectangle(((screenWidth - MeasureText(opcao, fonte))/2) - 100, 355, MeasureText(opcao,fonte)+10, fonte-20, BROWN);
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Jogar)) //Se o cursor do mouse colidir com o retângulo da palavra, ela fica verde
    {
        DrawText("1. Jogar", 400, 365, 30, GREEN);
    }
    else
    {
        DrawText("1. Jogar", 400, 365, 30, BLACK);
    }
    DrawRectangle(((screenWidth - MeasureText(opcao, fonte))/2) - 100, 455, MeasureText(opcao,fonte)+10, fonte-20, BROWN);
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Dificuldade))
    {
        DrawText("2. Dificuldade", 400, 465, 30, GREEN);
    }
    else
    {
        DrawText("2. Dificuldade", 400, 465, 30, BLACK);
    }
    DrawRectangle(((screenWidth - MeasureText(opcao, fonte))/2) - 100, 555, MeasureText(opcao,fonte)+10, fonte-20, BROWN);
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, TopScore))
    {
        DrawText("3. Top Scores", 400, 565, 30, GREEN);
    }
    else
    {
        DrawText("3. Top Scores", 400, 565, 30, BLACK);
    }
    DrawRectangle(((screenWidth - MeasureText(opcao, fonte))/2) - 100, 655, MeasureText(opcao,fonte)+10, fonte-20, BROWN);
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Sair))
    {
        DrawText("4. Sair", 400, 665, 30, GREEN);
    }
    else
    {
        DrawText("4. Sair", 400, 665, 30, BLACK);
    }

//Seleção das opções
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Jogar) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) //Se o cursor colidir com o retângulo e for pressionado o botão esquerdo
    {
        return 1; //Retorna 1
    }
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Dificuldade) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return 2; //Retorna 2
    }
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, TopScore) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return 3; //Retorna 3
    }
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Sair) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return 4; //Retorna 4
    }
    else
    {
        return 0; //Senão, retorna 0
    }
}

void menu()  //Função que cria o menu;
{
    SONS som;
    int checagem = 0, tem_dificuldade=0, som_tocou=0; //Declaração de variáveis
    Texture2D inicio = LoadTexture("./Texturas/inicio.png");
    som.menu = LoadSound("./Sons/erro_menu.mp3"); //Som de erro no menu
    som.menu_tema = LoadSound("./Sons/menu.mp3");
    while (1)
    {
        BeginDrawing(); // Início do desenho
        ClearBackground(WHITE);
        DrawTextureEx(inicio, (Vector2){0,0}, 0, 4, WHITE);
        // Desenhar o menu com as opções e destacar a selecionada
        checagem = menu_desenha_e_valida(); //Desenho das opções e também escolha delas
        DrawRectangle(700, 50, 350, 300, BLUE);
        DrawText(".INF", 700, 250, 125, YELLOW);
        DrawText("Feito por Nicolas Fagundes e Emanuel Rauter", 10, 740, 20, BLACK);
        EndDrawing();//Fim do desenho
        if(!IsSoundPlaying(som.menu_tema)){
            PlaySound(som.menu_tema); //Toca musica do menu
        }
        // Lidar com a opção selecionada
        switch (checagem)
        {
        case 1: //Caso o retorno da função menu_desenha_e_valida seja 1, incia o jogo
            if(tem_dificuldade)  //Verifica se alguma dificuldade foi escolhida, se sim:
            {
                StopSound(som.menu_tema); //Para com a música do menu
                iniciarJogo(); //Dá início ao jogo
                checagem = 0; //Reinica valor de checagem
                som_tocou = 0; //Reinicia o marcador de som
            }
            else //Se nenhuma dificuldade foi escolhida:
            {
                BeginDrawing();
                DrawText("1. Jogar", 400, 365, 30, RED); //Texto pisca vermelho
                DrawText("->", 350, 465, 30, BROWN); //Uma seta aponta para Dificuldade
                EndDrawing();
                if(!som_tocou)  //Se não tocou o som de alerta
                {
                    PlaySound(som.menu); //Toca som de alerta
                    som_tocou = 1; //Indica que o som já tocou para evitar repetições
                }
            }
            break;
        case 2: //Caso o retorno seja 2, entra no menu de escolher dificuldade
            StopSound(som.menu_tema); //Para com a música do menu
            tem_dificuldade = Dificuldade(); //Leva a tela de dificuldade e checa se alguma foi secolhida
            som_tocou = 0; //Reinicia o marcador de som
            break;
        case 3: //Caso o retorno seja 3, entra no ranking dos 5 melhores placares
            StopSound(som.menu_tema); //Para com a música do menu
            Ranking(); //Leva ao Ranking dos jogadores
            som_tocou = 0; //Reinicia o marcador de som
            break;
        case 4: //Caso o retorno seja 4, fecha o jogo
            StopSound(som.menu_tema); //Para com a música do menu
            CloseWindow();  //Fecha a janela
            break;
        }
    }
}

void unload()
{
    CloseAudioDevice();
    CloseWindow();
}

int main(void)  //Função principal
{
    setup(); //Faz o setup do jogo
    menu(); //Carrega o menu
    unload();
}
