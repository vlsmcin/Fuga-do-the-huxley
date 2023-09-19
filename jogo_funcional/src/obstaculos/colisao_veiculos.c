//------------------------------------------------------------------------------------

int colisao_veiculos(colecao Veiculos[], Rectangle *player, int *colided_left_right[], float *camera_target_x, int unidade) 
{
    
    // colided_left_right é colided_left, colided_right
    
    int colidiu = 0;
    
    // Colisao com carros, caminhoes, motos
    for(int v = 0; v < 3; v++) {
        for (int i = 0, max = Veiculos[v].qtd; i < max; i++) {
            
            //se colidiu com veiculo
            if (CheckCollisionRecs( (*player), Veiculos[v].lista[i] )) {
                
                //contabiliza colisao
                colidiu = 1;
                
                
                //veiculo que colidiu para facilitar aritmetica
                Rectangle veiculo = Veiculos[v].lista[i];
                
                //se player para esquerda
                if( ((*player).x + (*player).width / 2) <= ( veiculo.x + veiculo.width / 2) ) {
                    while ( (*player).x + (*player).width > veiculo.x ) {
                        //remove player do veiculo pela direita
                        (*player).x--;
                    }
                    (*colided_left_right[1]) += 6;
                    (*camera_target_x) += unidade * 18;
                }
                //se player para direita
                else {
                    while (CheckCollisionRecs( (*player), veiculo )) {
                        //remove player do veiculo pela esquerda
                        (*player).x++;
                    }
                    (*colided_left_right[0]) += 6;
                    (*camera_target_x) -= unidade * 18;
                }
                
                
                i = Veiculos[v].qtd;
                
                v = 3;
            }
        }
    }
    
    return colidiu;
}

//------------------------------------------------------------------------------------