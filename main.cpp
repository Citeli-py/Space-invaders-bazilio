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
		BITMAP* tiroImagem = load_bitmap("sprite/tiro_img.bmp", NULL);
		draw_sprite(tela, tiroImagem, x+largura+13, y);
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
		BITMAP* sprite;
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
		if(key[KEY_D]||key[KEY_RIGHT])
		{
			BITMAP* naveDir = load_bitmap("sprite/right.bmp", NULL);
			sprite = naveDir;	
			x+=v;
		}
		else if(key[KEY_A]||key[KEY_LEFT])
		{
			BITMAP* naveEsq = load_bitmap("sprite/left.bmp", NULL);
			sprite = naveEsq;
			x-=v;
		}
		else
		{
			BITMAP* naveCentro = load_bitmap("sprite/center.bmp", NULL);
			sprite = naveCentro;
		}
			
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
		draw_sprite(tela, sprite, x, y);
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
	jogador j(buffer,380,500); //sprite tem 20px de largura
	
	int pos=0, len=100;
	projetil *tiros = (projetil*) malloc(len*sizeof(projetil));
	inicializa(buffer, tiros, len);
	
	//Sons
	SAMPLE *start = load_sample("audio/inicio.wav");
	SAMPLE *soundtrack = load_sample("audio/soundtrack.wav");
	SAMPLE *tiro = load_sample("audio/tiro.wav");
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
