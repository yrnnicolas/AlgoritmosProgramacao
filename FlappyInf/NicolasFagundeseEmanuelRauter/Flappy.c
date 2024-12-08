//ALGORITMOS PROGRAMA��O
//PROFESSOR: MARCELO WALTER
//COMPONENTES: NICOLAS FAGUNDES MENDON�A 00344411 | EMANUEL RUSCHEL RAUTER 578247

#include <raylib.h>
#include <stdio.h>
#include <string.h>
//Defini��o de constantes
#define screenWidth 1200
#define screenHeight 800
#define max_obstaculos 4
#define top5 5
#define gravidade 1.5
#define fonte 70

//Defini��o de vari�veis universais
int score_threshold ;
int gap ;
int inc_gap ;
int dif_alt_maxima ;
int inc_dif_alt_maxima ;
int vel_obstaculos ;
int inc_vel_obstaculos ;

typedef struct //Defini��o da estrutura do Flappy Bird
{
    char Nome[11]; //Nome do jogador, ser� pedido caso ele fique entre os 5 melhores placares
    Vector2 posicao; //Vetor posicional. Cont�m posi��o {x,y} do jogador
    int Pontuacao; //Pontua��o, marca a pontua��o do jogador
    Vector2 velocidade; //Vetor de velocidade do jogador. Cont�m a velocidade X e Y do jogador
    Vector2 aceleracao; //Vetor de acelera��o do jogador. Cont�m a acelera��o X e Y do jogador
    Vector2 dimensao; //Vetor do tamanho do jogador. Cont�m a dimens�o X e Y do jogador
    float pulo; //Define a for�a do pulo do jogador
    Texture2D textura; //Textura do Flappy Bird
} FLAPPY;

typedef struct //Defini��o da estrutura dos obst�culos
{
    Vector2 cima; //Define as posi��es do cano de cima
    Vector2 baixo; //Define as posi��es do cano de baixo
    int altura; //Define a altura do cano
    int largura; //Define a largura do cano
    int velocidade; //Define a Velocidade do cano
    Texture2D textura; //Define a textura do cano
} OBSTACULO;

typedef struct //Defini��o da estrutura dos sons
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

typedef struct //Defini��o da estrutura do Jogador
{
    char nome[11]; //Nome do Jogador
    int pontos; //Pontua��o do jogador
} JOGADOR;

void setup()  //Fun��o da cria��o da tela de jogo
{
    InitWindow(screenWidth, screenHeight, "Flappy.inf"); //Cria janela do jogo 1200x800 com nome de Flappy.inf
    SetTargetFPS(30); //Define a quantidade de FPS desejados
    ToggleFullscreen(); //Ativa tela cheia
    InitAudioDevice(); //Inicia o dispositivo de �udio do computador
}

void cria_flappy(FLAPPY *f) //Fun��o de cria��o do FlappyBird
{
    f->posicao = (Vector2)
    {
        250, 400
    }; //Defini��o da Posi��o incial
    f->velocidade = (Vector2)
    {
        0, 0
    }; //Defini��o da Velocidade inicial
    f->aceleracao = (Vector2)
    {
        0, gravidade
    }; //Defini��o da acelera��o inicial
    f->dimensao = (Vector2)
    {
        80, 72
    }; //Defini��o do Tamanho inicial
    f->pulo = 20; //Defini��o da for�a do pulo
    f->textura = LoadTexture("./Texturas/flappy.png"); //Carregamento da textura do Flappy
    f->Pontuacao = 0; //Defini��o da pontua��o incial
}

