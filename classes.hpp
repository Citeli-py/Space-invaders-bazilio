#include <allegro.h>

class projetil
{
	public:
		int x, y, v;
		BITMAP* tela;
		
	projetil(BITMAP* bmp, int xo, int yo, int dir)
	{
		tela = bmp;
		x = xo;
		y = yo;
		v = 7*dir;
	}
	
	void desenha()
	{
		BITMAP* tiroImagem = load_bitmap("sprite/tiro_img.bmp", NULL);
		draw_sprite(tela, tiroImagem, x, y);
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
	
	int atirar(projetil *tiros, int pos, int len, SAMPLE *som)
	{
		if(key[KEY_SPACE] && shot_cont >= 30)
		{
			shot_cont = 0;
			projetil p(tela, x+20, y-15, -1);
			tiros[pos] = p;
			pos++;
			if(pos>=len) pos = 0;
			play_sample(som, 100, 128, 1000, 0);
		}
		return pos;
	}
	
	void desenha()
	{
		shot_cont++;
		draw_sprite(tela, sprite, x, y);
		draw_sprite(screen, tela, 0, 0);
		clear(tela);
	}
};

class inimigo
{
	private:
		int x,y;
		int v;
	public:
		BITMAP* tela;
		int shot_cont;
		
	inimigo(BITMAP* bmp, int xo, int yo)
	{
		tela = bmp;
		shot_cont = 0;
		x = xo;
		y = yo;
		v = 0;
	}
	
	void movimento()
	{
		if(x<=0 || x>=800)
		{
			v = -v;
			y += 10;
		}
		x += v;
	}
	
	projetil atirar()
	{
		shot_cont = 0;
		projetil p(tela, x, y+10, 1);
		return p;
	}
	
	void desenha()
	{
		shot_cont++;
		circlefill(tela, x, y, 10, makecol(255,0,0));
	}

};
