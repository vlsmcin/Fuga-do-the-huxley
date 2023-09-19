//------------------------------------------------------------------------------------

void colisao_topoebase(Rectangle *player, int bordas[])
{
    
    
    // Verifica colisoes com base e topo e mantem player na tela
    if ((*player).y + (*player).height > bordas[0]) {
        while((*player).y + (*player).height > bordas[0]) {
            (*player).y--;
        }
    }
    else if ((*player).y < bordas[1]) {
        while ((*player).y < bordas[1]) {
            (*player).y++;
        }
    }
    
}

//------------------------------------------------------------------------------------