#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
//funções
int velocidade ();
void girar ();
bool confere ();
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
bool rodando= true;
//pedras do jogo
int i,j;
int cor=0;
int passo = 0;
float pos_x=0;
int newPart= 0;
int nextPartX[4]={0};
int nextPartY[4]={0};
int nextPartCor= 0;
int nTimer= 6;
int tipopeca= 5;
int grade [20][10]= {0};
int peca [7][4]=
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
ALLEGRO_BITMAP *buffer, *itens,*bitmap;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue, *bunda = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_KEYBOARD_STATE keyState;

int main(int argc, char **argv)
{
	//inicialização
	al_install_system(ALLEGRO_VERSION_INT, atexit);	
	al_install_keyboard();
	al_get_keyboard_state(&keyState);

	//variaveis locais
	timer = al_create_timer((1.0/60));
	display = al_create_display(WIDTH,HEIGHT);
	buffer = al_create_bitmap (WIDTH,HEIGHT);
	intro=al_load_sample("../sons/seusom.wav");
	mover=al_load_sample("../sons/seusom.wav");
	linha=al_load_sample("../sons/seusom.wav");
	cair=al_load_sample("../sons/seusom.wav");
	virar=al_load_sample("../sons/seusom.wav");
	queue = al_create_event_queue();
	//criando bloco

	bitmap=al_create_bitmap(24,24);
	al_set_target_bitmap(bitmap);
	al_clear_to_color(al_map_rgb(255, 225, 255));
	

	al_set_target_bitmap(al_get_backbuffer(display));
	//registro de eventos
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	
	al_start_timer(timer);

	while(rodando)
	{
		control();
		
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		
		if(evento.type == ALLEGRO_EVENT_TIMER)
		{			
			
			velocidade();			
			al_clear_to_color(al_map_rgb(255,0,0));
			for (i = 0; i < NPART; i++)
			{				
				criaforma(); //monta formas
				al_draw_bitmap(bitmap, posicao_a[i].x*WDT, posicao_a[i].y*WDT, 0);
			}
			pos_x=0;
			al_flip_display();
		}

		if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			rodando= false;
		}
	}
	//limpeza
	al_destroy_bitmap(bitmap);
	al_uninstall_keyboard();
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	return 0;
}
void control (){
	al_get_keyboard_state(&keyState);
	if (al_key_down(&keyState,ALLEGRO_KEY_LEFT)){pos_x = -1;printf("control\n");}
	else if (al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){pos_x = 1;}

	for (i = 0; i < NPART; i++){
		posicao_b[i]=posicao_a[i];
		posicao_a[i].x += pos_x;
	}

	if (!confere()){
		for (i = 0; i < NPART; i++)	posicao_a[i]=posicao_b[i];
	}

}
bool confere (){
	for (i = 0; i < NPART; i++){
		if (posicao_a[i].x < 0 || posicao_a[i].x >= COL) return false;
		else if (posicao_a[i].y>= LIN|| grade[posicao_a[i].y][posicao_a[i].x] ){
			return false;
		}
		return true;
	}
}

int velocidade (){
	if (passo++ > nTimer){
		for (i = 0; i < NPART; i++){
			posicao_b[i]=posicao_a[i];
			posicao_a[i].y +=1;
		}
		criaforma();
		passo = 0;
	}
}
void criaforma(){
	if (!confere){
		for (i = 0; i < NPART; i++) 
		{
			
			grade[posicao_b[i].y][posicao_b[i].x] = cor;
		}
		tipopeca= rand()%7;
		if (newPart){
			cor=nextPartCor;
			for (i = 0; i < NPART; i++){
				posicao_a[i].x = nextPartX[i];
				posicao_a[i].y = nextPartY[i];
			}
		}
		nextPartCor = tipopeca+1;
		for (i = 0; i < NPART; i++){
			nextPartX[i] = peca[tipopeca][i] % 2;
			nextPartY[i] = peca[tipopeca][i] / 2;
		}
		newPart=1;
	}	
}