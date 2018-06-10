#include <stdio.h>
#include <allegro5/allegro.h>
/* Propoção do jogo */
/*
#define TAMANHO 200
const int LARGURA=TAMANHO;
const int ALTURA=TAMANHO*2;
const int LINHA=(TAMANHO/2)/5;
const int COLUNA=((TAMANHO/2)*2)/5;
const int LARGURA_BLOCO=((TAMANHO-(TAMANHO/20))/2)/5;
const int ALTURA_BLOCO=((TAMANHO-(TAMANHO/20))/2)/5;

*/
#define LENTIDAO 0.2
const int LARGURA=200;
const int ALTURA=400;
const int LINHA=20;
const int COLUNA=10;
const int LARGURA_BLOCO=19;
const int ALTURA_BLOCO=19;
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
int TIPO = 6;
//pecas
struct posicao
{
    int l,c;
}
posicao_a[4];
int peca [7][4]=
{
    { 3, 4, 5, 6},
    { 4, 5,14,15},
    { 3, 4, 5,15},
    { 3, 4, 5,13},
    { 4, 5,13,14},
    { 3, 4,14,15},
    { 3, 4, 5,14}
};
bool grade [200]={false};

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}


void generateNewPeca()
{
    peca[0][0] = 3;
    peca[0][1] = 4;
    peca[0][2] = 5;
    peca[0][3] = 6;

    peca[1][0] = 4;
    peca[1][1] = 5;
    peca[1][2] = 14;
    peca[1][3] = 15;

    peca[2][0] = 3;
    peca[2][1] = 4;
    peca[2][2] = 5;
    peca[2][3] = 15;

    peca[3][0] = 3;
    peca[3][1] = 4;
    peca[3][2] = 5;
    peca[3][3] = 13;

    peca[4][0] = 4;
    peca[4][1] = 5;
    peca[4][2] = 13;
    peca[4][3] = 14;

    peca[5][0] = 3;
    peca[5][1] = 4;
    peca[5][2] = 14;
    peca[5][3] = 15;

    peca[5][0] = 3;
    peca[5][1] = 4;
    peca[5][2] = 5;
    peca[5][3] = 14;

    TIPO = random_number(0,6);
}

void renderToGrade()
{
  for (int i = 0; i < 4; ++i)
  {
    grade[peca[TIPO][i]] = true;
  }

  generateNewPeca();
}

bool canIMove(int pos)
{
  if (pos < 189 && !grade[pos+10])
  {
    return true;
  }
  return false;
}

/* funçoes */
bool descer(void)
{
  /*
      printf("%d\t",peca[TIPO][0]);
      printf("%d\t",peca[TIPO][1]);
      printf("%d\t",peca[TIPO][2]);
      printf("%d\n",peca[TIPO][3]);
   */

  // for (int i = 0; i < 4; ++i)
  // {
  //  if (peca[TIPO][3] < 189)
  //  {
  //    peca[TIPO][i]= peca[TIPO][i] +10;
  //  }
  // }


  for (int i = 0; i < 4; ++i)
  {
    if(!canIMove(peca[TIPO][i]))
    {
      return false;
    }
  }

  for (int i = 0; i < 4; ++i)
  {
    peca[TIPO][i]= peca[TIPO][i] +10;
  }

  return true;
}



int posToLine(int pos)
{
  return pos/10;
}

int posToColl(int pos)
{
  return pos%10;
}

void criaforma(void)
{
  for (int i = 0; i < 4; i++)
  {
    // posicao_a[i].l = peca[TIPO][i] /10;
    // posicao_a[i].c = peca[TIPO][i] %10;
    posicao_a[i].l = posToLine(peca[TIPO][i]);
    posicao_a[i].c = posToColl(peca[TIPO][i]);
  }
}
void drawGrade()
{
  for (int i= 0; i < 200; i++)
  {
    if (grade[i])
    {
      al_draw_bitmap(bloco,posToColl(i)*20, posToLine(i)*20 , 0);
    }
  }
}
int inicie()
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
  temporizador= al_create_timer(LENTIDAO);
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

  return 0;
}
bool controles(void);
int main(int argc, char const *argv[])
{
  grade[184] = grade[185] = grade[186] = grade[195] = true;
  if (inicie())
  {
    return 0; /*erro*/
  }
  /* cor do display */
  al_clear_to_color(al_map_rgb(255, 0, 0));
  /* mostra no display a imagem criada no buffer */
  al_flip_display();
  /* inicia a contagem*/
  al_start_timer(temporizador);
  /*loop do jogo*/
   //monta formas
  bool sair= false;
  while(!sair)
  {
    sair=controles();
    /* se nenhum evento foi ativado */
    if(redraw&&al_is_event_queue_empty(eventos))
    {
      criaforma();
      redraw=false;
      al_clear_to_color(al_map_rgb(255, 255, 255));

      drawGrade();

      for (int i = 0; i < 4; i++)
      {
        al_draw_bitmap(bloco, posicao_a[i].c*20, posicao_a[i].l*20, 0);
      }
      al_flip_display();

      if(!descer()){
        renderToGrade();
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

bool checkBoundsLeft()
{
    for(int i = 0; i < 4; i++){
        if(posToColl(peca[TIPO][i]) == 0 && posToColl(peca[TIPO][i]-1) == 9)
        {
            return false;
        }
    }

    return true;
}

bool checkBoundsRight()
{
    for(int i = 0; i < 4; i++){
        if(posToColl(peca[TIPO][i]) == 9 && posToColl(peca[TIPO][i]+1) == 0)
        {
            return false;
        }
    }

    return true;
}


bool controles(void)
{
  ALLEGRO_EVENT evnt0;
  al_wait_for_event(eventos, &evnt0);
  if(evnt0.type == ALLEGRO_EVENT_TIMER)
  {
    if(KEY_SPACE)
    {
     // printf("HOLD\t\t");
      //printf("space\n");
    }
    if(KEY_DOWN)
    {
      //printf("HOLD\t\t");
      //printf("down\n");
    }
    if(KEY_LEFT)
    {
     // printf("HOLD\t\t");
     // printf("left\n");
    }
    if(KEY_RIGHT)
    {
      //printf("HOLD\t\t");
     // printf("right\n");
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
            //printf("KEY_DOWN\t");
            //printf("space\n");
            break;
          case ALLEGRO_KEY_DOWN:
            KEY_DOWN = true;
            //printf("KEY_DOWN\t");
            //printf("down\n");
            break;
          case ALLEGRO_KEY_LEFT:
            KEY_LEFT = true;
            if (checkBoundsLeft())
            {
                for (int i = 0; i < 4; ++i)
                {
                  peca[TIPO][i]=peca[TIPO][i]-1;
                }
            }
            //printf("KEY_DOWN\t");
            //printf("left\n");
            break;
          case ALLEGRO_KEY_RIGHT:
            KEY_RIGHT = true;
            if (checkBoundsRight())
            {
                for (int i = 0; i < 4; ++i)
                {
                  peca[TIPO][i]=peca[TIPO][i]+1;
                }
            }
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
             // printf("KEY_UP\t\t");
              //printf("space\n");
              break;
            case ALLEGRO_KEY_DOWN:
              KEY_DOWN = false;
             // printf("KEY_UP\t\t");
             // printf("down\n");
              break;
            case ALLEGRO_KEY_LEFT:
              KEY_LEFT = false;
             // printf("KEY_UP\t\t");
              //printf("left\n");
              break;
            case ALLEGRO_KEY_RIGHT:
              KEY_RIGHT = false;
              //printf("KEY_UP\t\t");
              //printf("right\n");
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
