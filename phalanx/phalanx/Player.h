#pragma once
#include"Friend.h"
class Player
{
private:
	int posX;
	int posY;
	int radius;
	int speed;
	int Range;
	int isGrab;

	int MousePosX = 0;
	int MousePosY = 0;
	int MouseLeft = 0;
	int oldMousePosX;
	int oldMousePosY;
	int oldMouseLeft;
public:
	Player(int posX, int posY, int radius, int speed,int Range);
	~Player();

	void update();
	void draw();

	void move(char keys[255], int WIN_WIDTH, int WIN_HEIGHT);
	void grabFriend(Friend* SolderF[9]);

	int getPosX();
	int getPosY();
	int getRadius();
	int getSpeed();
	int getRange();

	void setPosX(int posX);
	void setPosY(int posY);
	void setRadius(int radius);
	void setSpeed(int speed);
	void setRange(int Range);
};

