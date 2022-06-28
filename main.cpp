#include <allegro.h>
#include "classes.hpp"
#include "audio.hpp"


void inicializa(BITMAP* bmp, projetil* tiros, int len)
{
	projetil p(bmp, -1, -10, -1);
	for(int i=0; i<len; i++)
		tiros[i] = p;
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
	
	BITMAP* buffer = create_bitmap(800,600);
	//start_audio();
	SAMPLE *start = load_sample("audio/inicio.wav");
    SAMPLE *soundtrack = load_sample("audio/soundtrack.wav");
    SAMPLE *tiro = load_sample("audio/tiro.wav");
    play_sample(start, 100, 128, 1000, 0);
    play_sample(soundtrack, 100, 128, 1000, 1);
	
	jogador j(buffer,400,500);
	inimigo i(buffer, 400, 190);
	
	int pos=0, len=50;
	projetil *tiros = (projetil*) malloc(len*sizeof(projetil));
	inicializa(buffer, tiros, len);
	
	while (!key[KEY_ESC])
	{
		if(key[KEY_SPACE] && j.shot_cont >= 30)
		{
			tiros[pos] = j.atirar();
			pos++;
			if(pos>=len) pos = 0;
			play_sample(tiro, 100, 128, 1000, 0);
		}
		
		for(int i=0; i<len; i++)
		{
			if(tiros[i].y>=-10 && tiros[i].y<=610)
			{
				tiros[i].movimento();
				tiros[i].desenha();
			}
		}
		
		if(i.shot_cont == 100)
		{
			tiros[pos] = i.atirar();
			pos++;
			if(pos>=len) pos = 0;
		}
		
		i.movimento();
		i.desenha();
		
		j.movimento();
		j.desenha();
		
		rest(10);
	}
	destroy_bitmap(buffer);
	destroy_sample(start);
	destroy_sample(soundtrack);
	destroy_sample(tiro);
	
	return 0;
}
END_OF_MAIN();