void cria_primeiro_obstaculo(OBSTACULO o[max_obstaculos], int *i)  //Cria o primeiro obst�culo para depois os outros serem gerados a partir desse
{
    o[*i].baixo.x = screenWidth;//Canos de cima e de baixo come�am na direita da tela
    o[*i].cima.x =screenWidth;
    o[*i].altura = GetRandomValue(0, screenHeight-gap); //Altura do cano ser� um n�mero aleat�rio entre 0 e a altura da tela menos o gap
    o[*i].largura = 80; //Defini��o da largura dos canos
    o[*i].cima.y = 0; //Cano de cima sempre come�a no topo da tela
    o[*i].baixo.y = o[*i].altura + gap; //Cano de baixo come�a na altura do cao de cima mais o gap
    o[*i].velocidade = vel_obstaculos; //Defini��o da velocidade dos canos
    o[*i].textura = LoadTexture("./Texturas/obstaculo.png"); //Carregamento da textura dos canos
    *i++; // Soma 1 ao contador
}
void cria_obstaculo(OBSTACULO o[max_obstaculos], int *i)  //Fun��o de cria��o de obst�culos
{
    int altura_anterior = o[*i].altura; //Salva a altura do cano anterior ao ser gerado
    int altura_menor, altura_maior; //Vari�veis para criar o cano usando a diferen�a de altura m�xima
    altura_menor = altura_anterior - dif_alt_maxima; //A menor altura poss�vel � a subtra��o da altura do cano anterior com a diferen�a m�xima de altura
    if(altura_menor < 0)  //Se a altura m�nima sair da tela, defini-la como 0
    {
        altura_menor = 0;
    }
    altura_maior = altura_anterior + dif_alt_maxima; //A maior altura poss�vel � a soma da altura do cano anterior com a diferen�a m�xima de altura
    if(altura_maior > screenHeight - gap)  //Se a altura m�xima sair da tela, defini-la como a subtra��o da altura da tela pelo gap
    {
        altura_maior = screenHeight - gap;
    }
    if(screenWidth - o[*i].cima.x >= 400)  //Fun��o para o ciclo de canos, a cada 400 pixels que o �litmo cano gerado se mover, ser� gerado um novo cano.
    {
        *i = (*i + 1) % max_obstaculos; // A fun��o de resto garante a rota��o correta entre os n�meros 0, 1, 2 e 3 para numera��o do array
        o[*i].baixo.x = screenWidth;//Canos de cima e de baixo come�am na direita da tela
        o[*i].cima.x =screenWidth;
        o[*i].altura = GetRandomValue(altura_menor, altura_maior); //Altura do cano ser� um n�mero aleat�rio entre a menor altura poss�vel e a maior altura poss�vel
        o[*i].largura = 80; //Defini��o da largura dos canos
        o[*i].cima.y = 0; //Cano de cima sempre come�a no topo da tela
        o[*i].baixo.y = o[*i].altura + gap; //Cano de baixo come�a na altura do cao de cima mais o gap
        o[*i].velocidade = vel_obstaculos; //Defini��o da velocidade dos canos
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
void desenha_flappy(FLAPPY f)  //Fun��o que desenha o Flappy Bird
{
    DrawTextureEx(f.textura, (Vector2)
    {
        f.posicao.x-10,f.posicao.y-10
    }, 0, 5, WHITE); //Desenho do Flappy
}

void desenha_score(FLAPPY f)  //Fun��o que desenha a pontua��o
{
    DrawText(TextFormat("Score: %08d", f.Pontuacao), 50, 10, 40, BLACK); //Desenho do score
}

void desenha_background(Texture2D fundo)  //Fun��o que desenha o fundo
{
    DrawTextureEx(fundo, (Vector2)
    {
        0,0
    }, 0, 1.2, WHITE ); //Desenho do fundo
}

void desenha_obstaculo(OBSTACULO o[max_obstaculos])  //Fun��o que desenha os obst�culos
{
    int i; //contador
    for(i=0; i<max_obstaculos; i++)  //loop onde todos obst�culos gerados ser�o desenhados
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
        }, 0, WHITE); //Desenho do Obst�culo superior
        DrawTexturePro(o[i].textura, (Rectangle)
        {
            0, 0, 28, 151
        }, (Rectangle)
        {
            o[i].baixo.x, o[i].baixo.y, o[i].largura, screenHeight - (o[i].altura+gap)
        }, (Vector2)
        {
            o[i].largura, screenHeight - (o[i].altura+gap)
        }, 180, WHITE); //Desenho do obst�culo inferior
    }
}

