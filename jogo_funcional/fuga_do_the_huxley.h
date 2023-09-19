#ifndef JOGABILIDADE
#define JOGABILIDADE

// Arquivos .c
//------------------------------------------------------------------------------------
//bibliotecas e structs
#include "src/libs.c"
#include "src/structs.c"
//------------------------------------------------------------------------------------
// Funcoes arquivos

//obstaculos
#include "src/obstaculos/colisao_veiculos.c"
#include "src/obstaculos/atualiza_veiculos.c"
#include "src/obstaculos/atualiza_buraco.c"
#include "src/obstaculos/atualiza_helicoptero.c"
#include "src/desenha_veiculos.c"

#include "src/highscore.c" 

//visual
#include "src/atualiza_animacoes.c"
#include "src/DrawContents.c"
#include "src/fade_to.c"

//geral
#include "src/colisao_topoebase.c"

#include "src/tutorial.c" 
//------------------------------------------------------------------------------------


// Declaracoes de funcoes
//------------------------------------------------------------------------------------
// Atualiza posicao de veiculos  
    void atualiza_veiculos(colecao Veiculos[], float screen_speed, const int screenSizes[], int transicao_frame);

// Atualiza buraco
    void atualiza_buraco(Circle *buraco_obj, float screen_speed, const int screenSizes[], int transicao_frame);

// Checa colisao de veiculos
    int  colisao_veiculos(colecao Veiculos[], Rectangle *player, int *colided_left_right[], float *camera_target_x, int unidade);

// Anima lazer do helicoptero
    void atualiza_helicoptero(Line *lazer, Animacao *helicoptero, int *frame_helic, const int screenSizes[], int transicao_frame);


// Bloqueia player de sair da tela por cima ou baixo
    void colisao_topoebase(Rectangle *player, int bordas[]);


// Atualiza highscores
    void highscore(Pontuacoes player);
    Pontuacoes *ler_arquivo(FILE *arq);

// Atualiza animacoes
    void atualiza_animacoes(Animacao *Animacoes[], int qtd, int global_fps);

// Fades screen to desired color
    void fade_to(int *fade_frame, int fade_speed, Color *fade_cor, Color fade_src, Color fade_dst, const int screenSizes[]);

    void desenha_veiculos(colecao Veiculos[], int fase);



//------------------------------------------------------------------------------------

#endif