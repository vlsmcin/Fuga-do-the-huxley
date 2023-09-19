//------------------------------------------------------------------------------------
#define BLUETHE (Color){ 5, 173, 239, 255 } 
#define THENEON (Color){ 207, 216, 242, 255 }
#define GREENTHE (Color){ 116, 173, 38,  255 }
// arquivo com todas as structs

typedef struct {
    int acoes[5]; // vetor com informações sobre a função do botão
    char texto[32]; // texto do botão
    Color coloracao; // cor atual do botão
    int apertado;
    Rectangle retangulo; // retangulo do botão
} Botao;

typedef struct {
    Texture2D fundo; // textura do fundo (do The huxley)
    int botoes_qtd; // quantidade de botões na aba
    int botoes_id[8]; //quais são os botões na aba
} aba;

typedef struct {
    Rectangle *lista; //vetor q armazena elementos da colecao
    int qtd; //inteiro que armazena numero de elementos da colecao
    int speed; //multiplicador de velocidade do veiculo
    float ocupacao; //fracao de faixas ocupadas por veiculo

    Texture2D *texturas[2]; //vetor q armazena texturas da colecao do cyberverso

} colecao;

typedef struct {
  char nome[4];
  long int pontuacao;
} Pontuacoes;

typedef struct {
    
    Texture2D texture; //textura que armazena todos os frames da animacao
    
    Rectangle source;
    Rectangle dest;
    
    int frame_qtd;     //numero de frames na animacao
    int frame_curr;    //frame atual na animacao
    
    int frame_counter; //contador de frames do jogo
    int fps;         //numero de frames da animacao por segundo
    
} Animacao;

typedef struct {
    Vector2 pos;
    float radius;
} Circle;

typedef struct {
    Vector2 start;
    Vector2 end;
    float thick;
    Vector2 move;
} Line;

//------------------------------------------------------------------------------------