void move_flappy(FLAPPY *f, SONS som)  //Fun��o que move o FlappyBird
{
    f->velocidade.y += f->aceleracao.y; //A velocidade vertical ser� igual a soma desta com a gravidade
    f->posicao.y += f->velocidade.y; //A posi��o vertical ser� igual a soma desta com a velocidade vertical
    f->Pontuacao++; //Soma-se 1 � pontua��o do jogador
    if(IsKeyPressed(KEY_SPACE)) //Se Espa�o for pressionado:
    {
        f->velocidade.y = -f->pulo; //A velocidade vertical ser� igual ao negativo do pulo
        PlaySound(som.flap); //Toca o som de bater a asa
    }
}

void move_obstaculo (OBSTACULO o[max_obstaculos])  //Fun��o que move os obst�culos
{
    int i; //Contador
    for(i=0; i<max_obstaculos; i++)  //Loop que move todos os obst�culos criados
    {
        o[i].cima.x -= o[i].velocidade; //A posi��o horizontal de ambos canos ser�o igauis a subtra��o de suas posi��es originais pelas suas velocidades horizontais
        o[i].baixo.x -= o[i].velocidade;
    }
}

int verifica_colisao (FLAPPY f, OBSTACULO o[], int i, SONS som)  //Fun��o que verifica colis�o
{
    Rectangle player = {f.posicao.x, f.posicao.y+6, f.dimensao.x-5, f.dimensao.y-10}; //� criado um ret�ngulo para o player e ambos canos
    Rectangle cano_cima = {o[i].cima.x, o[i].cima.y, o[i].largura, o[i].altura};
    Rectangle cano_baixo = {o[i].baixo.x, o[i].baixo.y, o[i].largura, screenHeight - (o[i].altura+gap)};
    if(CheckCollisionRecs (player, cano_cima) || CheckCollisionRecs (player, cano_baixo))  //Caso o player colida com qualquer um dos canos, o programa retorn verdadeiro
    {
        PlaySound(som.hit); //Toca o som de acertar o cano
        return 1;
    }
    else  //Sen�o, retorna falso
    {
        return 0;
    }
}

void aumento_dificuldade(FLAPPY f, OBSTACULO o[max_obstaculos], SONS som)  //Fun��o que aumenta a dificuldade de acordo com a pontua��o
{
    int i; //Contador
    if(gap > 100)  //Se gap for maior que 100
    {
        gap -= inc_gap; //Diminui o gap de acordo com as vari�veis universais
    }
    if(vel_obstaculos < 100)  //Se a velocidade for menor que 100
    {
        vel_obstaculos += inc_vel_obstaculos; //Aumenta a velocidade de acordo com as vari�veis universais
        for(i=0; i<max_obstaculos; i++)
        {
            o[i].velocidade = vel_obstaculos; //Aplica a nova velocidade a todos obst�culos
        }
    }
    if(dif_alt_maxima < 900)  //Se a diferen�a de altura m�xima for menor que 900
    {
        dif_alt_maxima += inc_dif_alt_maxima;  //Aumenta a diferen�a de altura m�xima de acordo com as vari�veis universais
    }
    DrawText(TextFormat("Score: %08d", f.Pontuacao), 50, 10, 40, WHITE); // Score pisca branco para indicar o aumento da dificuldade
    PlaySound(som.point); //Toca o som de pontua��o
}

