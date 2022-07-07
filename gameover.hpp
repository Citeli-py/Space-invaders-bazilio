#include <allegro.h>

int gameover(BITMAP* bmp, int pontos)
{
    BITMAP* sprite = load_bitmap("sprite/gameover.bmp", NULL);

    while (!key[KEY_ESC])
    {
    	if(key[KEY_ENTER]) return 1;
    	
		textprintf_ex(sprite, font, 320, 300, makecol(255,255,255), -1, "Voce fez %d pontos", pontos);
		textprintf_ex(sprite, font, 310, 310, makecol(255,255,255), -1, "Aperte ESC para sair");
		textprintf_ex(sprite, font, 300, 320, makecol(255,255,255), -1, "Aperte ENTER para jogar de novo");
		
		draw_sprite(bmp, sprite, 0, 0);
        draw_sprite(screen, bmp, 0, 0);
		clear(bmp);
    }
    rest(100);
    
    return 0;
}
