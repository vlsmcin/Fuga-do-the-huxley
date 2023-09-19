//------------------------------------------------------------------------------------

void atualiza_veiculos(colecao Veiculos[], float screen_speed, const int screenSizes[], int transicao_frame)
{
    //screenSizes é screenWidth screenHeight 
    
    //vetor que conta veiculos na tela
    int veiculos_na_tela[3] = { 0, 0, 0 };
    //conta veiculos na tela
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < Veiculos[i].qtd; j++) {
            if(Veiculos[i].lista[j].x > 0) {
                //soma veiculo se estiver na tela
                veiculos_na_tela[i]++;
            }
        }
    }
    
    
    //numero de faixas do jogo
    int faixas = 4;
    
    
    //variaveis para facilitar aritmetica
    int borda = screenSizes[0] / 6;
    int largura_veiculo;
    int separacao;
    
    
    // Atualiza veiculos
    
    //atualiza carros e caminhoes primeiro
    for(int v = 0; v < 3; v += 2) {
        //atualiza largura do veiculo e separacao entre eles
        largura_veiculo = Veiculos[v].lista[0].width;
        separacao = (screenSizes[0] - borda * 2 - faixas * largura_veiculo) / (faixas + 1);
        
        //para cada veiculo na colecao
        for(int i = 0; i < Veiculos[v].qtd; i++) {
            
            //movimenta veiculo
            Veiculos[v].lista[i].y += screen_speed * Veiculos[v].speed;

            //veiculo sendo verificado, para facilitar calculos
            Rectangle vvi = Veiculos[v].lista[i];
            int w = screenSizes[0];
            
            //evita que caminhoes atropelem carros na tela ou caminhoes deixando margem de erro
            if( vvi.x > 0 && v == 2 ) {
                
                //carros
                for(int j = 0; j < Veiculos[0].qtd; j++) {
                    
                    if (CheckCollisionRecs( 
                        (Rectangle) {vvi.x, vvi.y - w / 40,vvi.width, vvi.height + w / 20}, 
                        Veiculos[0].lista[j])
                    ){
                        Veiculos[v].lista[i].y += Veiculos[v].speed + screen_speed;
                    }
                }
                //caminhoes
                for(int j = 0; j < Veiculos[2].qtd; j++) {
                    
                    if (i != j &&
                        CheckCollisionRecs( 
                        (Rectangle) {vvi.x, vvi.y - w / 40,vvi.width, vvi.height + w / 20}, 
                        Veiculos[2].lista[j])
                    ){
                        Veiculos[v].lista[i].y += Veiculos[v].speed + screen_speed;
                    }
                }
            }
            
            //se Sair da tela e Estiver na garagem
            if (Veiculos[v].lista[i].y >= screenSizes[1] && Veiculos[v].lista[i].x < 0){
                // se nao estiver na transicao, randomiza e limita
                if( !transicao_frame && GetRandomValue(0, 1) && (float)veiculos_na_tela[v] < (float)faixas * Veiculos[v].ocupacao) {
                    //manda para tela
                    veiculos_na_tela[v]++;
                    Veiculos[v].lista[i].y = -Veiculos[v].lista[i].height - GetRandomValue(0, 100) * 10;
                    Veiculos[v].lista[i].x = borda + separacao + GetRandomValue(0, faixas - 1) * (separacao + largura_veiculo);
                    
                    //evita spawnar veiculos secantes (se atropelando)
                    for(int v2 = 0; v2 < 3; v2 += 2) {
                        for(int j = 0; j < Veiculos[v2].qtd; j++) {
                            //se veiculos diferentes, colidindo
                            if( (v != v2||i != j) && CheckCollisionRecs(Veiculos[v].lista[i], Veiculos[v2].lista[j]) ) {
                                Veiculos[v].lista[i].y -= screenSizes[1];
                            }
                        }
                    }
                }
                else {
                    //mantem na garagem
                    Veiculos[v].lista[i].y = -Veiculos[v].lista[i].height;
                    Veiculos[v].lista[i].x = -screenSizes[0] -Veiculos[v].lista[i].width;
                }
            }
            //se Sair da tela e Não estiver na garagem
            else if (Veiculos[v].lista[i].y >= screenSizes[1] && Veiculos[v].lista[i].x > 0){
                //manda pra garagem
                veiculos_na_tela[v]--;
                Veiculos[v].lista[i].y = -Veiculos[v].lista[i].height;
                Veiculos[v].lista[i].x = -screenSizes[0] -Veiculos[v].lista[i].width;
            }
        }
    }
    
    
    // Motos
    //atualiza largura do veiculo e separacao entre eles
    largura_veiculo = Veiculos[1].lista[0].width;
    separacao = (screenSizes[0] - borda * 2 - largura_veiculo * 2 - largura_veiculo * (faixas - 1)) / (faixas);
    
    int posicoes_motos[faixas + 1];
    posicoes_motos[0] = borda;
    posicoes_motos[faixas] = screenSizes[0] - borda - largura_veiculo;
    
    for(int i = 1; i < faixas; i++) {
        posicoes_motos[i] = borda + largura_veiculo + separacao + (i - 1) * (largura_veiculo + separacao);
    }
    
    //para cada moto
    for(int i = 0; i < Veiculos[1].qtd; i++) {
        
        //movimenta moto
        Veiculos[1].lista[i].y += screen_speed * Veiculos[1].speed;
        
        //se Sair da tela e Estiver na garagem
        if (Veiculos[1].lista[i].y <= - Veiculos[1].lista[i].height && Veiculos[1].lista[i].x < 0){
            //se nao estiver na transicao randomiza
            if(!transicao_frame && GetRandomValue(0, 2) && veiculos_na_tela[1] < 1) {
                //manda para tela
                veiculos_na_tela[1]++;
                Veiculos[1].lista[i].y = screenSizes[1] + GetRandomValue(0, 100) * 10;
                Veiculos[1].lista[i].x = posicoes_motos[GetRandomValue(0, faixas)];
            }
            else {
                //mantem na garagem
                Veiculos[1].lista[i].y = screenSizes[1] + GetRandomValue(0, 30) * screenSizes[1] / 10;
                Veiculos[1].lista[i].x = -screenSizes[0] -Veiculos[1].lista[i].width;
            }
        }
        //se Sair da tela e Não estiver na garagem
        else if (Veiculos[1].lista[i].y <= - Veiculos[1].lista[i].height && Veiculos[1].lista[i].x > 0){
            //manda pra garagem
            veiculos_na_tela[1]--;
            Veiculos[1].lista[i].y = screenSizes[1];
            Veiculos[1].lista[i].x = -screenSizes[0] -Veiculos[1].lista[i].width;
        }
    }
    
    
}

//------------------------------------------------------------------------------------