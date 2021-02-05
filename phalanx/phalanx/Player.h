#pragma once
#include"Friend.h"
#include"Enemy.h"
class Player
{
private:
	int posX;
	int posY;
	int radius;
	int speed;
	int Range;
	int isGrab;
	int HP;
	int Gold;

	int MousePosX = 0;
	int MousePosY = 0;
	int MouseLeft = 0;
	int oldMousePosX;
	int oldMousePosY;
	int oldMouseLeft;

	int playerGraph;
public:
	Player(int posX, int posY, int radius, int speed,int Range);
	~Player();

	void update();
	void draw();
	void Defence(Enemy*enemy[72],int WIN_HEIGHT);

	void move(char keys[255], int WIN_WIDTH, int WIN_HEIGHT);
	void grabFriend(Friend* SolderF[9]);

	int getPosX();
	int getPosY();
	int getRadius();
	int getSpeed();
	int getRange();
	int getHP();

	void setPosX(int posX);
	void setPosY(int posY);
	void setRadius(int radius);
	void setSpeed(int speed);
	void setRange(int Range);
	void setHP(int HP);
	
};

