


void desenha_veiculos(colecao Veiculos[], int fase) 
{

    //desenha textura dos carros
    for (int i = 0; i < Veiculos[0].qtd; i++) {
        DrawTexturePro(
            Veiculos[0].texturas[(fase - 1) / 2][i], 
            (Rectangle) {0, 0, Veiculos[0].texturas[(fase - 1) / 2][i].width, Veiculos[0].texturas[(fase - 1) / 2][i].height},
            (Rectangle) {
                Veiculos[0].lista[i].x - Veiculos[0].lista[i].width * 0.3,
                Veiculos[0].lista[i].y - Veiculos[0].lista[i].height * 0.2,
                Veiculos[0].lista[i].width * 1.6,
                Veiculos[0].lista[i].height * 1.4
            },
            (Vector2) {0,0}, 0, WHITE
        );
    }
    //desenha textura dos caminhoes
    //caminhao 0
    DrawTexturePro(
        Veiculos[2].texturas[(fase - 1) / 2][0], 
        (Rectangle) {0, 0, Veiculos[2].texturas[(fase - 1) / 2][0].width, Veiculos[2].texturas[(fase - 1) / 2][0].height},
        //Veiculos[2].lista[i],
        
        (Rectangle) {
            Veiculos[2].lista[0].x - Veiculos[2].lista[0].width * 0.15,
            Veiculos[2].lista[0].y - Veiculos[2].lista[0].height * 0,
            Veiculos[2].lista[0].width * 1.3,
            Veiculos[2].lista[0].height * 1
        },
        
        (Vector2) {0,0}, 0, WHITE
    );
    
    //caminhao 1 onibus
    DrawTexturePro(
        Veiculos[2].texturas[(fase - 1) / 2][1], 
        (Rectangle) {0, 0, Veiculos[2].texturas[(fase - 1) / 2][1].width, Veiculos[2].texturas[(fase - 1) / 2][1].height},
        //Veiculos[2].lista[i],
        
        (Rectangle) {
            Veiculos[2].lista[1].x - Veiculos[2].lista[1].width * 0.1,
            Veiculos[2].lista[1].y - Veiculos[2].lista[1].height * 0.15,
            Veiculos[2].lista[1].width * 1.2,
            Veiculos[2].lista[1].height * 1.3
        },
        
        (Vector2) {0,0}, 0, WHITE
    );
    
    //caminhao 2 caminhao
    DrawTexturePro(
        Veiculos[2].texturas[(fase - 1) / 2][2], 
        (Rectangle) {0, 0, Veiculos[2].texturas[(fase - 1) / 2][2].width, Veiculos[2].texturas[(fase - 1) / 2][2].height},
        //Veiculos[2].lista[i],
        
        (Rectangle) {
            Veiculos[2].lista[2].x - Veiculos[2].lista[2].width * 0.2,
            Veiculos[2].lista[2].y - Veiculos[2].lista[2].height * 0.05,
            Veiculos[2].lista[2].width * 1.4,
            Veiculos[2].lista[2].height * 1.1
        },
        
        (Vector2) {0,0}, 0, WHITE
    );
    
    //caminhao 3 guicho
    DrawTexturePro(
        Veiculos[2].texturas[(fase - 1) / 2][3], 
        (Rectangle) {0, 0, Veiculos[2].texturas[(fase - 1) / 2][3].width, Veiculos[2].texturas[(fase - 1) / 2][3].height},
        //Veiculos[2].lista[i],
        
        (Rectangle) {
            Veiculos[2].lista[3].x - Veiculos[2].lista[3].width * 0.5,
            Veiculos[2].lista[3].y - Veiculos[2].lista[3].height * 0.2,
            Veiculos[2].lista[3].width * 2,
            Veiculos[2].lista[3].height * 1.4
        },
        
        (Vector2) {0,0}, 0, WHITE
    );
    
    //desenha textura das motos
    DrawTexturePro(
        Veiculos[1].texturas[0][0],
        (Rectangle) {0, 0, Veiculos[1].texturas[0][0].width, Veiculos[1].texturas[0][0].height},
        (Rectangle) {
            Veiculos[1].lista[0].x - Veiculos[1].lista[0].width * 0.75,
            Veiculos[1].lista[0].y - Veiculos[1].lista[0].height * 0.25,
            Veiculos[1].lista[0].width * 2.5,
            Veiculos[1].lista[0].height * 1.5
        },
        (Vector2) {0,0}, 0,
        (Color) {200, 150, 100, 255}
    );
    DrawTexturePro(
        Veiculos[1].texturas[0][0],
        (Rectangle) {0, 0, Veiculos[1].texturas[0][0].width, Veiculos[1].texturas[0][0].height},
        (Rectangle) {
            Veiculos[1].lista[1].x - Veiculos[1].lista[1].width * 0.75,
            Veiculos[1].lista[1].y - Veiculos[1].lista[1].height * 0.25,
            Veiculos[1].lista[1].width * 2.5,
            Veiculos[1].lista[1].height * 1.5
        },
        (Vector2) {0,0}, 0, 
        (Color) {200, 150, 100, 255}
    );
    
}