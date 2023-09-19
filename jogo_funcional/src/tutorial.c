//------------------------------------------------------------------------------------

void tutorial(long int *tutorial_frame, colecao Veiculos[], Circle *buraco_obj, int *frame_helic, const int screenSizes[])
{
    static int tutlen = 800;
    
    int borda = screenSizes[0] / 5;
    
    int largura_veiculo;
    int separacao;
    
    
    //bloqueia veiculos
    Veiculos[0].qtd = 0;
    Veiculos[1].qtd = 0;
    Veiculos[2].qtd = 0;
        
        
    //tutorial carros
    if((*tutorial_frame) < tutlen || Veiculos[0].lista[0].x > 0) {
        
        //bloqueia helicoptero e buraco
        (*frame_helic) = -1;
        buraco_obj->pos.y = - buraco_obj->radius * 2;
        
        //seta valores para calculo
        largura_veiculo = Veiculos[0].lista[0].width;
        separacao = (screenSizes[0] - borda * 2 - 4 * largura_veiculo) / (5);
        
        //permite um carro
        Veiculos[0].qtd = 1;
        
        // coloca carro na tela
        if(Veiculos[0].lista[0].x < 0) {
            Veiculos[0].lista[0].x = screenSizes[0] / 5 + (screenSizes[0] - borda * 2 - 4 * largura_veiculo) / (5) + GetRandomValue(0, 3) * (separacao + largura_veiculo);
            Veiculos[0].lista[0].y = -Veiculos[0].lista[0].height - borda;
        }
        
        //apos carro aparecer cinco vezes para carro
        if((*tutorial_frame) > tutlen * 0.95 && Veiculos[0].lista[0].y < 0) {
            //manda pra garagem
            Veiculos[0].lista[0].y = -Veiculos[0].lista[0].height;
            Veiculos[0].lista[0].x = -screenSizes[0] -Veiculos[0].lista[0].width;
        }
        
    }
    
    //tutorial motos
    else if((*tutorial_frame) < tutlen * 2 || Veiculos[1].lista[0].x > 0) {
        
        //bloqueia helicoptero e buraco
        (*frame_helic) = -1;
        buraco_obj->pos.y = - buraco_obj->radius * 2;
        
        //seta valores para calculo
        largura_veiculo = Veiculos[1].lista[0].width;
        separacao = (screenSizes[0] - borda * 2 - largura_veiculo * 2 - largura_veiculo * (3)) / (4);

        int posicoes_motos[5];
        posicoes_motos[0] = borda;
        posicoes_motos[4] = screenSizes[0] - borda - largura_veiculo;
    
        for(int i = 1; i < 4; i++) {
            posicoes_motos[i] = borda + largura_veiculo + separacao + (i - 1) * (largura_veiculo + separacao);
        }
        
        //permite uma moto
        Veiculos[1].qtd = 1;
        
        // coloca moto na tela
        if(Veiculos[1].lista[0].x < 0) {
            Veiculos[1].lista[0].x = posicoes_motos[GetRandomValue(0, 4)];
            Veiculos[1].lista[0].y = screenSizes[1] + borda;
        }
        
        //apos moto aparecer cinco vezes para carro
        if((*tutorial_frame) > tutlen * 2 * 0.95 && Veiculos[0].lista[0].y < 0) {
            //manda pra garagem
            Veiculos[1].lista[0].x = -screenSizes[0] -Veiculos[1].lista[0].width;
            Veiculos[1].lista[0].y = screenSizes[1];
        }
        
    }
    //tutorial caminhoes
    else if((*tutorial_frame) < 3600 || Veiculos[2].lista[0].x > 0) {
        
        //bloqueia helicoptero e buraco
        (*frame_helic) = -1;
        buraco_obj->pos.y = - buraco_obj->radius * 2;
        
        //permite um caminhao
        Veiculos[2].qtd = 1;
        
    }
    else {
        (*tutorial_frame) = -1;
    }
    /*
    if((*tutorial_frame)  0) {
        (*frame_helic) = 0;
        (*buraco_obj).pos.x = -buraco_obj.x * 2;
    }
    */
    (*tutorial_frame)++;
}

//------------------------------------------------------------------------------------