int Dificuldade() //Fun��o que cria o menu de dificuldade
{
    FILE *dificuldade_arq; //Declara��o de vari�veis
    char nome_arq[21]={NULL}, nome_comp_arq[50];
    int tecla, num_letras=0, validacao=0;
    SONS som;
    som.dif = LoadSound("./Sons/dificuldade.mp3"); //Carrega m�sica da dificuldade
    while(!(IsKeyDown(KEY_TAB))) //Enquanto TAB n�o � pressionado
    {
        if(!IsSoundPlaying(som.dif)){ //Toca m�sica da dificuldade
            PlaySound(som.dif);
        }
        while(!(IsKeyPressed(KEY_ENTER)) && !(IsKeyPressed(KEY_TAB)))  //Enquanto nem o ENTER e nem o TAB estiverem apertados, rodar o loop
        {
            tecla = GetCharPressed(); //Vari�vel inteira recebe o valor num�rico da tecla pressionada
            while(tecla>0)  //Enquanto alguma tecla estiver pressionada
            {
                if(num_letras < 20)  //Se o limite de caracteres n�o foi atingido
                {
                    nome_arq[num_letras] = (char)tecla; //Espa�o atual da palavra � equivalente a tecla digitada
                    nome_arq[num_letras+1] = '\0'; //Pr�ximo espa�o recebe o sinal de fim de string
                    num_letras++; //Soma-se um ao contador de espa�os
                }
                tecla = GetCharPressed(); //Tecla recebe o valor de outra tecla pressionada
            }
            if(IsKeyPressed(KEY_BACKSPACE))  //Se BACKSPACE for apertado
            {
                num_letras--; //Diminui o contador de espa�os em um
                if(num_letras<0)  //Se ele ficar negativo
                {
                    num_letras = 0; //O fazer valer 0
                }
                nome_arq[num_letras] = '\0'; //Colocar o marcador de fim de string no espa�o ocupado pelo marcador
            }
            BeginDrawing();  // Come�a o desenho
            ClearBackground(LIGHTGRAY); //Limpa o background e aplica a cor LIGHTGRAY
            DrawText("<- Pressione TAB para retornar ao menu", 50, 50, 30, BLACK); //Texto de como sair
            DrawText("Insira nome do arquivo da dificuldade", 100, 200, 50, BLUE); //Texto para explicar entrada
            DrawRectangle(240, 290, 860, 120, WHITE);
            DrawText(nome_arq, 250, 300, 100, BLACK); //Texto da palavra sendo digitada
            EndDrawing(); //Fim do desenho
        }
        sprintf(nome_comp_arq, "./Dificuldade/%s", nome_arq); //Depois que se aperta ENTER, se cria uma string com o nome do arquivo dentro do camino para ach�-lo
        if(!(dificuldade_arq = fopen(nome_comp_arq, "r")))  //Se o arquivo n�o for encontrado, piscar ele vermelho
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
            fscanf(dificuldade_arq, "%d %d %d %d %d %d %d", &score_threshold, &gap, &inc_gap, &dif_alt_maxima, &inc_dif_alt_maxima, &vel_obstaculos, &inc_vel_obstaculos); //Scanear as vari�veis globais
            fclose(dificuldade_arq); //Fechar o arquivo
            validacao = 1; //Valida��o vira 1
        }

    }
    StopSound(som.dif); //Para m�sica da dificuldade
    return validacao; //Retorna com a valida��o se foi ou n�o escolhida uma dificuldade
}

void le_jogador(JOGADOR jogador[top5])  //Aplica conte�do de uma bin a um array de jogadores
{
    FILE *placar; //Declara��o de vari�vel
    placar = fopen("./Ranking/top5.bin", "rb"); //Abre arquivo
    fread(jogador, sizeof(JOGADOR), 5, placar); //L� e salva conte�do na estrutura JOGADOR
    fclose(placar); //Fecha arquivo
}

