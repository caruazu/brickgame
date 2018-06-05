#include <stdio.h>
#include <allegro5/allegro.h>
/* criando os ponteiros */
ALLEGRO_TIMER *temporizador= NULL;
ALLEGRO_DISPLAY *janela= NULL; 
ALLEGRO_EVENT_QUEUE *eventos= NULL;
bool KEY_SPACE= false;
bool KEY_DOWN= false;
bool KEY_LEFT= false;
bool KEY_RIGHT= false;
bool redraw= true;

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
	janela= al_create_display(300,400);
	if(!janela) 
	{
		fprintf(stderr, "falha ao criar o display\n");
		al_destroy_timer(temporizador);
		return -1;
	}
	eventos= al_create_event_queue();
	if(!eventos) 
	{
		fprintf(stderr, "falha ao iniciar os eventos\n");
		al_destroy_timer(temporizador);
		al_destroy_display(janela);
		return -1;
	}
	/* registro de eventos */
	/* linka o teclado com o queue de eventos */
	al_register_event_source(eventos, al_get_keyboard_event_source());	
	/* linka o temporizador com o queue de eventos */
	al_register_event_source(eventos, al_get_timer_event_source(temporizador)); 
	/* linka o display com o queue de eventos */
	al_register_event_source(eventos, al_get_display_event_source(janela));

	/* cor do display */
	al_clear_to_color(al_map_rgb(255,0,0));
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
			al_clear_to_color(al_map_rgb(255,255,0));
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
			printf("HOLD ");
			printf("space\n");
		}
		if(KEY_DOWN)
		{
			printf("HOLD ");
			printf("down\n");
		}
		if(KEY_LEFT)
		{
			printf("HOLD ");
			printf("left\n");
		}
		if(KEY_RIGHT)
		{
			printf("HOLD ");
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
						printf("KEY_DOWN ");
						printf("space\n");
						break;
					case ALLEGRO_KEY_DOWN:
						KEY_DOWN = true;
						printf("KEY_DOWN ");
						printf("down\n");
						break;
					case ALLEGRO_KEY_LEFT: 
						KEY_LEFT = true;
						printf("KEY_DOWN ");
						printf("left\n");
						break;
					case ALLEGRO_KEY_RIGHT:
						KEY_RIGHT = true;
						printf("KEY_DOWN ");
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
							printf("KEY_UP ");
							printf("space\n");
							break;
						case ALLEGRO_KEY_DOWN:
							KEY_DOWN = false;
							printf("KEY_UP ");
							printf("down\n");
							break;
						case ALLEGRO_KEY_LEFT: 
							KEY_LEFT = false;
							printf("KEY_UP ");
							printf("left\n");
							break;
						case ALLEGRO_KEY_RIGHT:
							KEY_RIGHT = false;
							printf("KEY_UP ");
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