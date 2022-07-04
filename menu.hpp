#include <allegro.h>
//#include "classes.hpp"

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
    /*
    inimigo *i = (inimigo*) malloc(5*sizeof(inimigo));

    for(int j=0; j<5; j++)
    {
        inimigo p(bmp, 20*j + 10, 100);
        i[j] = p;
    }*/

    SAMPLE* musica = load_sample("audio/borges.wav");
    play_sample(musica, 100, 128, 1000, 0);

    while (!key[KEY_SPACE])
    {
        /*
        for(int j=0; j<5; j++)
        {
            i[j].movimento();
            i[j].desenha();
        }*/
		f->desenha();
    }
    free(f);
    destroy_sample(musica);
    rest(100);
}
