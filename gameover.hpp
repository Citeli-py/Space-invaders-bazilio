#include <allegro.h>

void gameover(BITMAP* bmp)
{
    BITMAP* sprite = load_bitmap("sprite/gameover.bmp", NULL);

    while (!key[KEY_ENTER])
    {
		draw_sprite(bmp, sprite, 0, 0);
        draw_sprite(screen, bmp, 0, 0);
		clear(bmp);
    }
    rest(100);
}
