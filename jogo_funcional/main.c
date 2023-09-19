
//------------------------------------------------------------------------------------

//biblioteca principal
#include "fuga_do_the_huxley.h"

void menu_salve(int *player_qtd,int *fechar,int *modo, Music *musica_menu);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    // Tela
    
    // Versao final com tela cheia
    // Inicializa janela nula
    InitWindow(700, 500, "janela raylib");
    // Configura janela com tamanho proporcional ao monitor do usuario
    const int screenWidth = GetMonitorWidth(GetCurrentMonitor()); 
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());
    const int screenSizes[] = { screenWidth, screenHeight };
    SetWindowSize(screenWidth, screenHeight);   
    ToggleFullscreen();

    //variavel usada para determinar a proporcao das coisas na tela
    int proporcao = screenWidth;
    float unidade = ((float)screenWidth) / 1366.0f;
    
    
    //camera
    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    
    // Initialize audio device
    InitAudioDevice();
    float master_volume = 0.05f;
    
    
    // Inicialização de assets, exceto veiculos
    //--------------------------------------------------------------------------------------
    
    // Fundo mundo real 1
    //Texture2D fundomr1 = LoadTexture("assets/backgrounds/fundomr1.png");
    Texture2D fundo[4] = {
        LoadTexture("assets/backgrounds/fundocy1.png"),
        LoadTexture("assets/backgrounds/fundocy2.png"),
        LoadTexture("assets/backgrounds/fundomr1.png"),
        LoadTexture("assets/backgrounds/fundomr2.png")
    };
    
    // tuneis
    Texture2D tunel[2] = {
        LoadTexture("assets/tunelcy.png"),
        LoadTexture("assets/tunelmr.png")
    };
    
    // Sprite sheets
    Texture2D buraco_sprite = LoadTexture("assets/Obstaculos/sprite_buraco.png");
    Texture2D helicoptero_sprite = LoadTexture("assets/Obstaculos/sprite_helicoptero.png");
    Texture2D pendrive_sprite = LoadTexture("assets/pendrive_spritesheet.png");
    
    
     // Atribuindo musicas
    Music Cyberverso = LoadMusicStream("assets/Soundtrack/Cyberverso.mp3");
    Music Creditos = LoadMusicStream("assets/Soundtrack/Creditos.mp3");
    Music Infinito = LoadMusicStream("assets/Soundtrack/Infinito.mp3");
    Music Menu = LoadMusicStream("assets/Soundtrack/Menu.mp3");
    Music MundoReal = LoadMusicStream("assets/Soundtrack/Mundo Real.mp3");
    Music Tutorial = LoadMusicStream("assets/Soundtrack/Tutorial.mp3");

    // Efeitos sonoros
    Sound ColisaoCarro = LoadSound("assets/Efeitos sonoros/Colisoes/ColisaoCarro.ogg");
    Sound Pendrive = LoadSound("assets/Efeitos sonoros/Pendrive/Pendrive.mp3");
    Sound Teclado = LoadSound("assets/Efeitos sonoros/Teclado/Teclado.mp3");
    Sound TiroHelicoptero = LoadSound("assets/Efeitos sonoros/Veiculos/Tiro do Helicoptero.mp3");
    Sound TiroTanque = LoadSound("assets/Efeitos sonoros/Veiculos/Tiro do Tanque.ogg");
    Music Helicoptero = LoadMusicStream("assets/Efeitos sonoros/Veiculos/Helicoptero.mp3");

    SetSoundVolume(ColisaoCarro, master_volume * 1.5);
    SetSoundVolume(Pendrive, master_volume);
    SetSoundVolume(Teclado, master_volume);
    SetSoundVolume(TiroHelicoptero, master_volume);
    SetSoundVolume(TiroTanque, master_volume);
    
    //tambem sao inicializadas algumas texturas na parte dos veiculos
    //a area em que isso aconte esta claramente indicada
    
    //--------------------------------------------------------------------------------------
    
    
    // Inicia musica
    Music musicas[] = {
        Cyberverso, //0
        Creditos, //1
        Infinito, //2
        Menu, //3
        MundoReal, //4
        Tutorial, //5
        Helicoptero, //6
    };
    int mus_atual = 4;
    int mus_passada;
    
    SetMusicVolume(musicas[mus_atual], master_volume);
    PlayMusicStream(musicas[0]);   
    PlayMusicStream(musicas[1]);
    PlayMusicStream(musicas[2]);
    PlayMusicStream(musicas[3]);
    PlayMusicStream(musicas[4]);
    PlayMusicStream(musicas[5]);
    PlayMusicStream(musicas[6]);
    
    
    
    // Expansao da textura para preencher a tela
    float expansao = ((float) screenWidth + unidade * 60) / fundo[0].width;
    // Altura da textura apos expansao
    float fundo_height = fundo[0].height * expansao;
    // Posicao das duas texturas em loop
    int fundo1y = - ((float)fundo_height) * 0.5f;
    int fundo2y = - ((float)fundo_height) * 1.5f;
    // Posicao em que testuras resetam loop
    int fim_do_fundo = fundo_height * 1.5f;
    
    
    //variavel que determina a velocidade da tela
    float screen_speed = 2 * unidade;
    
    
    //player
    int player_qtd = player_max;
    Rectangle player[] = {
        { screenWidth / 2 - proporcao / 60, screenHeight / 2, proporcao / 40, proporcao / 15 },
        { screenWidth / 2 - proporcao / 60, screenHeight / 2, proporcao / 40, proporcao / 15 },
        { screenWidth / 2 - proporcao / 60, screenHeight / 2, proporcao / 40, proporcao / 15 },
        { screenWidth / 2 - proporcao / 60, screenHeight / 2, proporcao / 40, proporcao / 15 }
    };
    int player_moves[][4] = {
        {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT},
        {KEY_W, KEY_A, KEY_S, KEY_D},
        {KEY_KP_8, KEY_KP_4, KEY_KP_5, KEY_KP_6},
        {KEY_I, KEY_J, KEY_K, KEY_L}
    };
    
    
    //barreiras topo e base
    int top_of_screen = screenHeight / 10;
    int bot_of_screen = screenHeight - screenHeight / (10);
    //barreiras laterais
    int left_wall = screenWidth / 6;
    int right_wall = screenWidth - screenWidth / 6;
    //vetor com todas as bordas
    int bordas[] = { bot_of_screen, top_of_screen, left_wall, right_wall };
    //variaveis usadas nas colisoes
    int colided_left[player_max] = {}, colided_right[player_max] = {};
    int *colided_left_right[player_max][2];
    for(int i = 0; i < player_max; i++) {
        colided_left_right[i][0] = &colided_left[i];
        colided_left_right[i][1] = &colided_right[i];
    }
    int colisao[player_max] = {};
    
    
    //contador de vidas do jogador
    int vidas[player_max] = {3, 3, 3, 3};
    char vidas_str_base[player_max][8] = {"Vidas1:", "Vidas2:", "Vidas3:", "Vidas4:"};
    char vidas_string[player_max][4] = {{}};
    //strings com qtd de carros, motos, caminhoes na tela
    char na_tela_str[3][4] = { "0 0", "0 0", "0 0" };
    //string no formato "pontuação: %i", pontuacao
    char pontuacao_str[player_max][32] = {};
    float pontuacao[player_max] = {};
    
    
    // Veiculos na garagem
    
    // Carros
    colecao carros;
    //qtd
    carros.qtd = 6;
    //speed e ocupacao
    carros.speed = 3;
    carros.ocupacao = 0.75f;
    //vetor lista
    Rectangle carros_lista[carros.qtd];
    carros.lista = carros_lista;
    //vetor texturas
    Texture2D carros_texturascy[carros.qtd];
    Texture2D carros_texturasmr[carros.qtd];
    carros.texturas[0] = carros_texturascy;
    carros.texturas[1] = carros_texturasmr;
    
    // Motos
    colecao motos;
    //qtd
    motos.qtd = 2;
    //speed
    motos.speed = -2;
    //vetor lista
    Rectangle motos_lista[motos.qtd];
    motos.lista = motos_lista;
    //motos so tem uma textura
    Texture2D motos_textura;
    motos.texturas[0] = &motos_textura;
    
    //Caminhoes
    colecao caminhoes;
    //qtd
    caminhoes.qtd = 4;
    //speed e ocupacao
    caminhoes.speed = 2;
    caminhoes.ocupacao = 0.5f;
    //vetor lista
    Rectangle caminhoes_lista[caminhoes.qtd];
    caminhoes.lista = caminhoes_lista;
    //vetor texturas
    Texture2D caminhoes_texturascy[caminhoes.qtd];
    Texture2D caminhoes_texturasmr[caminhoes.qtd];
    caminhoes.texturas[0] = caminhoes_texturascy;
    caminhoes.texturas[1] = caminhoes_texturasmr;
    
    
    // Inicializando texturas dos carros, caminhoes, motos
    //--------------------------------------------------------------------------------------
    char veiculos_arq_nome[80] = {};
    
    // Carros
    for(int i = 0; i < carros.qtd; i++) {
        //carros cyberverso de 1 a 6
        snprintf(veiculos_arq_nome, 80, "assets/Obstaculos/carros/carroscy/carrocy%i.png", i + 1);
        carros.texturas[0][i] = LoadTexture(veiculos_arq_nome);
    }
    for(int i = 0; i < carros.qtd; i++) {
        //carros mundo real de 1 a 6
        snprintf(veiculos_arq_nome, 80, "assets/Obstaculos/carros/carrosmr/carromr%i.png", i + 1);
        carros.texturas[1][i] = LoadTexture(veiculos_arq_nome);
    }
    // Motos
    motos.texturas[0][0] = LoadTexture("assets/Obstaculos/moto.png");
    
    // Caminhoes
    for(int i = 0; i < caminhoes.qtd; i++) {
        //caminhoes cyberverso de 1 a 4
        snprintf(veiculos_arq_nome, 80, "assets/Obstaculos/cami_onib/cami_onibcy/cami_onibcy%i.png", i + 1);
        caminhoes.texturas[0][i] = LoadTexture(veiculos_arq_nome);
    }
    for(int i = 0; i < caminhoes.qtd; i++) {
        //caminhoes mundo real de 1 a 4
        snprintf(veiculos_arq_nome, 80, "assets/Obstaculos/cami_onib/cami_onibmr/cami_onibmr%i.png", i + 1);
        caminhoes.texturas[1][i] = LoadTexture(veiculos_arq_nome);
    }
    
    //--------------------------------------------------------------------------------------
    
    // Inicialização dos retangulos "hitbox" dos carros, motos, caminhoes
    // Dimensionados a partir das texturas
    //carros
    for (int i = 0; i < carros.qtd; i++) {
        carros.lista[i] = (Rectangle) 
        { 
            -screenWidth -carros.lista[i].width, 
            -GetRandomValue(0, screenHeight / 2), 
            proporcao / 12, 
            (proporcao / 12) * carros.texturas[0][i].height / carros.texturas[0][i].width
        };
    }
    //motos
    for (int i = 0; i < motos.qtd; i++) {
        motos.lista[i] = (Rectangle) { -screenWidth -motos.lista[i].width, GetRandomValue(1, 4) * screenSizes[1], proporcao / 40, proporcao / 15 };
    }
    //caminhoes
    for (int i = 0; i < caminhoes.qtd; i++) {
        caminhoes.lista[i] = (Rectangle) { 
            -screenWidth -caminhoes.lista[i].width, 
            -GetRandomValue(0, screenHeight * 2), 
            proporcao / 10, 
            caminhoes.texturas[0][i].height * proporcao / 10 / caminhoes.texturas[0][i].width
        };
    }
    
    // Veiculos final
    colecao Veiculos[3] = { carros, motos, caminhoes };
    
    
    // Obstaculos estaticos
    
    //circulo do buraco / vazamento de memoria
    Circle buraco_obj = (Circle) {
        (Vector2) { -screenWidth - proporcao / 18, -screenHeight }, //pos x, y
        proporcao / 18 //radius
    };
    
    //struct de animacao para buraco animado
    Animacao buraco = {
        
        buraco_sprite, //textura que armazena todos os frames da animacao
        (Rectangle) 
        {              //retangulo de origem da textura dentro do sprite sheet:
            0.0f, 0.0f, 
            (float)buraco_sprite.height, 
            (float)buraco_sprite.height 
        },
        (Rectangle) 
        {              //retangulo em que textura é printada sobre circulo:
            buraco_obj.pos.x, buraco_obj.pos.y, 
            (float)buraco_obj.radius * 2.5f, 
            (float)buraco_obj.radius * 2.5f 
        },
        10, //numero de frames na animacao
        0,  //frame atual na animacao
        0,  //contador de frames do jogo
        60, //numero de frames da animacao por segundo
        
    };
    
    
    //ataque helicoptero fase 3
    //linha de tiro
    Line lazer = {
        (Vector2) { -screenWidth, -screenHeight },
        (Vector2) { -screenWidth, -screenHeight },
        (float)screenWidth / 200.0f,
        (Vector2) { 0.0f, 0.0f }
    };
    Vector2 buffer_v2;
    int frame_helic = 0;
    int max_frames_helic = 270;
    
    Animacao helicoptero = {
        
        helicoptero_sprite, //textura que armazena todos os frames da animacao
        
        (Rectangle) 
        {              //retangulo de origem da textura dentro do sprite sheet:
            0.0f, helicoptero_sprite.height / 9,
            helicoptero_sprite.width / 4, 
            helicoptero_sprite.height * 0.6
        },
        (Rectangle) 
        {              //retangulo em que textura é printada:
            0.0f, 0.0f,
            helicoptero_sprite.width / 4,
            helicoptero_sprite.height * 0.6
        },
        
        4,    //numero de frames na animacao
        0,    //frame atual na animacao
        0,    //contador de frames do jogo
        30,   //numero de frames da animacao por segundo
        
    };
    
    
    //TODO ataque tanke fase 4
    
    
    Animacao pendrive = (Animacao) {
        pendrive_sprite,
        (Rectangle) 
        {              //retangulo de origem da textura dentro do sprite sheet:
            0.0f, pendrive_sprite.height,
            pendrive_sprite.width / 84, 
            pendrive_sprite.height
        },
        (Rectangle) 
        {              //retangulo em que textura é printada:
            0.0f, 0.0f, screenWidth, screenHeight
        },
        
        84,    //numero de frames na animacao
        0,    //frame atual na animacao
        0,    //contador de frames do jogo
        24,   //numero de frames da animacao por segundo
        
    };
    
    
    int animacoes_qtd = 3;
    Animacao *Animacoes[] = {
        &buraco,
        &helicoptero,
        &pendrive
    };
    
    
    // Fase atual
    int fase = 1;
    // Contador de loops do fundo
    int fundo_loops = 0;
    
    
    // Set our game to run at 60 frames-per-second
    int global_fps = 60;
    SetTargetFPS(global_fps);               
    
    //contador apos colisoes
    int colisao_max = global_fps * 2.5f;
    
    //conta tempo de frame
    float timer = 0.0f;
    
    
    //variaveis usadas no fade da tela
    int fade_frame = 1;
    Color fade_cor = {0,0,0,255};
    Color fade_dst = {};
    Color fade_src = fade_cor;
    int fade_speed = 3;
    
    
    int modo_de_jogo = 1;
    
    
    //tutorial
    long int tutorial_frame = 0;
    int veiculos_qtds[3];
    for(int i = 0; i < 3;i ++) {
        veiculos_qtds[i] = Veiculos[i].qtd;
    }
    
    
    int transicao_frame = 0;
    float tunel_y = -tunel[1].height * 5;
    
    
    player_qtd = 1;
    for(int i = player_qtd; i < player_max; i++) {
        vidas[i] = 0;
    }
    Color cores_moto[] = {
        SKYBLUE,
        GREEN,
        RED,
        DARKPURPLE,
    };
    char player_cor[player_max] = {};
    player_cor[0] = 2;
    char ganhou_ou_nao = 0;
    int fechou = 0;
    int saiu=0;
    
    float time_comeco = 0;
    
    //FILE *arq = fopen ("highscore.bin", "rb");
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && fechou == 0)    // Detect window close button or ESC key
    {
        // Frame timer for update delay7
        //----------------------------------------------------------------------------------
        
        timer += GetFrameTime();
        
        if (timer >= 1.0f / global_fps) {
            
            //reseta frame timer
            timer = 0.0f;
    
            // Update
            //----------------------------------------------------------------------------------
            
            SetMousePosition(screenWidth, screenHeight);
            
            if (saiu == 0) {
                
                //roda menu
                menu_salve(&player_qtd, &fechou, &modo_de_jogo, musicas);
                saiu = 1;
                
                //reseta partes do jogo para inicio
                for(int i = 0; i < player_qtd; i++) {
                    vidas[i] = 3;
                }
                transicao_frame = 0;
                fade_frame = 1;
                fade_cor = (Color){0,0,0,255};
                fade_dst = (Color){0,0,0,0};
                fade_src = fade_cor;
                fase = 1;
                
                // Expansao da textura para preencher a tela
                expansao = ((float) screenWidth + unidade * 60) / fundo[fase - 1].width;
                // Altura da textura apos expansao
                fundo_height = fundo[fase - 1].height * expansao;
                // Posicao das duas texturas em loop
                fundo1y = - ((float)fundo_height) * 0.5f;
                fundo2y = - ((float)fundo_height) * 1.5f;
                // Posicao em que testuras resetam loop
                fim_do_fundo = fundo_height * 1.5f;
                
                time_comeco = GetTime();
                
            }
        
            
            // realiza tutorial
            if(modo_de_jogo == 0) {
                fase = 4;
                // Expansao da textura para preencher a tela
                expansao = ((float) screenWidth + unidade * 60) / fundo[fase - 1].width;
                // Altura da textura apos expansao
                fundo_height = fundo[fase - 1].height * expansao;
                // Posicao das duas texturas em loop
                fundo1y = - ((float)fundo_height) * 0.5f;
                fundo2y = - ((float)fundo_height) * 1.5f;
                // Posicao em que testuras resetam loop
                fim_do_fundo = fundo_height * 1.5f;
                
                tutorial(&tutorial_frame, Veiculos, &buraco_obj, &frame_helic, screenSizes);
            }
            
          
            // Tocar música
            // Update music buffer with new stream data
            UpdateMusicStream(musicas[mus_atual]);
            
            
            //morte, fim, recomeco
            if( vidas[0] <= 0 && vidas[1] <= 0  && vidas[2] <= 0  && vidas[3] <= 0 ) {
                
                //dps, voltar para menu
                saiu = 0;
                //reseta pontuacao, fase, fundo_loops
                for(int i = 0; i < player_qtd; i++) {
                    pontuacao[i] = 0;
                }
                fundo_loops = 0;
                //reseta objetos do jogo
                buraco_obj.pos = (Vector2) {-screenWidth, 0};
                buraco.dest.x = -screenWidth;
                frame_helic = 0;
                //fade to black
                if(fade_frame == 0) {
                    fade_frame = 1;
                    fade_src = (Color){0,0,0,0};
                    fade_dst = (Color){0,0,0,255};
                    fade_speed = 2;
                }
                
        
            // Player movement
            for(int i = 0; i < player_qtd; i++) {
                
                if(vidas[i] > 0 && !colided_left[i] && !colided_right[i]){
                
                    // Movimento Principal do personagem
                    if (IsKeyDown(player_moves[i][3])) player[i].x += unidade * 6;
                    else if (IsKeyDown(player_moves[i][1])) player[i].x -= unidade * 6;
                    
                    if (IsKeyDown(player_moves[i][0])) player[i].y -= unidade * 8;
                    else if (IsKeyDown(player_moves[i][2])) player[i].y += unidade * 7;
                    
                    //movimento da tela 
                    player[i].y += screen_speed;
                
                }
                
            }
            
            
            //movimento da tela 
            fundo1y += screen_speed * 4;
            fundo2y += screen_speed * 4;
            
            //loop do fundo
            if(fundo1y + fundo_height >= fim_do_fundo) {
                fundo1y = fundo2y - fundo_height;
                fundo_loops++;
            }
            if(fundo2y + fundo_height >= fim_do_fundo) {
                fundo2y = fundo1y - fundo_height;
                fundo_loops++;
            } 
            //apos _ segundos comeca transicao para fase 2
            if(fase == 1 && GetTime() - time_comeco > 20 && transicao_frame == 0) {
                
                transicao_frame = 1;
                tunel_y = -tunel[1].height * 6;
                
            }
            //apos _ segundos comeca transicao para fase 3
            else if(fase == 2 && GetTime() - time_comeco > 40 && transicao_frame == 0) { 
                
                transicao_frame = 1;
                tunel_y = -tunel[1].height * 6;
                
            }
            //apos _ segundos entra na fase 3
            else if(fase == 3 && GetTime() - time_comeco > 60 && transicao_frame == 0) { 
                
                transicao_frame = 1;
                tunel_y = -tunel[1].height * 6;
                
            }
            //apos _ segundos final do jogo
            else if(fase == 4 && GetTime() - time_comeco > 97 && GetTime() - time_comeco < 97.1 && fade_frame == 0) {
                
                fade_frame = 1;
                fade_src = (Color){0,0,0,0};
                fade_dst = (Color){255,255,255,255};
                fade_speed = 1;
                
            }
            else if(fase == 4 && GetTime() - time_comeco > 100) {
                
                saiu = 0;
                
            }
              
            
            //verifica cena de transicao
            if(transicao_frame > 0) {
                transicao_frame++;
                tunel_y += screen_speed * 4;
            }
            if(transicao_frame == 300) {
                
                //volta para menu ou fim do jogo?
                if(fase == 4 && modo_de_jogo == 1 ) {
                    saiu = 0;
                }
                
                //passa fase
                if(fase < 4) {
                    fase++;
                    if (fase == 1 || fase == 3){
                        mus_passada = mus_atual;
                        StopMusicStream(musicas[mus_passada]);
                        mus_atual = 4;
                        UpdateMusicStream(musicas[mus_atual]);
                        PlayMusicStream(musicas[mus_atual]);
                    }

                    else if (fase == 2 || fase == 4){
                        mus_passada = mus_atual;
                        StopMusicStream(musicas[mus_passada]);
                        mus_atual = 0;
                        UpdateMusicStream(musicas[mus_atual]);
                        PlayMusicStream(musicas[mus_atual]);
                    }
                }
                
                if(modo_de_jogo == 2){
                    mus_passada = mus_atual;
                    StopMusicStream(musicas[mus_passada]);
                    mus_atual = 2;
                    UpdateMusicStream(musicas[mus_atual]);
                    PlayMusicStream(musicas[mus_atual]);
                }
                
                else if(modo_de_jogo == 0){
                    mus_passada = mus_atual;
                    StopMusicStream(musicas[mus_passada]);
                    mus_atual = 5;
                    UpdateMusicStream(musicas[mus_atual]);
                    PlayMusicStream(musicas[mus_atual]);
                }
                
                //altera fase de 1 a 4
                //fase = fase % 4 + 1;

                //Mudar musica de acordo com a fase
                if (fase == 1 || fase == 3){
                    mus_atual = 4;
                    UpdateMusicStream(musicas[mus_atual]);
                }

                else if (fase == 2 || fase == 4){
                    mus_atual = 0;
                    UpdateMusicStream(musicas[mus_atual]);
                }
                
                //atualiza variaveis de fundo para novo fundo
                
                // Expansao da textura para preencher a tela
                expansao = ((float) screenWidth + unidade * 60) / fundo[fase - 1].width;
                // Altura da textura apos expansao
                fundo_height = fundo[fase - 1].height * expansao;
                // Posicao das duas texturas em loop
                fundo1y = - ((float)fundo_height) * 0.5f;
                fundo2y = - ((float)fundo_height) * 1.5f;
                // Posicao em que testuras resetam loop
                fim_do_fundo = fundo_height * 1.5f;
                
    
            }
            if(transicao_frame > 660) {
                tunel_y = -tunel[1].height * 5;
                transicao_frame = 0;
            }
            
            
            // Realizando o movimento dos veiculos na garagem
            atualiza_veiculos(Veiculos, screen_speed, screenSizes, transicao_frame);
            
            
            // Colisões
            
            
            //testes condicionais de fase
            if(fase >= 2) { //passou fase 1, buracos a partir da 2
            
                //atualiza burraco_obj
                atualiza_buraco(&buraco_obj, screen_speed, screenSizes, transicao_frame);
                
                //atualiza retangulo de destino da animacao do buraco
                buraco.dest.x = buraco_obj.pos.x - buraco_obj.radius * 1.45f;
                buraco.dest.y = buraco_obj.pos.y - buraco_obj.radius * 1.25f;
                
            }
            if(fase >= 3) { //passou fase 2, helicopteros a partir da 3
                
                //anima vetores do lazer do helicoptero
                atualiza_helicoptero(&lazer, &helicoptero, &frame_helic, screenSizes, transicao_frame);
                
                // Colisao com lazer: ao fim dos frames, se player no lazer
                if( frame_helic == max_frames_helic - 30 ) {
                    for(int i = 0; i < player_qtd; i++) {
                        if ( vidas[i] > 0 && colisao[i] == 0 && (
                            CheckCollisionLines( //colisao lazer e lado esq player
                                lazer.start, lazer.end, 
                                (Vector2){player[i].x, player[i].y}, 
                                (Vector2){player[i].x, player[i].y + player[i].height},
                                &buffer_v2
                            ) ||
                            CheckCollisionLines( //colisao lazer e lado dir player
                                lazer.start, lazer.end, 
                                (Vector2){player[i].x + player[i].width, player[i].y}, 
                                (Vector2){player[i].x + player[i].width, player[i].y + player[i].height},
                                &buffer_v2
                            ))
                        ){
                            //conta colisao
                            colisao[i] = colisao_max;
                        }
                    }
                }
            }
            if (fase >= 4) {


                
            }
            
            for(int i = 0; i < player_qtd; i++) {
                
                if( vidas[i] > 0 ) {
                
                    // Buracos
                    if( colisao[i] == 0 && CheckCollisionCircleRec(buraco_obj.pos, buraco_obj.radius, player[i])) {
                        colisao[i] = colisao_max;
                    }
                
                    // Veiculos
                    // Verifica colisao, se houver remove player do carro e conta a colisao
                    char collision_check = colisao_veiculos(
                        Veiculos, 
                        &player[i], 
                        colided_left_right[i], 
                        &camera.target.x, 
                        unidade
                    );
                    if(collision_check && colisao[i] == 0) {
                        colisao[i] = colisao_max;
                    }
                    else if(collision_check) {
                        PlaySound(ColisaoCarro);
                    }
                    
                    // Paredes
                    if (player[i].x <= left_wall) {
                        PlaySound(ColisaoCarro);
                        if(colisao[i] == 0) {
                            colisao[i] = colisao_max;
                        }
                        colided_left[i] += 6;
                        camera.target.x -= unidade * 18;
                    }
                    else if (player[i].x + player[i].width >= right_wall) {
                        PlaySound(ColisaoCarro);
                        if(colisao[i] == 0) {
                            colisao[i] = colisao_max;
                        }
                        colided_right[i] += 6;
                        camera.target.x += unidade * 18;
                    }
                    
                    //contabiliza mexida da tela por colisoes
                    if (colided_left[i]  > 0) {colided_left[i]--;  player[i].x +=  unidade * 3; player[i].y++; camera.target.x +=  unidade * 3;}
                    if (colided_right[i] > 0) {colided_right[i]--; player[i].x -=  unidade * 3; player[i].y++; camera.target.x -=  unidade * 3;}
                    
                    // Verifica perda de vida
                    if(colisao[i] == colisao_max) {
                        vidas[i]--;
                        pontuacao[i] -= 50;
                    }
                    
                    //Se colidiu
                    if (colisao[i] > 0) {
                        // Contador
                        colisao[i]--;
                    }
                    
                    
                    //verifica colisoes com topo e base da tela
                    colisao_topoebase(&player[i], bordas);
                    
                }
            }

            
            // Camera zoom controls
            camera.zoom += ((float)GetMouseWheelMove()*0.05f);

            if (camera.zoom > 1.0f) camera.zoom = 1.0f;
            else if (camera.zoom < 0.01f) camera.zoom = 0.01f;

            
            //atualiza string com numeros de veiculos na tela
            int veiculos_na_tela[3] = { 0, 0, 0 };
            //conta veiculos na tela
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < Veiculos[i].qtd; j++) {
                    if(Veiculos[i].lista[j].x > 0) {
                        veiculos_na_tela[i]++;
                    }
                }
                //atualiza string com contador
                snprintf(na_tela_str[i], 4, "%i %i", i, veiculos_na_tela[i]);
            }
            for(int i = 0; i < player_qtd; i++) {
                
                if( vidas[i] > 0 ) {
                    
                    //atualiza string com vidas
                    snprintf(vidas_string[i], 4, "%i", vidas[i]);
                    
                    pontuacao[i] += 0.2;
                    //atualiza string de pontuacao
                    snprintf(pontuacao_str[i], 32, "pontação%i: %.0f", i + 1, pontuacao[i]);
                    
                }
                else if( vidas[i] == 0 ) {
                    //atualiza string com vidas
                    snprintf(vidas_string[i], 4, "%i", vidas[i]);
                    //atualiza string de pontuacao
                    snprintf(pontuacao_str[i], 32, "pontação%i: %.0f", i + 1, pontuacao[i]);
                    vidas[i]--;
                }
            }
            
            
            // Atualiza animacoes em sprite sheet
            atualiza_animacoes(Animacoes, animacoes_qtd, global_fps);
            
            
            //updates screen fade overlay
            fade_to(&fade_frame, fade_speed, &fade_cor, fade_src, fade_dst, screenSizes);
            
            
            //conserta partes do jogo apos tutorial
            if(modo_de_jogo == 0) {
                for(int i = 0; i < 3;i ++) {
                    Veiculos[i].qtd = veiculos_qtds[i];
                }
                fase = 0;
                //tutorial(&tutorial_frame, Veiculos, &buraco_obj, &frame_helic);
            }
            
            
            //----------------------------------------------------------------------------------
        }
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            BeginMode2D(camera);
            
            
                // Desenha fundo
                DrawTextureEx(fundo[fase - 1], (Vector2){ -unidade * 30, fundo1y }, 0, expansao, WHITE);
                DrawTextureEx(fundo[fase - 1], (Vector2){ -unidade * 30, fundo2y }, 0, expansao, WHITE);
                
                
                // Desenha buraco na rua
                //DrawCircleV(buraco_obj.pos, buraco_obj.radius, PINK);
                DrawTexturePro(
                    buraco.texture,
                    buraco.source,
                    buraco.dest,
                    (Vector2) {0,0}, 0, WHITE
                );
                
                
                //desenha textura (e talvez hitbox) dos veiculos na tela
                desenha_veiculos(Veiculos, fase);
                
                
                // Printa players
                for(int i = 0; i < player_qtd; i++) {
                    
                    if(vidas[i] > 0 && (colisao[i] == 0 || colisao[i] % 2 == 0) ) {
                        
                        //DrawRectangleRec(player[i], RED);
                        
                        
                        DrawTexturePro(
                            Veiculos[1].texturas[0][0],
                            (Rectangle) {0, 0, Veiculos[1].texturas[0][0].width, Veiculos[1].texturas[0][0].height},
                            (Rectangle) {
                                player[i].x - player[i].width * 0.75,
                                player[i].y - player[i].height * 0.25,
                                player[i].width * 2.5,
                                player[i].height * 1.5
                            },
                            (Vector2) {0,0}, 0, 
                            cores_moto[i]
                        );
                        
                    }
                }
                
                if(transicao_frame) {
                    DrawTextureEx(tunel[(fase - 1) / 2] , (Vector2){-screenWidth / 6+ 20  ,tunel_y  - 50} , 0, 4.5, WHITE);
                }
                
                if(frame_helic) {
                    
                    // Printa lazer helicoptero
                    DrawLineEx(lazer.start, lazer.end, lazer.thick, (Color){255, 0, 0, 255});
                    
                    // Printa helicoptero
                    DrawTexturePro(
                        helicoptero.texture,
                        helicoptero.source,
                        helicoptero.dest,
                        (Vector2) {helicoptero.dest.width / 2.0f, helicoptero.dest.height / 2.0f},
                        ((lazer.move.y * 100.0f) / (lazer.move.x * 100.0f)) * 57.3f, 
                        WHITE
                    );
                    
                }

            EndMode2D();
            
            


            //printa texto
            DrawText("FUJA DO THE HUXLEY", 150, 20, 30, LIGHTGRAY);
            //printa vidas e pontuacao
            DrawRectangle(15, 45, 120, 650, (Color){230, 230, 230, 200});
            DrawRectangle( screenWidth * 4 / 5 + 10, 15, 260, 150, (Color){30, 30, 30, 200});
            for(int i = 0; i < player_qtd; i++) {
                DrawText(vidas_str_base[i], 20, 50 + 170 * i, 30, RED);
                DrawText(vidas_string[i],   40, 80 + 170 * i, 120, RED);
                //printa pontuacao
                DrawText(pontuacao_str[i], screenWidth * 4 / 5 + 15, 20 + 30 * i, 30, WHITE);
            }
            // coloca n de veiculos na tela
            for(int i = 0; i < 3; i++) {
                DrawText(na_tela_str[i], 600, 30 * (i + 1), 20, BLACK);
            }
            
            if(fade_cor.a) {
                //draws screen fade
                DrawRectangleRec((Rectangle) { 0, 0, screenSizes[0], screenSizes[1] }, fade_cor );
            }
            
            
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization / free
    //--------------------------------------------------------------------------------------
    
    //Unload texturas
    //fundos
    UnloadTexture(fundo[0]);
    UnloadTexture(fundo[1]);
    UnloadTexture(fundo[2]);
    UnloadTexture(fundo[3]);
    
    //tuneis
    UnloadTexture(tunel[0]);
    UnloadTexture(tunel[1]);
    
    UnloadTexture(pendrive_sprite);
    
    //ostáculos
    // buraco
    UnloadTexture(buraco_sprite);
    // helicoptero
    UnloadTexture(helicoptero_sprite);
    // carros, caminhoes, motos
    //  carros
    for(int i = 0; i < carros.qtd; i++) {
        //carros cyberverso de 1 a 6
        UnloadTexture(carros.texturas[0][i]);
    }
    for(int i = 0; i < carros.qtd; i++) {
        //carros mundo real de 1 a 6
        UnloadTexture(carros.texturas[1][i]);
    }
    //  motos
    UnloadTexture(motos.texturas[0][0]);
    //  caminhoes
    for(int i = 0; i < caminhoes.qtd; i++) {
        //caminhoes cyberverso de 1 a 4
        UnloadTexture(caminhoes.texturas[0][i]);
    }
    for(int i = 0; i < caminhoes.qtd; i++) {
        //caminhoes mundo real de 1 a 4
        UnloadTexture(caminhoes.texturas[1][i]);
    }
    
    
    //Unload Audio
    UnloadMusicStream(Cyberverso);
    UnloadMusicStream(Creditos);
    UnloadMusicStream(Infinito);
    UnloadMusicStream(Menu);
    UnloadMusicStream(MundoReal);
    UnloadMusicStream(Tutorial);
    UnloadMusicStream(Helicoptero);
    UnloadSound(ColisaoCarro);
    UnloadSound(Pendrive);
    UnloadSound(TiroHelicoptero);
    UnloadSound(TiroTanque);
    UnloadSound(Teclado);
    
    //--------------------------------------------------------------------------------------
    // Close audio device (music streaming is automatically stopped)
    CloseAudioDevice();
    
    // Close window and OpenGL context
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}

