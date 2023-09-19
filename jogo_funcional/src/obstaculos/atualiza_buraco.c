//------------------------------------------------------------------------------------

void atualiza_buraco(Circle *buraco_obj, float screen_speed, const int screenSizes[], int transicao_frame)
{
    
    int borda = screenSizes[0] / 6;
    
    // Atualiza buraco
    
    // Movimento do circulo
    buraco_obj->pos.y += screen_speed * 4;
    
    //Se Objeto passar da borda final do mapa ele vai ser posto na garagem
    if( buraco_obj->pos.y >= screenSizes[1] + (buraco_obj->radius * 2) ){
        
        //manda para garagem
        buraco_obj->pos.x = -screenSizes[0] -(buraco_obj->radius * 2);//valor da "garagem"
        buraco_obj->pos.y = -(buraco_obj->radius * 2);
        
    }
    if( transicao_frame && buraco_obj->pos.y == -(buraco_obj->radius * 2) && !(GetRandomValue(0,2)) ){
        
        // Coloca buraco em posicao aleatoria da rua
        buraco_obj->pos.x = 
        GetRandomValue(borda + (buraco_obj->radius * 2) / 2, screenSizes[0] - borda - (buraco_obj->radius * 2) / 2);
        buraco_obj->pos.y = -(buraco_obj->radius * 2);
        
        
    }
}

//------------------------------------------------------------------------------------