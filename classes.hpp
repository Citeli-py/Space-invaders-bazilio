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
		v = 1;
	}
	
	void movimento()
	{
		if(x<=0 || x>=800)
		{
			v = -v;
			y += 10;
		}
		x = x+ v;
	}
	
	projetil atirar()
	{
		shot_cont = 0;
		projetil p(tela, x, y+15, 1);
		return p;
	}
	
	void desenha()
	{
		shot_cont++;
		circlefill(tela, x, y, 10, makecol(255,0,0));
	}

};