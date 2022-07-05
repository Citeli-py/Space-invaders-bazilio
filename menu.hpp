#include <allegro.h>

class Fundo
{
    public:
        BITMAP* sprite;
        BITMAP* tela;

    Fundo(BITMAP* bmp)
    {
        tela = bmp;
        sprite = load_bitmap("sprite/Menu.bmp", NULL);
    }

    void desenha()
    {
        draw_sprite(tela, sprite, 0, 0);
        draw_sprite(screen, tela, 0, 0);
		clear(tela);
    }
};

void menu(BITMAP* bmp)
{
    Fundo *f = new Fundo(bmp);

    //SAMPLE* musica = load_sample("audio/soundtrack.wav");
    //play_sample(musica, 100, 128, 1000, 0);

    while (!key[KEY_SPACE])
    {
		f->desenha();
    }
    free(f);
    //destroy_sample(musica);
    rest(100);
}
