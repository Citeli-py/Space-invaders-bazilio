#include <allegro.h>

class projetil
{
	public:
		int x, y, v;
		BITMAP* tela;
		BITMAP* tiroImagem;
		
	projetil(BITMAP* bmp, BITMAP* tiro, int xo, int yo, int dir)
	{
		tela = bmp;
		tiroImagem = tiro;
		x = xo;
		y = yo;
		v = 7*dir;
	}
	
	void desenha()
	{
		draw_sprite(tela, tiroImagem, x, y);
	}
	
	void movimento()
	{
		y += v;
	}
	
	void destruir()
	{
		x = -99;
		y = -10;
	}
	
};

class personagem
{
	public:
		int x, y, v, shot_cont;
		BITMAP* tela;
		BITMAP* sprite;
		BITMAP* tiro;
		BITMAP* explosao;
		
		virtual void movimento()=0;
		virtual int atirar(projetil *tiros, int pos, int len, SAMPLE *som)=0;
		virtual void desenha()=0;
		virtual void destruir()=0;
		virtual void colisao(projetil *tiro)=0;
		
};

class jogador : public personagem 
{	
	public:
		
		jogador(BITMAP* bmp,  int xo, int yo)
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
				BITMAP* tiroJogador = load_bitmap("sprite/tiro_img.bmp", NULL);
				tiro = tiroJogador;
				shot_cont = 0;
				projetil p(tela, tiro, x+20, y-15, -1);
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
		
		void destruir()
		{
			x = 0;
			y = 0;
		}
		
		void colisao(projetil *tiro)
		{
			if(tiro->v>0)
				if(tiro->y<=y+10 && tiro->y>=y)
					if(tiro->x>=x-10 && tiro->x<=x+10)
					{
						explosao = load_bitmap("sprite/colisao1.bmp", NULL);
						draw_sprite(tela, explosao, x, y);
						tiro->destruir();
						destruir();
					}
		}
};

class inimigo : public personagem
{
	public:
		
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
			if(x<=20 || x>=780)
			{
				v = -v;
				y += 10;
			}
			x += v;
		}
		
		int atirar(projetil *tiros, int pos, int len, SAMPLE *som)
		{
			if(shot_cont >= 30)
			{
				BITMAP* tiroJogador = load_bitmap("sprite/enemy_shot.bmp", NULL);
				tiro = tiroJogador;
				shot_cont = 0;
				projetil p(tela, tiro, x, y+10, 1);
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
			BITMAP* naveInimigo = load_bitmap("sprite/enemy_ship.bmp", NULL);
			sprite = naveInimigo;
			draw_sprite(tela, sprite, x-20, y-25);				
		}
		
		void destruir()
		{
			x = -99;
			y = -10;
		}

		void colisao(projetil *tiro)
		{
			if(tiro->v<0)
				if(tiro->y<=y+10 && tiro->y>=y)
					if(tiro->x>=x-10 && tiro->x<=x+10)
					{
						rest(80);
						explosao = load_bitmap("sprite/colisao1.bmp", NULL);
						draw_sprite(tela, explosao, x, y);
						rest(80);
						explosao = load_bitmap("sprite/colisao2.bmp", NULL);
						draw_sprite(tela, explosao, x, y);
						rest(80);
						explosao = load_bitmap("sprite/colisao3.bmp", NULL);
						draw_sprite(tela, explosao, x, y);
						rest(80);
						explosao = load_bitmap("sprite/colisao4.bmp", NULL);
						draw_sprite(tela, explosao, x, y);
						rest(80);
						explosao = load_bitmap("sprite/colisao5.bmp", NULL);
						draw_sprite(tela, explosao, x, y);
						rest(80);
						explosao = load_bitmap("sprite/colisao6.bmp", NULL);
						draw_sprite(tela, explosao, x, y);
						rest(80);
						tiro->destruir();
						destruir();
					}
		}
};
