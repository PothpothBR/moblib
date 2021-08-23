// biblioteca allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_primitives.h>
// spritesheet - animacao - movimentacao - colisao
#include "moblib/moblib.h"


//variaveis allegro
ALLEGRO_DISPLAY *screen;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *playerSheet;
ALLEGRO_BITMAP *almap;
ALLEGRO_BITMAP *seta;
ALLEGRO_BITMAP *agua;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT ev;
ALLEGRO_MOUSE_STATE stateMouse;

int main(int argc, char **argv) {

	mlMovimentInstance buttonExit(1030, 0);
	mlFormat objbuttonExit(&buttonExit, 50, 50);

	mlMovimentInstance buttonUp(524, 644);
	mlMovimentInstance buttonDown(524, 678);
	mlMovimentInstance buttonLeft(490, 678);
	mlMovimentInstance buttonRight(558, 678);

	mlFormat objButtonUp(&buttonUp, 32, 32);
	mlFormat objButtonDown(&buttonDown, 32, 32);
	mlFormat objButtonLeft(&buttonLeft, 32, 32);
	mlFormat objButtonRight(&buttonRight, 32, 32);

	mlMovimentKeys player(100, 100, 2, 5, 3);
	mlFormat objplayer(&player, 50,50);
	mlMovimentTouch mouse(-10, -10);
	mlFormat objmouse(&mouse, 1, 1);

	mlSheet mapsht(1024,1024,32,32);
	
	mlObject bird;
	bird.initSheet(576, 384, 12, 8);
	bird.initAnimationInstance(3, ANIMATION_FLIP,8);
	bird.initMoviment(100, 100);
	bird.initAnimation(4);
	bird.addAnimation(0);
	bird.addAnimation(12);
	bird.addAnimation(24);
	bird.addAnimation(36);

	usint tilemap[5 * 5] = {
		32,33,33,33,34,
		64,65,65,65,66,
		64,65,65,65,66,
		64,65,65,65,66,
		96,97,97,97,98,
	};

	mlObject map;
	map.initMovimentKeys(100, 100,2);
	map.initSheet(1024, 1024, 32, 32);
	map.initMapping(5,5,tilemap);

	map.map->setAnimKey(2, 2, bird.getAnim(3));





	mlDirection(bird.mov, 600, 600, 1);
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_touch_input();

	queue = al_create_event_queue();
	screen = al_create_display(1080, 720);
	timer = al_create_timer(0.016);
	seta = al_load_bitmap("seta100x66.png");
	almap = al_load_bitmap("chao2-0.png");
	agua = al_load_bitmap("bird.png");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_touch_input_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool end = false;

	al_start_timer(timer);
	int pos = 0;
	while (!end) {

		al_wait_for_event(queue, &ev);
		al_get_mouse_state(&stateMouse);
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {


			if (stateMouse.buttons & 1) {
				mouse.activeLEFT = true;
				mouse.x = stateMouse.x;
				mouse.y = stateMouse.y;
				mlIsolatedCollision(&objmouse, &objbuttonExit);
				if (mouse.colid) return 1;

				if (mlIsolatedCollision(&objmouse, &objButtonUp)) { player.activeUP = true; }
				else if (mlIsolatedCollision(&objmouse, &objButtonDown)) { player.activeDOWN = true; }
				if (mlIsolatedCollision(&objmouse, &objButtonLeft)) { player.activeLEFT = true; }
				else if (mlIsolatedCollision(&objmouse, &objButtonRight)) { player.activeRIGHT = true; }
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			player.activeUP = false; 
			player.activeDOWN = false; 
			player.activeLEFT = false; 
			player.activeRIGHT = false; 
		mlDirection(bird.mov,ev.mouse.x + bird.sheet->getHandleX(4), ev.mouse.y + bird.sheet->getHandleY(4),3);
		}

		 else if (ev.type == ALLEGRO_EVENT_TOUCH_BEGIN) {

			mouse.activeLEFT = true;
			mouse.x = ev.touch.x;
			mouse.y = ev.touch.y;
			mlIsolatedCollision(&objmouse, &objbuttonExit);
			if (mouse.colid) return 1;

			if (mlIsolatedCollision(&objmouse, &objButtonUp)) { player.activeUP = true; }
			else if (mlIsolatedCollision(&objmouse, &objButtonDown)) { player.activeDOWN = true; }
			if (mlIsolatedCollision(&objmouse, &objButtonLeft)) { player.activeLEFT = true; }
			else if (mlIsolatedCollision(&objmouse, &objButtonRight)) { player.activeRIGHT = true; }

		}
		else if (ev.type == ALLEGRO_EVENT_TOUCH_END) {
			player.activeUP = false;
			player.activeDOWN = false;
			player.activeLEFT = false;
			player.activeRIGHT = false;
			mlDirection(bird.mov, ev.mouse.x + bird.sheet->getHandleX(4), ev.mouse.y + bird.sheet->getHandleY(4), 3);
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
				player.activeUP = true;
				map.movK->activeDOWN = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
				player.activeDOWN = true;
				map.movK->activeUP = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
				player.activeLEFT = true;
				map.movK->activeRIGHT = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
				player.activeRIGHT = true;
				map.movK->activeLEFT = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				end = !end;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
				player.activeUP = false;
				map.movK->activeDOWN = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
				player.activeDOWN = false;
				map.movK->activeUP = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
				player.activeLEFT = false;
				map.movK->activeRIGHT = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
				player.activeRIGHT = false;
				map.movK->activeLEFT = false;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
			mouse.setAutoXY(stateMouse.x, stateMouse.y);
			
			mlRun(&player);
			mlRun(bird.mov);
			mlRun(map.movK);
			player.setAutoTrace();
			
			pos = mlAnim(bird.getAnim(3));

			mlIsolatedCollision(&objplayer,0,0,1080,720);

		}
		else {
			al_flush_event_queue(queue);
		}
		

		al_draw_filled_rectangle(buttonExit.x, buttonExit.y, buttonExit.x + objbuttonExit.getWidth(), buttonExit.y + objbuttonExit.getHeight(), smokyblack);

		al_draw_rectangle(buttonExit.x, buttonExit.y, buttonExit.x + objbuttonExit.getWidth(), buttonExit.y + objbuttonExit.getHeight(), darkscarlet, 5);

		al_draw_rectangle(buttonUp.x, buttonUp.y, buttonUp.x + objButtonUp.getWidth(), buttonUp.y + objButtonUp.getHeight(), black, 1);
		al_draw_rectangle(buttonDown.x, buttonDown.y, buttonDown.x + objButtonDown.getWidth(), buttonDown.y + objButtonDown.getHeight(), black, 1);
		al_draw_rectangle(buttonLeft.x, buttonLeft.y, buttonLeft.x + objButtonLeft.getWidth(), buttonLeft.y + objButtonLeft.getHeight(), black, 1);
		al_draw_rectangle(buttonRight.x, buttonRight.y, buttonRight.x + objButtonRight.getWidth(), buttonRight.y + objButtonRight.getHeight(), black, 1);

		for (int x = 0;x < map.map->bufferWidth;x++) {
			for (int y = 0;y < map.map->bufferHeight;y++) {
				if (map.movK->x + x * map.sheet->getWidth() + map.sheet->getWidth() < 0 || map.movK->x + x * map.sheet->getWidth() > al_get_display_width(screen) ||
					map.movK->y + y * map.sheet->getHeight() + map.sheet->getHeight() < 0 || map.movK->y + y * map.sheet->getHeight() > al_get_display_height(screen)) {
					cout << "no draw:" << x << '-' << y << endl;
					continue;
				}
				al_draw_bitmap_region(
					almap,
					map.sheet->posX(map.map->getKey(x, y)),mapsht.posY(map.map->getKey(x, y)),
					map.sheet->getWidth(),map.sheet->getHeight(),
					map.movK->x+x*map.sheet->getWidth(), map.movK->y+y*map.sheet->getHeight(),NULL
				);
			}
		}

		al_draw_bitmap_region(agua, bird.sheet->posX(pos), bird.sheet->posY(pos),
			bird.sheet->getWidth(), bird.sheet->getHeight(),
			bird.mov->x, bird.mov->y,0);

		usint sizeModf = 1;

		al_draw_scaled_bitmap(seta, 0, 0, 100, 66,
			1080 / 2 - 100 * sizeModf / 2, 720 - 66 * sizeModf - 10, 100 * sizeModf, 66 * sizeModf, 1);

		for (int i = player.getTraceSize();i >= 0;i--) {
			if (player.getTraceX(i) == player.x && player.getTraceY(i) == player.y) continue;
			al_draw_rectangle(player.getTraceX(i), player.getTraceY(i), player.getTraceX(i) + 50, player.getTraceY(i) + 50, red, 4 - i);
		}

		al_draw_rectangle(player.x, player.y, player.x + 50, player.y + 50, red, 5);
		
		al_flip_display();
		al_clear_to_color(cinzafundo);

	}

	al_destroy_display(screen);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	map.map->destroyAnimKey(2,2);
	return 0;
}