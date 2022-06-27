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