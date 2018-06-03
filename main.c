#include <stdio.h>
#include <allegro5/allegro.h>
int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *quadrado = NULL;
	ALLEGRO_BITMAP *quadrado1 = NULL;

	bool redraw = true;

	al_install_system(ALLEGRO_VERSION_INT, atexit);

	timer = al_create_timer((1.0/60));
	display = al_create_display(300,400);
	quadrado = al_create_bitmap(20,20);
	quadrado1 = al_create_bitmap(20,20);
	event_queue = al_create_event_queue();

	al_set_target_bitmap(quadrado);
	
	al_clear_to_color(al_map_rgb(255, 225, 255));
	al_set_target_bitmap(quadrado1);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_set_target_bitmap(al_get_backbuffer(display));
 
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_flip_display();
	al_start_timer(timer);

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

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false
			for (int i = 0; i < 15; ++i)
			{
				for (int j = 0; j < 20; ++j)
				{
					if ((i%2)^(j%2))
					{
						al_draw_bitmap(quadrado, i*20, j*20, 0);
					}
					else
					{
						al_draw_bitmap(quadrado1, i*20, j*20, 0);
					}
				}				
			}
			
			al_flip_display();
		}
	}
 
	al_destroy_bitmap(quadrado);
	al_destroy_bitmap(quadrado1);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}