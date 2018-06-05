#include <stdio.h>
#include <allegro5/allegro.h>
/* criando os ponteiros */
ALLEGRO_DISPLAY *janela= NULL; 
ALLEGRO_EVENT_QUEUE *eventos= NULL;
ALLEGRO_TIMER *temporizador= NULL;
ALLEGRO_KEYBOARD_STATE tecla;
/* funçoes */
void controles();
int main(int argc, char const *argv[])
{
	/* inicialização e verificação*/
	if(!al_install_system(ALLEGRO_VERSION_INT, atexit)) 
	{
		fprintf(stderr, "fallha ao iniciar o allegro\n");
		return -1;
	}
	if (!al_install_keyboard())
	{
		fprintf(stderr, "falha ao iniciar o teclado\n");
		return -1;
	}
	/* eventos */
	temporizador= al_create_timer(1.0 / 60);
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
	/* linka o display com o queue de eventos */
	al_register_event_source(eventos, al_get_display_event_source(janela));
	/* linka o temporizador com o queue de eventos */
	al_register_event_source(eventos, al_get_timer_event_source(temporizador)); 

	/* cor do display */
	al_clear_to_color(al_map_rgb(255,0,0));
	/* mostra no display a imagem criada no buffer */
	al_flip_display();
	/* inicia a contagem*/
	al_start_timer(temporizador);	
	/*loop do jogo*/
	bool rodando= true;
	while(rodando)
	{
		/*cria o evento*/
		ALLEGRO_EVENT evnt0;
		al_wait_for_event(eventos, &evnt0);
		/* se apertar em fechar ou teclar ESC */		
		if (evnt0.type == ALLEGRO_EVENT_DISPLAY_CLOSE 
			|| al_key_down(&tecla,ALLEGRO_KEY_ESCAPE))
		{
			rodando = false;
		}
		else
		{	/* se nenhum evento foi ativado */
			if (al_is_event_queue_empty(eventos))
			{
				controles();
				al_clear_to_color(al_map_rgb(255,255,0));
				al_flip_display();
			}
		}
	}
	/* limpeza */
	al_destroy_timer(temporizador);
	al_destroy_display(janela);
	al_destroy_event_queue(eventos);
	al_uninstall_keyboard();
	return 0;
}
void controles()
{
	al_get_keyboard_state(&tecla);
	if (al_key_down(&tecla,ALLEGRO_KEY_RIGHT))
	{
		printf("direira\n");
	}
		if (al_key_down(&tecla,ALLEGRO_KEY_LEFT))
	{
		printf("esquerda\n");
	}
		if (al_key_down(&tecla,ALLEGRO_KEY_DOWN))
	{
		printf("baixo\n");
	}
		if (al_key_down(&tecla,ALLEGRO_KEY_SPACE))
	{
		printf("espaço\n");
	}
}