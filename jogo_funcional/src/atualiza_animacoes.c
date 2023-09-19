//------------------------------------------------------------------------------------

void atualiza_animacoes(Animacao *Animacoes[], int qtd, int global_fps)
{
    
    for(int s = 0; s < qtd; s++) {
        
        (*Animacoes[s]).frame_counter++;
        
        if((*Animacoes[s]).frame_counter >= global_fps / (*Animacoes[s]).fps) {
            
            (*Animacoes[s]).frame_counter = 0;
            
            (*Animacoes[s]).frame_curr = ((*Animacoes[s]).frame_curr + 1) % (*Animacoes[s]).frame_qtd;
            
            (*Animacoes[s]).source.x = 
                (float)(*Animacoes[s]).frame_curr * 
                (float)(*Animacoes[s]).texture.width / 
                (float)(*Animacoes[s]).frame_qtd
            ;
            
        }
        
    }
}

//------------------------------------------------------------------------------------