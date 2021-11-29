#include "_frontend.h"


// cache temporario
class _tempCache {
public:
	_tempCache() {

	}
};

// nucleo do programa
class _gameCore {
public:
	_frontEnd frontEnd;
	_tempCache tempCache;
	
	// junta as 3 classes <_frontEnd | _backEnd | _tempCache> iniciando-as
	_gameCore() {

	}

	void mainLoop() {

		mlMovimentInstance targettest;
		targettest.x = 300;
		targettest.y = 300;
		mlFormat target(&targettest, 100, 10);

		al_start_timer(frontEnd.sourceEvents.timer);

		while (!frontEnd.endGame){

			frontEnd.events();

			if (frontEnd.sourceEvents.ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(frontEnd.sourceEvents.queue)) {

				frontEnd.backEnd.player.switchAnimation();

				/*if (mlIsolatedCollision(&target, frontEnd.backEnd.player.mouse.x, frontEnd.backEnd.player.mouse.y, 2, 2) && frontEnd.backEnd.player.mouse_is_pressed) {
					frontEnd.backEnd.player.attack(&target); }*/

				mlRun(frontEnd.backEnd.player.Player.moviment,frontEnd.backEnd.player.Player.format,&target,false);
				
				if (!frontEnd.backEnd.player.rangedAttack.empty()) {
					for (int i = 0;i < frontEnd.backEnd.player.rangedAttack.size();i++) {
						mlRun(&frontEnd.backEnd.player.rangedAttack[i]);
					}
				}
				
			}

			al_draw_bitmap_region(frontEnd.data.playersheet,
				frontEnd.backEnd.player.Player.sheet->cellX[frontEnd.backEnd.player.player_anim_pos], frontEnd.backEnd.player.Player.sheet->cellY[frontEnd.backEnd.player.player_anim_pos],
				frontEnd.backEnd.player.Player.sheet->cellWidth, frontEnd.backEnd.player.Player.sheet->cellHeight,
				frontEnd.backEnd.player.Player.moviment->x, frontEnd.backEnd.player.Player.moviment->y, NULL);

			al_draw_filled_rectangle(*target.x,*target.y, *target.x+target.width, *target.y+target.height,al_map_rgb(255,0,0));

			al_flip_display();
			al_clear_to_color(al_map_rgb(22,24,28));
		}
		
	}

}gameCore;

int main() {

	gameCore.mainLoop();

	return 0;
}
