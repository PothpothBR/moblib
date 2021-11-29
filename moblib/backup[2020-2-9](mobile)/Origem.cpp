// biblioteca allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_primitives.h>
// spritesheet - animacao - movimentac#include "main_header.h"

#include "main_header.h"
// variaveis allegro
ALLEGRO_DISPLAY *screen;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *playerSheet;
ALLEGRO_BITMAP *seta;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT ev;
ALLEGRO_MOUSE_STATE stateMouse;

int main(int argc, char **argv)
{
    
    SpriteMovimentStance buttonExit(980,0);
    SpriteFormat objbuttonExit(&buttonExit, 100,100);
    
	SpriteMovimentStance buttonUp(800, 100);
    SpriteSheet bird(576 * 2, 384 * 2, 12, 8);
	SpriteMoviment birdMov(100, 100);
	SpriteAnimation birdAnim(3, 0, ANIMATION_FLIP, 40, 0);

	SpriteMoviment boxM(200, 200);
	SpriteSheet boxS(100, 100, 1, 1);

	SpriteMoviment boxM2(500, 500);
	SpriteSheet boxS2(100, 100, 1, 1);

	SpriteFormat boxF(&boxM, &boxS);
	SpriteFormat boxF2(&boxM2, &boxS2);

	SpriteMovimentKeys player(100, 100, 5);
	SpriteMovimentClick mouse(100, 100, 2);
    SpriteFormat objmouse(&mouse,1,1);


	direction(&boxM, 500, 500, 1);
	direction(&boxM2, 200, 200, 1);
	direction(&birdMov, 200, 200, 0.5);

	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_touch_input();

	queue = al_create_event_queue();
	screen = al_create_display(1080, 720);
	timer = al_create_timer(0.016);
	playerSheet = al_load_bitmap("bird2x.png");
    seta = al_load_bitmap("seta.png");
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_touch_input_event_source());

	bool end = false;

	float x = 50, y = 110, r = 80, x2 = 300, y2 = 110, r2 = 80;

	while (!end)
	{

		al_wait_for_event_timed(queue, &ev, 0.16);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			al_get_mouse_state(&stateMouse);

			if (stateMouse.buttons & 1)
			{
				mouse.activeLEFT = true;
				mouse.x = stateMouse.x;
				mouse.y = stateMouse.y;
			}
		}

		if (ev.type == ALLEGRO_EVENT_TOUCH_BEGIN)
		{
			al_get_mouse_state(&stateMouse);
			mouse.activeLEFT = true;
			mouse.x = stateMouse.x;
			mouse.y = stateMouse.y;
			
			isolatedCollision(&objmouse,&objbuttonExit);
			mouse.setTrace(mouse.x,mouse.y);
			if(mouse.colid) return 1;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{

			if (ev.keyboard.keycode == ALLEGRO_KEY_W)
			{
				player.activeUP = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
			{
				player.activeDOWN = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A)
			{
				player.activeLEFT = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_D)
			{
				player.activeRIGHT = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				end = !end;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_W)
			{
				player.activeUP = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
			{
				player.activeDOWN = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A)
			{
				player.activeLEFT = false;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_D)
			{
				player.activeRIGHT = false;
			}
		}
		x++;
		usint frm = anim(&birdAnim);

		// al_draw_circle(x, y, r, purple, 2);
		// al_draw_circle(x2, y2, r2, gold, 2);

		// testcriclcold(x, y, r, x2, y2, r2);

		al_draw_rectangle(player.x, player.y, player.x + 50, player.y + 50, red, 5);
		run(&player);


		al_draw_filled_rectangle(980,0,1080,100,smokyblack);
		
        al_draw_rectangle(980,0,1080,100,darkscarlet,5);
		al_draw_bitmap(seta,243,1540,0);
        
        al_draw_filled_circle(mouse.getTraceX(0),mouse.getTraceY(0),10,purple);
        /*al_draw_filled_circle(mouse.getTraceX(2),mouse.getTraceY(2),9,crimson);
        al_draw_filled_circle(mouse.getTraceX(3),mouse.getTraceY(3),8,outerspace);
        al_draw_filled_circle(mouse.getTraceX(4),mouse.getTraceY(4),7,arsenic);
        al_draw_filled_circle(mouse.getTraceX(5),mouse.getTraceY(5),6,aeroblue);
        al_draw_filled_circle(mouse.getTraceX(6),mouse.getTraceY(6),5,green);
        al_draw_filled_circle(mouse.getTraceX(7),mouse.getTraceY(7),4,gold);
        al_draw_filled_circle(mouse.getTraceX(8),mouse.getTraceY(8),3,red);
        al_draw_filled_circle(mouse.getTraceX(9),mouse.getTraceY(9),2,gray);
        al_draw_filled_circle(mouse.getTraceX(10),mouse.getTraceY(10),1,blue);
        */
		// al_draw_rectangle(boxM.x, boxM.y, boxM.x + boxS.getCellWidth(),
		// boxM.y + boxS.getCellHeight(), deepskyblue, 5);
		// al_draw_rectangle(boxM2.x, boxM2.y, boxM2.x + boxS2.getCellWidth(), 
		// boxM2.y + boxS2.getCellHeight(), lightseagreen, 5);

		// al_draw_bitmap_region(playerSheet, bird.getCellsX(frm),
		// bird.getCellsY(frm), bird.getCellWidth(), bird.getCellHeight(),
		// birdMov.x, birdMov.y, NULL);

		run(&birdMov);
		run(&boxM);
		run(&boxM2);

		collision(&boxF);



		al_flip_display();
		al_clear_to_color(cinzafundo);

	}
	return 0;
}
