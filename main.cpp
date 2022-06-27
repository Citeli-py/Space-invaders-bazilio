#include <allegro.h>


class projetil
{
	public:
		int x, y, v;
		int largura, altura;
		BITMAP* tela;
		
	projetil(BITMAP* bmp, int xo, int yo, int dir)
	{
		tela = bmp;
		largura = 5;
		altura = 20;
		x = xo;
		y = yo;
		v = 7*dir;
	}
	
	void desenha()
	{
		int dir=1;
		if(v<0) dir = -1;
		//circle(tela, x, y-10, 5, makecol(255,0,0));
		rectfill(tela, x, y, x+largura, y-dir*altura, makecol(255,0,0));
	}
	
	void movimento()
	{
		y += v;
	}
};


class jogador
{
	public:
		int x,y;
		int v;
		BITMAP* tela;
		int shot_cont;
		
	jogador(BITMAP* bmp, int xo, int yo)
	{
		shot_cont = 0;
		tela = bmp;
		x = xo;
		y = yo;
		v = 5;
	}
	
	void movimento()
	{
		if(key[KEY_D]||key[KEY_RIGHT]) x+=v;
		if(key[KEY_A]||key[KEY_LEFT]) x-=v;	
	}
	
	projetil atirar()
	{
		shot_cont = 0;
		projetil p(tela, x, y-15, -1);
		return p;
	}
	
	void desenha()
	{
		shot_cont++;
		circlefill(tela, x, y, 10, makecol(255,255,255));
		draw_sprite(screen, tela, 0, 0);
		clear(tela);
	}
};

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
	
	//Sons
	SAMPLE *start = load_sample("inicio.wav");
	SAMPLE *soundtrack = load_sample("soundtrack.wav");
	SAMPLE *tiro = load_sample("tiro.wav");
	play_sample(start, 100, 128, 1000, 0);
	play_sample(soundtrack, 100, 128, 1000, 1);
	
	while (!key[KEY_ESC])
	{
		if(key[KEY_SPACE] && j.shot_cont >= 20)
		{
			tiros[pos] = j.atirar();
			pos++;
			if(pos>=len) pos = 0;
			play_sample(tiro, 100, 128, 1000, 0);
		}
		
		for(int i=0; i<len; i++) //Aqui tem um bug
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
	destroy_sample(start);
	destroy_sample(soundtrack);
	destroy_sample(tiro);
	
	return 0;
}
END_OF_MAIN();
