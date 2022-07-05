#include <allegro.h>
#include "classes.hpp"
#include "menu.hpp"
#include "gameover.hpp"

void inicializa(BITMAP* bmp, BITMAP* tiro,projetil* tiros, int len)
{
	projetil p(bmp, tiro, -1, -11, -1);
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

inimigo* spawner(BITMAP* bmp, int* pos)
{
	*pos++;
	inimigo *p = new inimigo(bmp, rand()%500 + 50, -(rand()%100)-30);
	return p;
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
	
	BITMAP *buffer = create_bitmap(800,600);
	
	BITMAP *fundo = load_bitmap("sprite/background.bmp", NULL);
	
	BITMAP *tiroImagem = create_bitmap(0,0);
	SAMPLE *start = load_sample("audio/inicio.wav");
    SAMPLE *soundtrack = load_sample("audio/soundtrack.wav");
    SAMPLE *tiro = load_sample("audio/tiro.wav");
    
    play_sample(soundtrack, 100, 128, 1000, 1);
    menu(buffer);
    play_sample(start, 100, 128, 1000, 0);
	
	jogador *j = new jogador(buffer, 400,500);
	int n=5, pontos=0;
	inimigo *i[n];
	
	for(int k=0; k<n; k++)
		i[k] = spawner(buffer, NULL);
	
	int pos=0, len=100;
	projetil *tiros = (projetil*) malloc(len*sizeof(projetil));
	inicializa(buffer, tiroImagem,tiros, len);
	
	int fim=0;
	
	while (!key[KEY_ESC] && !fim)
	{	
		draw_sprite(buffer, fundo, 0,0);
		pos = j->atirar(tiros, pos, len, tiro);
		computa_tiros(tiros, len, j);
		
		for(int k=0; k<n; k++)
		{
			computa_tiros(tiros, len, i[k]);
			pos = i[k]->atirar(tiros, pos, len, tiro);
			
			if(i[k]->x >=0 && i[k]->x <=800)
			{
				if(i[k]->y <=600)
				{
					i[k]->movimento();
					i[k]->desenha();
				}
				else
					fim = 1; 
			}
			else
			{
				play_sample(start, 100, 128, 1000, 0);
				i[k] = spawner(buffer, NULL);
				pontos += 100;
			}
		}
		
		if(j->x <= -40)
			fim = 1;
		
		textprintf_ex(buffer, font, 10, 10, makecol(255,255,255), 1, "Pontuacao: %d", pontos);

		
		j->movimento();
		j->desenha();
		
		rest(1);
	}
	
	if(fim)
		gameover(buffer);
	
	free(i);
	free(j);
	
	destroy_bitmap(buffer);
	destroy_sample(start);
	destroy_sample(soundtrack);
	destroy_sample(tiro);
	
	return 0;
}
END_OF_MAIN();
