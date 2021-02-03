#include "SceneManager.h"
#include "DxLib.h"

SceneManager::SceneManager() {
	sc = title;
	isEnd = 0;
	
	mapGraph = LoadGraph("resource/map1.png");
	ui1 = LoadGraph("resource/scroll.png");
	ui2 = LoadGraph("resource/number.png");
	title1 = LoadGraph("resource/title.png");
	title2 = LoadGraph("resource/title2.png");

}

void SceneManager::change(char keys[255], char oldkeys[255], Player* player, Enemy* enemy[81], Friend* friends[9]) {
	if (isEnd == 0) {
		switch (sc) {
		case title:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				sc = play;
			}

			DrawGraph(0, 0, title2, true);

			break;
		case play:
			/*if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				Scene = 3;
			}*/
			// çXêVèàóù

			GetMousePoint(&MousePosX, &MousePosY);
			GetMouseInput();
			MouseLeft = MOUSE_INPUT_LEFT;

			player->move(keys, WIN_WIDTH, WIN_HEIGHT);

			player->grabFriend(FriendSolder);

			/*if(GetMouseInput()&&MOUSE_INPUT_LEFT!=0)
			{
			}*/
			for (int i = 0; i < 9; i++)
			{
				FriendSolder[i]->update(EnemySolder);
			}

			for (int i = 0; i < 81; i++)
			{
				EnemySolder[i]->update(FriendSolder);
			}

			// ï`âÊèàóù
			DrawGraph(0, 0, mapGraph, true);
			DrawGraph(WIN_WIDTH - 480, 0, ui1, true);
			for (int i = 0; i < 81; i++)
			{
				EnemySolder[i]->draw();
			}
			for (int i = 0; i < 9; i++) {
				FriendSolder[i]->draw();
			}
			/*if (
				(FriendSolder[8]->getPosX() - MousePosX) * (FriendSolder[8]->getPosX() - MousePosX) + (FriendSolder[8]->getPosY() - MousePosY) * (FriendSolder[8]->getPosY() - MousePosY)
				<= FriendSolder[8]->getRadius()* FriendSolder[8]->getRadius()
			)
			{
				DrawFormatString(5, 5, GetColor(0, 200, 0), "grab now");
			}
			else
			{
				DrawFormatString(5, 5, GetColor(100, 0, 0), "free hand");
			}*/
			player->draw();



			break;
		case result:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				isEnd = 1;
			}
			break;
		}
	}
}
