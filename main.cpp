#include <allegro.h>
#include "classes.hpp"


void inicializa(BITMAP* bmp, projetil* tiros, int len)
{
	projetil p(bmp, -99, -1, -1);
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
	jogador j(buffer,400,550);
	
	int pos=0, len=100;
	projetil *tiros = (projetil*) malloc(len*sizeof(projetil));
	inicializa(buffer, tiros, len);
	
	while (!key[KEY_ESC])
	{
		if(key[KEY_SPACE] && j.shot_cont >= 30)
		{
			tiros[pos] = j.atirar();
			pos++;
			if(pos>=len) pos = 0;
		}
		
		for(int i=0; i<len; i++)
		{
			if(tiros[i].x!=-99)
			{
				tiros[i].movimento();
				tiros[i].desenha();
			}
		}
		
		j.movimento();
		j.desenha();
		rest(10);
	}
	destroy_bitmap(buffer);
	
	return 0;
}
END_OF_MAIN();
