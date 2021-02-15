#pragma once
#include"Player.h"
#include"Enemy.h"
#include"Friend.h"
class SceneManager
{
private:
	enum scene {
		title,
		play,
		result
	};
	int isEnd;
	enum scene sc;
	int hud[10];
	int gold;

	int mapGraph;
	int ui1;
	int ui2;
	int title1;
	int title2;
	int resultMoji;
	int resultBack;

	int titleBGM;
	int inGameBGM;

	int oldEnemyisAlive[72];

public:
	SceneManager();
	//
	void change(char keys[255],char oldkeys[255],Player* player,Enemy* enemy[72],Friend* friends[64],int MousePosX,int MousePosY,int MouseLeft,int WIN_WIDTH,int WIN_HEIGHT);
	void Killbonas(Enemy*enemy[72]);
};

