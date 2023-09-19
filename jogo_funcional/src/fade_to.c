//------------------------------------------------------------------------------------

void fade_to(int *fade_frame, int fade_speed, Color *fade_cor, Color fade_src, Color fade_dst, const int screenSizes[])
{
    
    
    if((*fade_frame) == 1) {

    }
    
    if((*fade_frame) > 0 && (*fade_frame) < 255) {
        
        (*fade_cor).r = (fade_dst.r - fade_src.r) / 255 * (*fade_frame);
        (*fade_cor).g = (fade_dst.g - fade_src.g) / 255 * (*fade_frame);
        (*fade_cor).b = (fade_dst.b - fade_src.b) / 255 * (*fade_frame);
        (*fade_cor).a = (fade_dst.a - fade_src.a) / 255 * (*fade_frame);
        
        (*fade_frame) += fade_speed;
        
    } 
    else if ((*fade_frame) >= 255) {
        (*fade_frame) = 0;
    }
    
}



//------------------------------------------------------------------------------------