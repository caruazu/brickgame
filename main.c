#include <stdio.h>
#include <allegro5/allegro.h>
/* criando os ponteiros */
ALLEGRO_TIMER *temporizador= NULL;
ALLEGRO_DISPLAY *janela= NULL;
ALLEGRO_BITMAP *bloco = NULL;
ALLEGRO_EVENT_QUEUE *eventos= NULL;
/* variaveis locais*/
bool KEY_SPACE= false;
bool KEY_DOWN= false;
bool KEY_LEFT= false;
bool KEY_RIGHT= false;
bool redraw= true;
/* Propoção do jogo */
#define TAMANHO 200
const int LARGURA=TAMANHO;
const int ALTURA=TAMANHO*2;
const int LINHA=(TAMANHO/2)/5;
const int COLUNA=((TAMANHO/2)*2)/5;
const int LARGURA_BLOCO=((TAMANHO-(TAMANHO/20))/2)/5;
const int ALTURA_BLOCO=((TAMANHO-(TAMANHO/20))/2)/5;
/* funçoes */
bool controles();
int main(int argc, char const *argv[])
{
	/* inicialização e verificação*/
	if(!al_install_system(ALLEGRO_VERSION_INT, atexit)) 
	{
		fprintf(stderr, "fallha ao iniciar o allegro\n");
		return -1;
	}
	if(!al_install_keyboard())
	{
		fprintf(stderr, "falha ao iniciar o teclado\n");
		return -1;
	}
	/* eventos */
	temporizador= al_create_timer(1.0/60);
	if(!temporizador) {
		fprintf(stderr, "falha ao criar o temporizador\n");
		return -1;
	}
	janela= al_create_display(LARGURA,ALTURA);
	if(!janela) 
	{
		fprintf(stderr, "falha ao criar o display\n");
		al_destroy_timer(temporizador);
		return -1;
	}
	bloco = al_create_bitmap(LARGURA_BLOCO,ALTURA_BLOCO);
	if(!bloco) 
	{
			fprintf(stderr, "falha ao criar o bitmap\n");
			al_destroy_timer(temporizador);
			al_destroy_display(janela);
			return -1;
	}
	eventos= al_create_event_queue();
	if(!eventos) 
	{
		fprintf(stderr, "falha ao iniciar os eventos\n");
		al_destroy_timer(temporizador);
		al_destroy_display(janela);
		al_destroy_bitmap(bloco);
		return -1;
	}
	/* The target bitmap is the bitmap in which all drawing functions currently draw to */
	al_set_target_bitmap(bloco);
	al_clear_to_color(al_map_rgb(0, 0, 255));
	/* hange the drawing target back to the display we created */
	al_set_target_bitmap(al_get_backbuffer(janela));

	/* registro de eventos */
	/* linka o teclado com o queue de eventos */
	al_register_event_source(eventos, al_get_keyboard_event_source());	
	/* linka o temporizador com o queue de eventos */
	al_register_event_source(eventos, al_get_timer_event_source(temporizador)); 
	/* linka o display com o queue de eventos */
	al_register_event_source(eventos, al_get_display_event_source(janela));


	/* cor do display */
	al_clear_to_color(al_map_rgb(255, 0, 0));
	/* mostra no display a imagem criada no buffer */
	al_flip_display();
	/* inicia a contagem*/
	al_start_timer(temporizador); 
	/*loop do jogo*/
	bool sair= false;
	while(!sair)
	{
		sair=controles();
		/* se nenhum evento foi ativado */
		if(redraw&&al_is_event_queue_empty(eventos))
		{
			redraw=false;
			al_clear_to_color(al_map_rgb(255, 255, 255));
			for (int linha = 0; linha < 20; ++linha)
			{
				for (int coluna = 0; coluna < 10; ++coluna)
				{
					al_draw_bitmap(bloco, coluna*LINHA, linha*LINHA, 0);
				}				
			}			
			al_flip_display();
		}		
	}
	/* limpeza */
	al_destroy_timer(temporizador);
	al_destroy_display(janela);
	al_destroy_event_queue(eventos);
	al_uninstall_keyboard();
	return 0;
}
bool controles()
{
	ALLEGRO_EVENT evnt0;
	al_wait_for_event(eventos, &evnt0);
	if(evnt0.type == ALLEGRO_EVENT_TIMER)
	{
		if(KEY_SPACE)
		{
			printf("HOLD\t\t");
			printf("space\n");
		}
		if(KEY_DOWN)
		{
			printf("HOLD\t\t");
			printf("down\n");
		}
		if(KEY_LEFT)
		{
			printf("HOLD\t\t");
			printf("left\n");
		}
		if(KEY_RIGHT)
		{
			printf("HOLD\t\t");
			printf("right\n");
		}
		redraw = true;
	}
	else
	{
		if(evnt0.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return true;
		}
		else
		{
			if(evnt0.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch(evnt0.keyboard.keycode) 
				{
					case ALLEGRO_KEY_SPACE:
						KEY_SPACE = true;
						printf("KEY_DOWN\t");
						printf("space\n");
						break;
					case ALLEGRO_KEY_DOWN:
						KEY_DOWN = true;
						printf("KEY_DOWN\t");
						printf("down\n");
						break;
					case ALLEGRO_KEY_LEFT: 
						KEY_LEFT = true;
						printf("KEY_DOWN\t");
						printf("left\n");
						break;
					case ALLEGRO_KEY_RIGHT:
						KEY_RIGHT = true;
						printf("KEY_DOWN\t");
						printf("right\n");
						break;
				}
			}
			else
			{
				if(evnt0.type == ALLEGRO_EVENT_KEY_UP)
				{
					switch(evnt0.keyboard.keycode)
					{
						case ALLEGRO_KEY_SPACE:
							KEY_SPACE = false;
							printf("KEY_UP\t\t");
							printf("space\n");
							break;
						case ALLEGRO_KEY_DOWN:
							KEY_DOWN = false;
							printf("KEY_UP\t\t");
							printf("down\n");
							break;
						case ALLEGRO_KEY_LEFT: 
							KEY_LEFT = false;
							printf("KEY_UP\t\t");
							printf("left\n");
							break;
						case ALLEGRO_KEY_RIGHT:
							KEY_RIGHT = false;
							printf("KEY_UP\t\t");
							printf("right\n");
							break;
						case ALLEGRO_KEY_ESCAPE:
							return true;
							break;
					}
				}
			}
		}
	}		
}