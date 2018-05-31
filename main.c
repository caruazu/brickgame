//cria um display e o desativa ao apertar qualquer botão
#include<stdio.h>
#include <allegro5/allegro.h>

int main(int argc, char const *argv[])
{
  ALLEGRO_DISPLAY * display; //ponteiro para a tela
  ALLEGRO_EVENT_QUEUE *queue;
  
  al_install_system(ALLEGRO_VERSION_INT, atexit); //inicia o alegro
  al_install_keyboard();
  

  display= al_create_display(600,800);
  queue= al_create_event_queue();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));

  bool running = true;   // Looping para pegar os eventos de teclado
  while (running)
  {
    al_flip_display();
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      running = false;
    }
  }

  al_destroy_display(display);
  al_uninstall_keyboard();

  return 0;
}