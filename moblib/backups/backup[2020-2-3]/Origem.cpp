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
	SpriteMoviment birdMov(100,100);
	SpriteAnimation birdAnim(3, 0,ANIMATION_FLIP,40,0);

	SpriteMoviment boxM(200, 200);
	SpriteSheet    boxS(100, 100, 1, 1);

	SpriteMoviment boxM2(500, 500);
	SpriteSheet    boxS2(100, 100, 1, 1);

	SpriteFormat   boxF(&boxM, &boxS);
	SpriteFormat   boxF2(&boxM2, &boxS2);

	SpriteMoviment key(100, 100);
	direction(&key, 99, 101,1);

	std::cout << key.vuX << ' ' << key.vuY;
	std::cin.get();

	direction(&boxM, 500, 500, 1);
	direction(&boxM2, 200, 200, 1);
	direction(&birdMov, 200, 200, 0.5);

	(al_init_native_dialog_addon()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init_native_dialog_addon()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	(al_init()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	(al_init_image_addon()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init_image_addon()", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	(al_init_primitives_addon()) ? true : al_show_native_message_box(screen, "ERROR MESSAGE!", "Erro ao iniciar:", "al_init_primitives_addon()", NULL, ALLEGRO_MESSAGEBOX_ERROR);

	screen = al_create_display(1080, 720);
	timer = al_create_timer(0.016);
	playerSheet = al_load_bitmap("C:/Users/bd88/Google Drive/recursos/sprites-modelos/bird2x.png");

	bool end = false;

	float
		x=50, y=50, r=30,
		x2=200, y2=50, r2=30;


	while (!end) {
		x++;
		usint frm = anim(&birdAnim);

		al_draw_circle(x, y, r, purple, 2);
		al_draw_circle(x2, y2, r2, gold, 2);

		testcriclcold(x, y, r, x2, y2, r2);

		//al_draw_rectangle(boxM.x, boxM.y, boxM.x + boxS.getCellWidth(), boxM.y + boxS.getCellHeight(), deepskyblue, 5);
		//al_draw_rectangle(boxM2.x, boxM2.y, boxM2.x + boxS2.getCellWidth(), boxM2.y + boxS2.getCellHeight(), lightseagreen, 5);

		//al_draw_bitmap_region(playerSheet, bird.getCellsX(frm), bird.getCellsY(frm), bird.getCellWidth(), bird.getCellHeight(), birdMov.x, birdMov.y, NULL);
		
		run(&birdMov);
		run(&boxM);
		run(&boxM2);

		collision(&boxF);


		al_flip_display();
		al_clear_to_color(cinzafundo);

		al_rest(0.016);
	}
	return 0;
}