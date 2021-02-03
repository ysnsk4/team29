#pragma once
#include "Solder.h"
#include"Enemy.h"

class Friend :public Solder
{
private:
	int FriendSoldier;

	int AttackHaste;
	int AttackCooldown;
	int isAlive;
public:
	Friend(int posX, int posY, int radius, int speed, int HP, int DEF, int ATK, int Range);
	~Friend();

	void update(Enemy* enemys[81]);
	void draw();

	void move();
	void Attack(Enemy* enemys[81]);
	void death();

	int getPosX();
	int getPosY();
	int getRadius();
	int getSpeed();
	int getHP();
	int getDEF();
	int getATK();
	int getRange();

	void setPosX(int posX);
	void setPosY(int posY);
	void setRadius(int radius);
	void setSpeed(int speed);
	void setHP(int HP);
	void setDEF(int DEF);
	void setATK(int ATK);
	void setRange(int Range);
};

