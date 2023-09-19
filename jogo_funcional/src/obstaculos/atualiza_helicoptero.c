//------------------------------------------------------------------------------------

void atualiza_helicoptero(Line *lazer, Animacao *helicoptero, int *frame_helic, const int screenSizes[], int transicao_frame)
{
    
    //numero de frames da animacao
    const int max_frames_helic = 270;
    
    
    //contabiliza frame
    (*frame_helic)++;
    
    
    //se inicio da animacao
    if ((*frame_helic) == 1) {
        
        //se for dessa vez +/- 2.5 segundos entre helicopteros
        if( transicao_frame && !GetRandomValue(0, 300) ) {
            
            //right or left
            int r_or_l = GetRandomValue(0, 1);
            r_or_l = r_or_l * 2 - 1;
            
            //inicializa lazer do helicoptero em posicao aleatoria
            lazer->start.x = (float)(screenSizes[0] / 2 + r_or_l * screenSizes[0] * 3 / 8);
            lazer->start.y = (float)GetRandomValue(screenSizes[1] / 8, screenSizes[1] * 7 / 8);
            lazer->end = (*lazer).start;
            
            //coloca valor a se alterare end para que chegue em posicao aleatoria do outro lado
            lazer->move.x = ( (float)( screenSizes[0] / 2 +  -r_or_l * screenSizes[0] * 0.55f ) - lazer->end.x ) / 60.0f;
            lazer->move.y = ( (float)GetRandomValue(screenSizes[1] / 8, screenSizes[1] * 7 / 8) - lazer->end.y ) / 60.0f;
            
            //coloca helicoptero fora da tela
            helicoptero->dest.x = lazer->start.x - lazer->move.x * 60.0f;
            helicoptero->dest.y = lazer->start.y - lazer->move.y * 60.0f;
            
            helicoptero->source.x -= (-r_or_l - 1) / 2 * helicoptero->source.width;
            helicoptero->source.width *= -r_or_l;
            
        }
        //se nao, reseta
        else {
            
            (*frame_helic) = 0;
            
        }
        
    }
    //na parte que move o helicopteroo ate o lugar
    else if( (*frame_helic) < 90 ){
        
        //desloca helicoptero ate posicao
        helicoptero->dest.x += lazer->move.x * (80 - (*frame_helic)) / 60.0f;
        helicoptero->dest.y += lazer->move.y * (80 - (*frame_helic)) / 60.0f;
        
    }
    else if( (*frame_helic) == 90 ){
        lazer->start.x = helicoptero->dest.x;
        lazer->start.y = helicoptero->dest.y;
        lazer->end = lazer->start;
    }
    //na parte da extensao do lazer pela tela
    else if( (*frame_helic) < 150 ){
        
        //move fim do lazer ate outro lado da tela
        lazer->end.x += lazer->move.x;
        lazer->end.y += lazer->move.y;
        
    }
    //na parte de piscar
    else if((*frame_helic) < 240) {
        
        //apaga lazer a cada 10 frames
        if(((*frame_helic) / 10) % 2) {
            lazer->thick = (float)screenSizes[0] / 200.0f;
        }
        else {
            lazer->thick = 0.0f;
        }
        
    }
    //na parte de sair
    else if((*frame_helic) <= max_frames_helic) {
        lazer->thick = 0.0f;
        //desloca helicoptero ate fora da tela
        helicoptero->dest.x -= lazer->move.x / 2;
        helicoptero->dest.y -= lazer->move.y / 2;
    }
    //ao fim da animação frame max_frames_helic + 1
    else {
        
        //reseta lazer e frame_helic
        (*frame_helic) = 0;
        (*lazer) = (Line){
            (Vector2) { -screenSizes[0], -screenSizes[1] },
            (Vector2) { -screenSizes[0], -screenSizes[1] },
            (float)screenSizes[0] / 200.0f
        };
        
        //coloca source no lugar
        helicoptero->source.x = 0;
        helicoptero->source.width = helicoptero->texture.width / 4;
        
    }
}

//------------------------------------------------------------------------------------