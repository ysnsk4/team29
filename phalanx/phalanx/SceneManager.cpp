#include "SceneManager.h"
#include "DxLib.h"

SceneManager::SceneManager() {
	sc = title;
	isEnd = 0;
	LoadDivGraph("resource/number128.png", 10, 10, 1, 128, 128, hud);
	gold = 0;

	mapGraph = LoadGraph("resource/map1.png");
	ui1 = LoadGraph("resource/scroll.png");
	ui2 = LoadGraph("resource/number.png");
	title1 = LoadGraph("resource/title.png");
	title2 = LoadGraph("resource/title2.png");
	titleBGM = LoadSoundMem("resource/title.mp3");
	inGameBGM = LoadSoundMem("resource/inGame.mp3");
	resultBack = LoadGraph("resource/scroll2.png");
	resultMoji= LoadGraph("resource/result.png");

	for (int i = 0; i < 72; i++)
	{
		oldEnemyisAlive[i] = 1;
	}
}
//
void SceneManager::change(char keys[255], char oldkeys[255], Player* player, Enemy* enemy[72], Friend* friends[64],int MousePosX,int MousePosY,int MouseLeft,int WIN_WIDTH,int WIN_HEIGHT) {
	if (isEnd == 0) {
		switch (sc) {
		case title:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				sc = play;
			}
			if (CheckSoundMem(inGameBGM) == 1)
			{
				StopSoundMem(inGameBGM);
			}
			if (CheckSoundMem(titleBGM) == 0)
			{
				PlaySoundMem(titleBGM, DX_PLAYTYPE_BACK, true);
			}
			DrawGraph(0, 0, title2, true);

			break;
		case play:
			if (CheckSoundMem(titleBGM) == 1)
			{
				StopSoundMem(titleBGM);
			}
			if (CheckSoundMem(inGameBGM) == 0)
			{
				PlaySoundMem(inGameBGM, DX_PLAYTYPE_BACK, true);
			}
			
			for (int i = 0; i < 72; i++)
			{
				oldEnemyisAlive[i] = enemy[i]->getisAlive();
			}
			if (player->getHP()<=0) {
				sc = result;
			}
			// �X�V����

			GetMousePoint(&MousePosX, &MousePosY);
			GetMouseInput();
			MouseLeft = MOUSE_INPUT_LEFT;

			player->move(keys, WIN_WIDTH, WIN_HEIGHT);
			player->Defence(enemy,WIN_HEIGHT);
			player->grabFriend(friends);

			/*if(GetMouseInput()&&MOUSE_INPUT_LEFT!=0)
			{
			}*/
			for (int i = 0; i < 64; i++)
			{
				friends[i]->update(enemy);
			}

			for (int i = 0; i < 72; i++)
			{
				enemy[i]->update(friends);
			}

			for (int i = 0; i < 72; i++)
			{

				if (oldEnemyisAlive[i] == 1 && enemy[i]->getisAlive() == 0)
				{
					gold += 10;
				}
			}
			// �`�揈��
			DrawGraph(0, 0, mapGraph, true);
			DrawGraph(WIN_WIDTH - 480, 0, ui1, true);
			for (int i = 0; i < 72; i++)
			{
				enemy[i]->draw();
			}
			for (int i = 0; i < 64; i++) {
				friends[i]->draw();
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

			int HPcolor;
			if (player->getHP() >= 400)
			{
				HPcolor = GetColor(0, 255, 0);
			}
			else if (player->getHP() < 400 && player->getHP() >= 200)
			{
				HPcolor = GetColor(255, 255, 0);
			}
			else if (player->getHP() < 200 )
			{
				HPcolor = GetColor(255, 0, 0);
			}
			DrawBox(0, 0, player->getHP(), 10, HPcolor, true);

			break;
		case result:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				sc = title;
			}
			DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), true);
			DrawGraph(0, 0, resultBack, TRUE);
			DrawGraph(0, 0, resultMoji, TRUE);
			DrawGraph(WIN_WIDTH / 2 - 128 * 2, WIN_HEIGHT/2-64, hud[gold / 1000 % 10], TRUE);
			DrawGraph(WIN_WIDTH / 2 - 128 , WIN_HEIGHT/2-64, hud[gold / 100 % 10], TRUE);////timer / 50 % 360 / 60 % 100 / 10], true);
			DrawGraph(WIN_WIDTH / 2 , WIN_HEIGHT/2-64, hud[gold / 10 % 10], TRUE);
			DrawGraph(WIN_WIDTH / 2 + 128 , WIN_HEIGHT/2-64, hud[gold % 10], TRUE);

			break;
		}
	}
}

void SceneManager::Killbonas(Enemy* enemy[72])
{
	

}