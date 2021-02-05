#include "Result.h"
#include <DxLib.h>

Result::Result() {
	
	LoadDivGraph("number128.png", 10, 10, 1, 128, 128, hud);
}

void Result::draw(int gold) {

	
	DrawGraph(30, 30, hud[gold / 1000 % 10], TRUE);
	DrawGraph(30 + 128, 30, hud[gold / 100 % 10], TRUE);////timer / 50 % 360 / 60 % 100 / 10], true);
	DrawGraph(30 + 128 * 2, 30, hud[gold / 10 % 10], TRUE);
	DrawGraph(30 + 128 * 3, 30, hud[gold % 10], TRUE);
}
