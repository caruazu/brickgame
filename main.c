#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
//funções
int timer1 ();
void girar ();
int confere ();
void control ();
void apagarlinha ();
void criaforma ();
//objetos
struct Partes
{
	int x,y;
}
posicao_a[4],posicao_b[4],troca[4];
//Variáveis constantes
const int WIDTH= 300, HEIGHT=700, LIN=20, COL =10, WDT=25, NPART=4;
//pedras do jogo
int i,j;
int tipopeca = 0;
int grade [20][10] = {0};
int peca [7][4] =
{
	{1,3,5,7},
	{2,4,5,7},
	{3,5,4,6},
	{3,5,4,7},
	{2,3,5,7},
	{3,5,7,6},
	{3,2,4,5}
};
//ponteiros dos objetos alegro
ALLEGRO_SAMPLE *intro, *mover, *linha, *cair, *virar;
ALLEGRO_BITMAP *buffer, *itens,*img;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

int main(int argc, char **argv)
{
	//inicialização
	al_install_system(ALLEGRO_VERSION_INT, atexit);
	al_install_keyboard();
	bool redraw = true;
	//variaveis locais
	timer = al_create_timer((1.0/60));
	display = al_create_display(WIDTH,HEIGHT);
	buffer = al_create_bitmap (WIDTH,HEIGHT);
	intro=al_load_sample("../sons/seusom.wav");
	mover=al_load_sample("../sons/seusom.wav");
	linha=al_load_sample("../sons/seusom.wav");
	cair=al_load_sample("../sons/seusom.wav");
	virar=al_load_sample("../sons/seusom.wav");
	event_queue = al_create_event_queue();
	//criando bloco
	img=al_create_bitmap(24,24);
	al_set_target_bitmap(img);
	al_clear_to_color(al_map_rgb(255, 225, 255));


	al_set_target_bitmap(al_get_backbuffer(display));

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	criaforma();

	while(1)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(event_queue, &evento);
			
		if(evento.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
		}
		else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) //fim da verificação do loop
		{
			redraw = false;
			for (int i = 0; i < NPART; i++)
			{
				al_draw_bitmap(img, posicao_a[i].x*WDT, posicao_a[i].y*WDT, 0);   
			}
			al_flip_display();
		}
	}
	//limpeza
	al_destroy_bitmap(img);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}
void criaforma()
{
	for (int i = 0; i < NPART; i++)
	{
		posicao_a[i].x = peca[tipopeca][i] % 2;
		posicao_a[i].y = peca[tipopeca][i] / 2;
	}
}