void Ranking() //Desenha o Ranking
{
    JOGADOR ranque[top5]; //Declara��o de vari�vel
    SONS som;
    som.ranqueado = LoadSound("./Sons/ranking.mp3"); //Carrega m�sica do rank
    le_jogador(ranque); //Aplica conte�do do top5.bin aos jogadores
    while(!IsKeyPressed(KEY_TAB))  //Enquanto TAB n�o � pressionado
    {
        if(!IsSoundPlaying(som.ranqueado)){ //Toca m�sica do rank
            PlaySound(som.ranqueado);
        }
        BeginDrawing(); //�nicio do desenho
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
    StopSound(som.ranqueado); //Para m�sica do rank
}

void novo_score(JOGADOR jogador[top5], FLAPPY player)  //Fun��o que pede o nome do jogador que conseguiu novo placar top 5 e grava ele no arquivo bin
{
    int posicao, i, tecla, num_letras=0; //Declara��o de vari�veis
    FILE *arq_rank;
    sprintf(player.Nome,"");
    le_jogador(jogador); //Fun��o para aplicar conte�do do bin nos jogadores
    while(!(IsKeyPressed(KEY_ENTER)))  //Enquanto enter n�o foi pressionado
    {
        tecla = GetCharPressed(); //Repete-se o mesmo processo do menu de Dificuldade, s� com menos letras dessa vez
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
        DrawText("Digite seu nome(10 caracteres):", 200, 300, 50, BLUE); //Texto de explica��o de entrada
        DrawRectangle(340, 440, 710, 120, WHITE);
        DrawText(player.Nome, 350, 450, 100, BLACK); //Texto que mostra o que o jogador est� editando
        EndDrawing(); //Fim do desenho
    }
    for(i = top5-1; i>= 0; i--)  //Contador para a posi��o do novo highscore
    {
        if(player.Pontuacao > jogador[i].pontos)  //Se a pontua��o do player for maior do que a do jogador i
        {
            posicao = i; // A posi��o do player ser� i
        }
    }
    for(i=top5-1; i>posicao; i--)  //Contador para Ordenamento de valores
    {
        strcpy(jogador[i].nome, jogador[i-1].nome); //Jogador na posi��o i recebe o nome do jogador acima dele
        jogador[i].pontos = jogador[i-1].pontos; //Jogador na posi��o i receb ospontos do jogador acima dele
    }
    strcpy(jogador[posicao].nome, player.Nome); //Nome e pontua��o do player s�o aplicados na sua posi��o do ranking
    jogador[posicao].pontos = player.Pontuacao;
    arq_rank = fopen("./Ranking/top5.bin", "wb"); //Abertura do arquivo
    fwrite(jogador, sizeof(JOGADOR), 5, arq_rank); //S�o gravados os dados
    fclose(arq_rank); //Fechamento do arquivo
}

void iniciarJogo()  //Fun��o do jogo em si
{
    Texture2D fundo; //Defini��o de vari�veis
    FLAPPY player;
    JOGADOR jogador[top5];
    OBSTACULO obs[max_obstaculos]; // Declara��o do array de obst�culos
    SONS som;
    int contador = 0, i=0, hold=0, temp_gap = gap, temp_vel = vel_obstaculos, temp_alt = dif_alt_maxima, validacao=0; //Contadores
    bool game_over=false, reiniciar=false; //V�riaveis de fim de jogo
    le_jogador(jogador);
    fundo = LoadTexture("./Texturas/fundo.png"); //Carregamento da textura do fundo
    for(i=0; i<max_obstaculos; i++)
    {
        obs[i].textura = LoadTexture("./Texturas/obstaculo.png");
    }
    cria_flappy(&player); //Cria o jogador
    carrega_sons(&som);
    cria_primeiro_obstaculo(obs, &contador); //Cria o primeiro obst�culo
//Come�o do jogo
    while(!IsKeyPressed(KEY_TAB)) //O jogo roda enquanto TAB n�o for apertado
    {
        if(!game_over)  //Enquanto n�o ocorrer a condi��o de game over
        {
            if(!IsSoundPlaying(som.jogo)){
            PlaySound(som.jogo); //Toca m�sica do jogo
        }
            validacao=0; //Permite que a fun��o novo_score ocorra
            //Movimentar o player
            move_flappy(&player, som);
            //Movimentar os obst�culos
            move_obstaculo(obs);

            cria_obstaculo(obs, &contador); //Criar um novo obst�culo

            for(i=0; i<max_obstaculos; i++)  //Faz um loop para verificar se o player colidiu com qualquer um dos obst�culos na tela
            {
                if(verifica_colisao(player, obs, i, som)|| player.posicao.y+player.dimensao.y<0 || player.posicao.y>800)  //Se ocorrer uma colis�o
                {
                    StopSound(som.jogo); //Para m�sica do jogo
                    game_over = true; //Dar game over
                    PlaySound(som.game_over);
                }
            }
        }
        //Se a condi��o de game over tiver ocorrido
        else
        {
            for (i = 0; i < max_obstaculos; i++)   //Leva todos obst�culos para depois da tela para limp�-la
            {
                obs[i].cima.x = -80;
                obs[i].baixo.x = -80;
            }
            if(!validacao && player.Pontuacao > jogador[4].pontos)  //Se o player tiver pontua��o maior que o quinto do ranking e ele ainda n�o tiver colocado o nome
            {
                novo_score(jogador, player); //Acontece a fun��onovo_score
                validacao = 1; //A fun��o novo_score s� ir� acontecer denovo se o player recome�ar o jogo
                PlaySound(som.parabens); //Toca som de parab�ns
            }
            if(IsKeyDown(KEY_R))  //Se espa�o for pressionado novamente
            {
                if(hold == 1)
                {
                    reiniciar = true; //Marcar como true a condi��o de recome�o
                }
                hold = 1;
            }
            if(reiniciar)  //Se a condi�ao de recome�o for verdadeira
            {
                int gap = temp_gap; //Restaura os valores de gap, velocidade e diferen�a de altura a seus originais
                int vel_obstaculos = temp_vel;
                int dif_alt_maxima = temp_alt;
                cria_flappy(&player); //Criar novo Flappy com pontua��o zerada
                contador = 0; //contador reinicia
                cria_primeiro_obstaculo(obs, &contador); //Criar novo obst�culo
                game_over = false; //Zerar condi��es de game over e recome�o
                reiniciar = false;
            }
        }
        //Desenho
        BeginDrawing();
        //Limpar fundo
        ClearBackground(WHITE);
        //Se a condi��o de game over n�o tiver ocorrido
        if(!game_over)
        {
            desenha_background(fundo); //Desenha o background
            desenha_flappy(player); //Desenha o jogador
            desenha_obstaculo(obs); //Desenha os obst�culos
            desenha_score(player); //Desenha a pontua��o
            if(player.Pontuacao % score_threshold == 0 && player.Pontuacao != 0)  //Se a pontua��o do player chegar no threshold
            {
                aumento_dificuldade(player, obs, som); //Aumentar a dificuldade
            }
        }
        //Se a condi��o de game over tiver ocorrido
        else
        {
            DrawText("Fim de Jogo!", 350, 100, 100, RED);  //Desenha texto de fim de jogo
            DrawText(TextFormat("Score: %08d", player.Pontuacao), 350, 200, 70, BLACK); //Desenha o placar final
            DrawText("Pressione R para jogar novamente", 175, 500, 50, GREEN); //Desenha instru��o para reiniciar
            DrawText("Pressione TAB para retornar ao menu", 150, 600, 50, BLACK);//Desenha instru��o para voltar ao menu
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
    char opcao[50]; //Defini��o de vari�vel
    sprintf(opcao, "1. Jogar"); //faz uma string com o nome da op��o
    Rectangle Jogar = (Rectangle) // Faz um ret�ngulo usando como par�metro a string
    {
        ((screenWidth - MeasureText(opcao, fonte))/2) - 100, //coord x
        365, //coord y
        MeasureText(opcao,fonte), //largura
        fonte //altura
    };
    sprintf(opcao, "2. Dificuldade"); //Repete-se o mesmo com as outras 3 op��es
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

//Desenho das op��es
    DrawRectangle(((screenWidth - MeasureText(opcao, fonte))/2) - 100, 355, MeasureText(opcao,fonte)+10, fonte-20, BROWN);
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Jogar)) //Se o cursor do mouse colidir com o ret�ngulo da palavra, ela fica verde
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

//Sele��o das op��es
    if(CheckCollisionPointRec((Vector2)
{
    GetMouseX(), GetMouseY()
    }, Jogar) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) //Se o cursor colidir com o ret�ngulo e for pressionado o bot�o esquerdo
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
        return 0; //Sen�o, retorna 0
    }
}

