#include "Result.h"
#include <DxLib.h>

Result::Result() {
	gold = 0;
	
	LoadDivGraph("number128.png", 10, 10, 1, 128, 128, hud);
}

void Result::draw(char keys[255]) {
	if (keys[KEY_INPUT_UP] == 1) {
		gold += 1;
	}
	if (keys[KEY_INPUT_DOWN] == 1) {
		gold -= 1;
	}
	if (keys[KEY_INPUT_RIGHT] == 1) {
		gold += 14;
	}
	if (keys[KEY_INPUT_LEFT] == 1) {
		gold -= 15;
	}
	
	DrawGraph(30, 30, hud[gold / 1000 % 10], TRUE);
	DrawGraph(30 + 128, 30, hud[gold / 100 % 10], TRUE);////timer / 50 % 360 / 60 % 100 / 10], true);
	DrawGraph(30 + 128 * 2, 30, hud[gold / 10 % 10], TRUE);
	DrawGraph(30 + 128 * 3, 30, hud[gold % 10], TRUE);
}