void menu_salve(int *player_qtd,int *fechar,int *modo, Music *musica_menu) { 
    //vao vim da main
    //int cor[4] = {-1, -1, -1, -1};
    int screen[2];
    screen[0] = GetMonitorWidth(GetCurrentMonitor()); 
    screen[1] = GetMonitorHeight(GetCurrentMonitor());
    
    //InitAudioDevice();
    UpdateMusicStream(musica_menu[3]);
    PlayMusicStream(musica_menu[3]);
    //CloseAudioDevice();

    
    Texture2D fundos[8];   
    fundos[0] = LoadTexture("assets/backgrounds/TI_The_Huxley.png");
    fundos[1] = LoadTexture("assets/backgrounds/Creditosf.png");
    fundos[2] = LoadTexture("assets/backgrounds/Highscoresf.png");
    fundos[3] = LoadTexture("assets/backgrounds/roubosfErrados.png");
    fundos[4] = LoadTexture("assets/backgrounds/selecao_jogf.png");
    fundos[5] = LoadTexture("assets/backgrounds/roubosfCertos.png");
    fundos[6] = LoadTexture("assets/backgrounds/fundomr1.png");
    fundos[7] = LoadTexture("assets/Obstaculos/moto.png");
    
    SetTargetFPS(60);
    char ganhou_ou_nao = 1;
    
    int botao_atual = 0;
    //vetor char que será retornado a main
    int informacao[5] = {0, -1, -1, -1, 1};
    
    
    //declarando os botoes
    int botoes_qtdd = 12;    
    
    
    
    Botao botoes[12] = {
        
        //botoes do menu principal
        {// botão 0
            {0, -1, -1, -1, 1}, 
            "Enviar resposta", 
            BLUETHE,
            1,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+135.0f, (screen[1]/2 - fundos[0].height/2)+255.0f, 243.0f, 19.0f}  
        }, 
        {// botão 1
            {1, -1, -1, -1, 1},
            "Créditos",
            LIGHTGRAY,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+379.0f, (screen[1]/2 - fundos[0].height/2)+255.0f, 243.0f, 19.0f}
        }, 
        {// botão 2
            {2, -1, -1, -1, 1},
            "Highscores",
            LIGHTGRAY,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+623.0f, (screen[1]/2 - fundos[0].height/2)+255.0f, 243.0f, 19.0f}
        }, 
        {// botão 3
            {3, -1, -1, -1, 1},
            "Roubar casos testes",
            DARKBLUE,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+556.0f, (screen[1]/2 - fundos[0].height/2)+675.0f, 143.0f, 21.0f}
        },
        {// botão 4
            {-1, -1, -1, -1, 0},
            "Sair",
            GREENTHE,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+701.0f, (screen[1]/2 - fundos[0].height/2)+675.0f, 143.0f, 21.0f}
        },
        
        //botoes do secundário
        {// botão 5
            {4, 1, -1, -1, 1}, 
            "./finito", 
            BLACK,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+143.0f, (screen[1]/2 - fundos[0].height/2)+609.0f, 356.0f, 21.0f}
        },
        {// botão 6
            {4, 2, -1, -1, 1},
            "./infinito",
            BLACK,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+143.0f, (screen[1]/2 - fundos[0].height/2)+630.0f, 356.0f, 21.0f}
        },
        {// botão 7
            {4, 0, -1, -1, 1}, 
            "./tutorial",
            BLACK,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+143.0f, (screen[1]/2 - fundos[0].height/2)+651.0f, 356.0f, 21.0f}
        },
        {// botão 8
            {0, -1, -1, -1, 1},
            "./voltar",
            BLACK,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+143.0f, (screen[1]/2 - fundos[0].height/2)+672.0f, 356.0f, 21.0f}
        },
        
        //botoes da aba selecionar jogadores
        {// botão 9
            {3, -1, -1, -1, 1},
            "voltar",
            GRAY,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+701.0f, (screen[1]/2 - fundos[0].height/2)+675.0f, 143.0f, 21.0f}
        },
        {// botão 10
            {4, *modo, 0, -1, 1},
            "",
            GRAY,
            0,
            (Rectangle) {0.0f, 0.0f, 0.0f, 0.0f}
        },
        {// botão 11
            {-1, *modo, 0, 1, 1},
            "START",
            GREENTHE,
            0,
            (Rectangle) {(screen[0]/2 - fundos[0].width/2)+556.0f, (screen[1]/2 - fundos[0].height/2)+675.0f, 143.0f, 21.0f}
        }  
    };


    //declarando abas
    
    
    aba abas_menu[5] = {
        {// aba 0 -- menu principal
            fundos[0],               
            5, {0, 1, 2, 3, 4, -1, -1, -1}
        },
        {// aba 1 -- créditos
            fundos[1],              
            3, {0, 1, 2, -1, -1, -1, -1, -1}    
        },
        {// aba 2 -- highscores
            fundos[2],
            5, {0, 1, 2, 3, 4, -1, -1, -1}
        },
        {// aba 3 -- terminal
            fundos[3],
            7, {0, 1, 2, 5, 6, 7, 8, -1}
        },
        {// aba 4 -- seleção de jogadores
            fundos[4],
            3, {9, 10, 11, -1, -1, -1, -1, -1}
        }
    };  
    
    // Expansao da texturra para preencher a tela
    float expansao = ((float) screen[0]) / ((float)fundos[6].width);
    // Altura da textura apos expansao
    int fundos6_height = fundos[6].height * expansao / 4;
    // Posicao das duas texturas em loop
    float fundo1y = - ((float)fundos6_height) * 0.5f;
    float fundo2y = - ((float)fundos6_height) * 1.5f;
    // Posicao em que testuras resetam loop
    int fim_do_fundo = fundos6_height * 1.5f;
    
    //variavel que determina a velocidade da tela
    float screen_speed = 0.2 * expansao;

    //-------------------------------------------------------------------------------------------
    /* se ganhou coloca casos certos no lugar dos errados.
    if((*ganhou_ou_nao == 1) {
        abas_menu[3].fundo = fundos[5];
    } */
    
    
    (*fechar) = 0;
    
    while (!WindowShouldClose() && informacao[3] == -1 && informacao[4] == 1) {

        for(int i = 0; i < botoes_qtdd; i++) {      
            for(int y = 0; y < abas_menu[informacao[0]].botoes_qtd; y++) {
            //colocar isso dentro de um for e um if dps para saber se tem esse botao na aba
                if(abas_menu[informacao[0]].botoes_id[y] == i) {
          
                    // se mouse sobre botao
                    if (CheckCollisionPointRec(GetMousePosition(), botoes[i].retangulo)) {
                        
                        botoes[i].apertado = 1;
                        
                        // se hover
                        if(i >= 0 && i <= 2) {
                            botoes[i].coloracao = BLUETHE;
                        }
                        else if(i >= 5 && i <= 8) {
                            botoes[i].coloracao = WHITE;
                        }
                        else if(i == 9 || i==10) {
                            botoes[i].coloracao = BLUETHE;
                        }
                        else if(i == 11) {
                            botoes[i].coloracao = MAROON;
                        }
                          
                        // se apertou botao
                        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                            botao_atual = i;  
                            // atualizando valores da aba, cor, modo, começar_jogo e r
                            if( botoes[i].acoes[0] >= 0 && botoes[i].acoes[0] <= 4 ) {                        
                                informacao[0] = botoes[i].acoes[0];
                            }
                            if( botoes[i].acoes[1] >= 0 && botoes[i].acoes[1] <= 2 ) {
                                informacao[1] = botoes[i].acoes[1];
                            }
                            if( botoes[i].acoes[2] >= 0 && botoes[i].acoes[0] <= 4 ) {
                                informacao[2] = botoes[i].acoes[2];
                            }
                            if( botoes[i].acoes[3] == 1 ) {
                                informacao[3] = botoes[i].acoes[3];
                            }
                            if( botoes[i].acoes[4] == 0 ) {
                                informacao[4] = botoes[i].acoes[4];
                            }                    
                        }                
                    }
                    // se nao houver
                    else {
                        
                        botoes[i].apertado = 0;
                        
                        if(i >= 0 && i <= 2)  {
                            botoes[i].coloracao = LIGHTGRAY;
                        }
                        else if(i >= 5 && i <= 8) {
                            botoes[i].coloracao = BLACK;
                        }
                        else if(i == 9 || i==10) {
                            botoes[i].coloracao = GRAY;
                        }
                        else if(i == 11) {
                            botoes[i].coloracao = GREENTHE;
                        }              
                    }
                }
            }
        }
        
        //salvando cores do botao atual (após teclado e mouse)
        if(botao_atual >= 0 && botao_atual <= 2) {
            botoes[botao_atual].coloracao = BLUETHE;
        }
        else if(botao_atual == 4) {
            (*fechar) = 1;
        }
        else if(botao_atual >= 5 && botao_atual <= 8) {
            botoes[botao_atual].coloracao = WHITE;
        }
        else if(botao_atual == 9 || botao_atual ==10) {
            botoes[botao_atual].coloracao = BLUETHE;
            if(botao_atual == 9) {
                (*player_qtd) = 1;
            }
        }
        else if( botao_atual == 11) {
            botoes[botao_atual].coloracao = MAROON;
        }

        //salvando as acoes dos botoes
        for( int t = 0; t < 5; t++ ) {
            informacao[t] = botoes[botao_atual].acoes[t];
        }
        if(informacao[0]==4) {
            if(IsKeyPressed(KEY_ENTER)) {
                (*player_qtd)++;
            }
        }
        (*modo) =  informacao[1];
        //mecanica de casos especiais.... 
        //botão 10
      
        //agr que ja sei em qual botão apertei posso comecar a printar as coisas
        //basicamente, há 5 abas que irão ser desenhadas
      
        if((*fechar) != 1) {    
            BeginDrawing();
                ClearBackground(THENEON);
                if(informacao[0] == 0) { //menu principal
                        
                    fundo1y += screen_speed * 2;
                    fundo2y += screen_speed * 2;
                
                    //loop do fundo
                    if(fundo1y + fundos6_height >= fim_do_fundo) {
                        fundo1y = fundo2y - fundos6_height;
                    }
                    if(fundo2y + fundos6_height >= fim_do_fundo) {
                        fundo2y = fundo1y - fundos6_height;
                    }
                    
                    // Desenha fundo
                    DrawTextureEx(fundos[6], (Vector2){(screen[0]/2 - fundos[0].width/2)+124, fundo1y }, 0, 0.65, WHITE);
                    DrawTextureEx(fundos[6], (Vector2){(screen[0]/2 - fundos[0].width/2)+124 , fundo2y }, 0, 0.65, WHITE);
                    
                    
                    DrawRectangleRec((Rectangle) {( screen[0]/2 - fundos[0].width/2), 0, 965, (screen[1]/2 -fundos[0].height/2) + 100}, THENEON);
                    DrawRectangleRec((Rectangle) {( screen[0]/2 - fundos[0].width/2), (screen[1]/2 -fundos[0].height/2)+ fundos[0].height - 30, 965, (screen[1]/2 -fundos[0].height/2) + 100 }, THENEON);
                    //desenha a textura do The_huxley_TI
                    DrawTexture(fundos[0], (screen[0]/2 - fundos[0].width/2), (screen[1]/2 - fundos[0].height/2)+30, WHITE);
                    
                }
                else if(informacao[0] == 1) { //créditos
                        
                        //fundo The Huxley créditos
                        DrawTexture(fundos[1],(screen[0]/2 - fundos[1].width/2), (screen[1]/2 - fundos[1].height/2)+30, WHITE);
                  
                        
                          
                }
                else if(informacao[0] == 2) {  //Highscores
        
                        //fundo The Huxley highscores
                        DrawTexture(fundos[2], (screen[0]/2 - fundos[2].width/2), (screen[1]/2 - fundos[1].height/2)+30, WHITE);
                        //os textos do arquivo
                       
                             
                }
                else if(informacao[0] == 3) { //terminal
                    //desenha a rua
                    fundo1y += screen_speed * 2;
                    fundo2y += screen_speed * 2;
                
                    //loop do fundo
                    if(fundo1y + fundos6_height >= fim_do_fundo) {
                        fundo1y = fundo2y - fundos6_height;
                    }
                    if(fundo2y + fundos6_height >= fim_do_fundo) {
                        fundo2y = fundo1y - fundos6_height;
                    }
                    
                    // Desenha fundo
                    DrawTextureEx(fundos[6], (Vector2){(screen[0]/2 - fundos[0].width/2)+124, fundo1y }, 0, 0.65, WHITE);
                    DrawTextureEx(fundos[6], (Vector2){(screen[0]/2 - fundos[0].width/2)+124 , fundo2y }, 0, 0.65, WHITE);
                    
                    //concerta a rebarba
                    DrawRectangleRec((Rectangle) {( screen[0]/2 - fundos[0].width/2), 0, 965, (screen[1]/2 -fundos[0].height/2) + 100}, THENEON);
                    DrawRectangleRec((Rectangle) {( screen[0]/2 - fundos[0].width/2), (screen[1]/2 -fundos[0].height/2)+ fundos[0].height - 30, 965, (screen[1]/2 -fundos[0].height/2) + 100 }, THENEON);
                    if(ganhou_ou_nao == 1) {
                        DrawTexture(fundos[5], (screen[0]/2 - fundos[5].width/2), (screen[1]/2 - fundos[5].height/2)+30, WHITE);
                    }
                    else if(ganhou_ou_nao == 0) {
                        DrawTexture(fundos[3], (screen[0]/2 - fundos[3].width/2), (screen[1]/2 - fundos[3].height/2)+30, WHITE);
                    }                                         
                }
                else if(informacao[0] == 4) { //selecionar jogadores
                        
                    //if(IsKeyPressed(KEY_ENTER)) {
                            
                    //fundo
                    DrawTexture(fundos[4],(screen[0]/2 - fundos[3].width/2), (screen[1]/2 - fundos[3].height/2)+30, WHITE);
                        
                    if((*player_qtd) >= 1) {
                        DrawRectangleRec((Rectangle) {(screen[0]/2 - fundos[3].width/2) + 202 , (screen[1]/2 - fundos[3].height/2)+323, 56, 56}, SKYBLUE);        
                        DrawTextureEx(fundos[7], (Vector2) {(screen[0]/2 - fundos[3].width/2) + 190 , (screen[1]/2 - fundos[3].height/2)+530}, 0 ,0.35, SKYBLUE);
                        if((*player_qtd) >= 2) {
                            DrawRectangleRec((Rectangle) {(screen[0]/2 - fundos[3].width/2) + 383 , (screen[1]/2 - fundos[3].height/2)+323, 56, 56}, GREEN);  
                            DrawTextureEx(fundos[7], (Vector2) {(screen[0]/2 - fundos[3].width/2) + 370 , (screen[1]/2 - fundos[3].height/2)+530}, 0 ,0.35, GREEN);
                            if((*player_qtd) >= 3) {
                                DrawRectangleRec((Rectangle) {(screen[0]/2 - fundos[3].width/2) + 561 , (screen[1]/2 - fundos[3].height/2)+323, 56, 56}, RED);
                                DrawTextureEx(fundos[7], (Vector2) {(screen[0]/2 - fundos[3].width/2) + 547 , (screen[1]/2 - fundos[3].height/2)+530}, 0 ,0.35, RED);                                                      
                                if((*player_qtd)== 4) {
                                    DrawRectangleRec((Rectangle) {(screen[0]/2 - fundos[3].width/2) + 743 , (screen[1]/2 - fundos[3].height/2)+323, 56, 56}, DARKPURPLE);
                                     DrawTextureEx(fundos[7], (Vector2) {(screen[0]/2 - fundos[3].width/2) + 727 , (screen[1]/2 - fundos[3].height/2)+530}, 0 ,0.35, DARKPURPLE);
                                }
                            }                                    
                        }
                    }
                    //ainda n tenho as coisas certas... preciso da arte... vou fazer quando acordar...
                }
                else { //sair
                  
                    //unload nas imagens
                    for(int tam = 0 ; tam < 8; tam++) {
                        UnloadTexture(fundos[tam]);
                    }
                }  
                
        
                //desenhando botoes
                for(int x = 0; x < botoes_qtdd; x++) {
                    for(int y = 0; y < abas_menu[informacao[0]].botoes_qtd; y++) {
                        if(abas_menu[informacao[0]].botoes_id[y] == x) {
                            Color colo;
                            DrawRectangleRec(botoes[x].retangulo, botoes[x].coloracao);
                            
                            if((x>=0 && x<=4) || (x>=9 && x<=11)) {
                                colo = (botoes[x].apertado == 1) ? WHITE : BLACK;
                            }
                            else {
                                colo = (botoes[x].apertado == 1) ? BLACK : WHITE;
                            }
                            
                            DrawText(
                                      botoes[x].texto, 
                                      (int) (botoes[x].retangulo.x + botoes[x].retangulo.width/2 - MeasureText(botoes[x].texto, 10)/2), 
                                      (int) (botoes[x].retangulo.y + 6), 10, colo);
                        }
                    }
                }
            EndDrawing();
        }
    }
          
    //unload nas imagens
    for(int tam = 0; tam< 8; tam++) {
        UnloadTexture(fundos[tam]);
    }    
        

}    

//------------------------------------------------------------------------------------