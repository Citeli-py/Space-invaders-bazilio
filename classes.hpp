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
		v = 3*dir;
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
			if(key[KEY_D]||key[KEY_RIGHT]&&x<=750)
			{
				BITMAP* naveDir = load_bitmap("sprite/right.bmp", NULL);
				sprite = naveDir;	
				x+=v;
			}
			else if((key[KEY_A]||key[KEY_LEFT])&&x>=0)
			{
				BITMAP* naveEsq = load_bitmap("sprite/left.bmp", NULL);
				sprite = naveEsq;
				x-=v;
			}
			else
			{
				BITMAP* naveCentro = load_bitmap("sprite/center.bmp", NULL);
				sprite = naveCentro;
				if(key[KEY_W] || key[KEY_UP]) y-=v;
				if(key[KEY_S] || key[KEY_DOWN]) y+=v;
			}
				
		}
		
		int atirar(projetil *tiros, int pos, int len, SAMPLE *som)
		{
			if(key[KEY_SPACE] && shot_cont >= 10)
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
			x = -99;
			y = -99;
		}
		
		void colisao(projetil *tiro)
		{
			if(tiro->v>0)
				if(tiro->y<=y+40 && tiro->y>=y)
					if(tiro->x>=x-10 && tiro->x<=x+10)
					{
						tiro->destruir();
						destruir();
					}
		}
};

class inimigo : public personagem
{
	public:
		int shot_rate;
		inimigo(BITMAP* bmp, int xo, int yo)
		{
			shot_rate = rand()%40 + 51;
			tela = bmp;
			shot_cont = 0;
			x = xo;
			y = yo;
			v = 1;
		}
		
		void movimento()
		{
			if(x <=150 || x>= 700)
			{
				v = -v;
			}
			if(v<0) y += -v;
			else y += v;
			x += v;
		}
		
		int atirar(projetil *tiros, int pos, int len, SAMPLE *som)
		{
			if(shot_cont >= shot_rate)
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
				if(tiro->y<=y+40 && tiro->y>=y)
					if(tiro->x>=x-10 && tiro->x<=x+10)
					{
						tiro->destruir();
						destruir();
					}
		}
};
