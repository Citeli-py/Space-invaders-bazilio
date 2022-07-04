#include <allegro.h>
#include "classes.hpp"
#include "audio.hpp"

void inicializa(BITMAP* bmp, BITMAP* tiro,projetil* tiros, int len)
{
	projetil p(bmp, tiro, -1, -10, -1);
	for(int i=0; i<len; i++)
	{
		tiros[i] = p;
	}
}

void computa_tiros(projetil *tiros, int len, personagem *j)
{
	for(int i=0; i<len; i++)
		if(tiros[i].y>=-10 && tiros[i].y<=610)
		{
			j->colisao(&tiros[i]);
			tiros[i].movimento();
			tiros[i].desenha();
		}
}

int main() 
{
	allegro_init();
	install_timer();
	install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	set_window_title("Space Invaders");
	
	BITMAP *buffer = load_bitmap("sprite/background.bmp", NULL);
	BITMAP *tiroImagem = create_bitmap(0,0);
	SAMPLE *start = load_sample("audio/inicio.wav");
    SAMPLE *soundtrack = load_sample("audio/soundtrack.wav");
    SAMPLE *tiro = load_sample("audio/tiro.wav");
    
    play_sample(start, 100, 128, 1000, 0);
    play_sample(soundtrack, 100, 128, 1000, 1);
	
	jogador *j = new jogador(buffer, 400,501);
	inimigo *i = new inimigo(buffer, 400, 190);
	
	int pos=0, len=100;
	projetil *tiros = (projetil*) malloc(len*sizeof(projetil));
	inicializa(buffer, tiroImagem,tiros, len);
	
	while (!key[KEY_ESC])
	{	
		pos = j->atirar(tiros, pos, len, tiro);
		pos = i->atirar(tiros, pos, len, tiro);
		
		computa_tiros(tiros, len, i);
		
		if(i->x >=0 && i->x <=800)
			if(i->y >=0 && i->y <=600)
			{
				i->movimento();
				i->desenha();
			}
		
		j->movimento();
		j->desenha();
		
		rest(10);
	}
	
	free(i);
	free(j);
	
	destroy_bitmap(buffer);
	destroy_sample(start);
	destroy_sample(soundtrack);
	destroy_sample(tiro);
	
	return 0;
}
END_OF_MAIN();
