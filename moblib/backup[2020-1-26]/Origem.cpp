// biblioteca allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_primitives.h>
// spritesheet - animacao - movimentacao - colisao
#include "main_header.h"


//variaveis allegro

ALLEGRO_DISPLAY *screen;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *playerSheet;


int main(int argc,char **argv) {

	SpriteSheet bird(576*2,384*2,12,8);
	SpriteAnimation birdAnim(3,1,2);
	SpriteMoviment birdMov(100,100);

	direction(&birdMov,200,200,3);

	(al_init_native_dialog_addon()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init_native_dialog_addon()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	(al_init()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	(al_init_image_addon()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init_image_addon()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	(al_init_primitives_addon()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init_primitives_addon()", NULL, ALLEGRO_MESSAGEBOX_ERROR);

	screen = al_create_display(1080, 720);
	timer = al_create_timer(0.016);
	playerSheet = al_load_bitmap("C:/Users/bd88/Google Drive/recursos/sprites-modelos/bird2x.png");

	bool end = false;
	short int timing = 120;

	while (!end && timing) {
		timing--;
		al_clear_to_color(black);

		usint frm = anim(&birdAnim);

		al_draw_bitmap_region(playerSheet, bird.cellsX[frm], bird.cellsY[frm], bird.cellWidth, bird.cellHeight, birdMov.x, birdMov.y, NULL);
		run(&birdMov);

		al_flip_display();


		al_rest(0.016);
	}
	return 0;
}