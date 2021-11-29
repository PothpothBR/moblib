// biblioteca allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_primitives.h>
// spritesheet - animacao - movimentacao - colisao
#include "main_header.h"


//variaveis allegro
ALLEGRO_DISPLAY *screen;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *playerSheet;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT ev;
ALLEGRO_MOUSE_STATE stateMouse;

int main(int argc,char **argv) {

	SpriteSheet bird(576*2,384*2,12,8);
	SpriteMoviment birdMov(100,100);
	SpriteAnimation birdAnim(3, 0,ANIMATION_FLIP,40,0);

	SpriteMoviment boxM(200, 200);
	SpriteSheet    boxS(100, 100, 1, 1);

	SpriteMoviment boxM2(500, 500);
	SpriteSheet    boxS2(100, 100, 1, 1);

	SpriteFormat   boxF(&boxM, &boxS);
	SpriteFormat   boxF2(&boxM2, &boxS2);

	SpriteMovimentKeys player(100, 100,5);
	SpriteMovimentClick mouse(0,0);

	direction(&boxM, 500, 500, 1);
	direction(&boxM2, 200, 200, 1);
	direction(&birdMov, 200, 200, 0.5);

	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	queue = al_create_event_queue();
	screen = al_create_display(1080, 720);
	timer = al_create_timer(0.016);
	playerSheet = al_load_bitmap("C:/Users/bd88/Google Drive/recursos/sprites-modelos/bird2x.png");

	al_register_event_source(queue,al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	bool end = false;

	float
		x=50, y=50, r=30,
		x2=200, y2=50, r2=30;

	while (!end) {

		al_wait_for_event_timed(queue, &ev,0.16);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&stateMouse);

			if (stateMouse.buttons & 1) {
				mouse.x = stateMouse.x;
				mouse.y = stateMouse.y;
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
				player.activeUP=true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
				player.activeDOWN = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
				player.activeLEFT = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
				player.activeRIGHT = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				end = !end;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
				player.activeUP = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
				player.activeDOWN = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
				player.activeLEFT = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
				player.activeRIGHT = false;
			}
		}
		x++;
		usint frm = anim(&birdAnim);

		al_draw_circle(x, y, r, purple, 2);
		al_draw_circle(x2, y2, r2, gold, 2);

		//testcriclcold(x, y, r, x2, y2, r2);

		al_draw_rectangle(player.x,player.y, player.x+50, player.y+50, red, 5 );
		run(&player);
		//al_draw_rectangle(boxM.x, boxM.y, boxM.x + boxS.getCellWidth(), boxM.y + boxS.getCellHeight(), deepskyblue, 5);
		//al_draw_rectangle(boxM2.x, boxM2.y, boxM2.x + boxS2.getCellWidth(), boxM2.y + boxS2.getCellHeight(), lightseagreen, 5);

		//al_draw_bitmap_region(playerSheet, bird.getCellsX(frm), bird.getCellsY(frm), bird.getCellWidth(), bird.getCellHeight(), birdMov.x, birdMov.y, NULL);
		
		run(&birdMov);
		run(&boxM);
		run(&boxM2);

		collision(&boxF);


		al_flip_display();
		al_clear_to_color(cinzafundo);

	}
	return 0;
}