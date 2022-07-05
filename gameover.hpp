#include <allegro.h>

void gameover(BITMAP* bmp, int pontos)
{
    BITMAP* sprite = load_bitmap("sprite/gameover.bmp", NULL);

    while (!key[KEY_ENTER])
    {
		textprintf_ex(sprite, font, 320, 300, makecol(255,255,255), -1, "Voce fez %d pontos", pontos);
		textprintf_ex(sprite, font, 310, 310, makecol(255,255,255), -1, "Aperte enter para sair");
		draw_sprite(bmp, sprite, 0, 0);
        draw_sprite(screen, bmp, 0, 0);
		clear(bmp);
    }
    rest(100);
}
