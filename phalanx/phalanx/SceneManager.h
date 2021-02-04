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

	int mapGraph;
	int ui1;
	int ui2;
	int title1;
	int title2;

	int titleBGM;
	int inGameBGM;

public:
	SceneManager();
	
	void change(char keys[255],char oldkeys[255],Player*player,Enemy*enemy[81],Friend*friends[9]);
};