void menu()  //Fun��o que cria o menu;
{
    SONS som;
    int checagem = 0, tem_dificuldade=0, som_tocou=0; //Declara��o de vari�veis
    Texture2D inicio = LoadTexture("./Texturas/inicio.png");
    som.menu = LoadSound("./Sons/erro_menu.mp3"); //Som de erro no menu
    som.menu_tema = LoadSound("./Sons/menu.mp3");
    while (1)
    {
        BeginDrawing(); // In�cio do desenho
        ClearBackground(WHITE);
        DrawTextureEx(inicio, (Vector2){0,0}, 0, 4, WHITE);
        // Desenhar o menu com as op��es e destacar a selecionada
        checagem = menu_desenha_e_valida(); //Desenho das op��es e tamb�m escolha delas
        DrawRectangle(700, 50, 350, 300, BLUE);
        DrawText(".INF", 700, 250, 125, YELLOW);
        DrawText("Feito por Nicolas Fagundes e Emanuel Rauter", 10, 740, 20, BLACK);
        EndDrawing();//Fim do desenho
        if(!IsSoundPlaying(som.menu_tema)){
            PlaySound(som.menu_tema); //Toca musica do menu
        }
        // Lidar com a op��o selecionada
        switch (checagem)
        {
        case 1: //Caso o retorno da fun��o menu_desenha_e_valida seja 1, incia o jogo
            if(tem_dificuldade)  //Verifica se alguma dificuldade foi escolhida, se sim:
            {
                StopSound(som.menu_tema); //Para com a m�sica do menu
                iniciarJogo(); //D� in�cio ao jogo
                checagem = 0; //Reinica valor de checagem
                som_tocou = 0; //Reinicia o marcador de som
            }
            else //Se nenhuma dificuldade foi escolhida:
            {
                BeginDrawing();
                DrawText("1. Jogar", 400, 365, 30, RED); //Texto pisca vermelho
                DrawText("->", 350, 465, 30, BROWN); //Uma seta aponta para Dificuldade
                EndDrawing();
                if(!som_tocou)  //Se n�o tocou o som de alerta
                {
                    PlaySound(som.menu); //Toca som de alerta
                    som_tocou = 1; //Indica que o som j� tocou para evitar repeti��es
                }
            }
            break;
        case 2: //Caso o retorno seja 2, entra no menu de escolher dificuldade
            StopSound(som.menu_tema); //Para com a m�sica do menu
            tem_dificuldade = Dificuldade(); //Leva a tela de dificuldade e checa se alguma foi secolhida
            som_tocou = 0; //Reinicia o marcador de som
            break;
        case 3: //Caso o retorno seja 3, entra no ranking dos 5 melhores placares
            StopSound(som.menu_tema); //Para com a m�sica do menu
            Ranking(); //Leva ao Ranking dos jogadores
            som_tocou = 0; //Reinicia o marcador de som
            break;
        case 4: //Caso o retorno seja 4, fecha o jogo
            StopSound(som.menu_tema); //Para com a m�sica do menu
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

int main(void)  //Fun��o principal
{
    setup(); //Faz o setup do jogo
    menu(); //Carrega o menu
    unload();
}
