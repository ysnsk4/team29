#pragma once
#include "Solder.h"
class Enemy : public Solder
{
private:
	int isAlive;
	int EnemySolder;
public:
	static int EnemyCount;

	Enemy(int posX, int posY, int radius, int speed, int HP, int DEF, int ATK, int Range,int isAlive);
	~Enemy();

	void update();
	void draw();
	void move();
	void Attack();

	int getPosX();
	int getPosY();
	int getRadius();
	int getSpeed();
	int getHP();
	int getDEF();
	int getATK();
	int getRange();
	int getisAlive();

	void setPosX(int posX);
	void setPosY(int posY);
	void setRadius(int radius);
	void setSpeed(int speed);
	void setHP(int HP);
	void setDEF(int DEF);
	void setATK(int ATK);
	void setRange(int Range);
	void setisAlive(int isAlive);
};

