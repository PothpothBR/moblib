#include "object.h"

std::vector<int> tst;


int main() {

    tst.push_back(22);
    tst[0];

	Object test(100,100,20,20,4,4,OBJECT_RECT);
	test.addAnimation(3,0,ANIMATION_SPIN);

	return 0;
}



/*
    Debug normal...

    ─┬───> created obj <Sprite_secondFloor>
     ├─> count: -1
     ├─> start: 0
     ├─> end: 2
     ├─> interval: 1
     ├─> jump: 0
     ├─> direction: 0
     ├─> rangeOfCells: 3
     ├─> flip: -1
     ├─> step: 1

    ...and spin.
    ─┬───> created obj <Sprite_secondFloor>
     ├─> count: 1
     ├─> start: 0
     ├─> end: 2
     ├─> interval: 1
     ├─> jump: 0
     ├─> direction: 2
     ├─> rangeOfCells: 3
     ├─> flip: -1
     ├─> step: 1
*/

