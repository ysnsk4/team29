#include "Friend.h"
#include"Enemy.h"
#include<DxLib.h>

// Constructor
Friend::Friend(int posX, int posY, int radius, int speed, int HP, int DEF, int ATK, int Range) {
	this->posX = posX;
	this->posY = posY;
	this->radius = radius;
	this->speed = speed;
	this->HP = HP;
	this->DEF = DEF;
	this->ATK = ATK;
	this->Range = Range;
	this->FriendSoldier = LoadGraph("resource/inf.png");

	AttackHaste = 50;
	AttackCooldown = AttackHaste;
	isAlive = 1;
}

// Destructor
Friend::~Friend() {
}

// Getter
int Friend::getPosX() { return posX; }
int Friend::getPosY() { return posY; }
int Friend::getRadius() { return radius; }
int Friend::getSpeed() { return speed; }
int Friend::getHP() { return HP; }
int Friend::getDEF() { return DEF; }
int Friend::getATK() { return ATK; }
int Friend::getRange() { return Range; }

// Setter
void Friend::setPosX(int posX) { this->posX = posX; }
void Friend::setPosY(int posY) { this->posY = posY; }
void Friend::setRadius(int radius) { this->radius = radius; }
void Friend::setSpeed(int speed) { this->speed = speed; }
void Friend::setHP(int HP) { this->HP = HP; }
void Friend::setDEF(int DEF) { this->DEF = DEF; }
void Friend::setATK(int ATK) { this->ATK = ATK; }
void Friend::setRange(int Range) { this->Range = Range; }
// Member Function
void Friend::update(Enemy*enemys[81]) {
	death();
	move();
	Attack(enemys);
}

void Friend::draw() {
	if (1) {
		/*DrawBox(
			this->posX - this->radius,
			this->posY - this->radius,
			this->posX + this->radius,
			this->posY + this->radius,
			GetColor(5, 200, 5),
			TRUE);*/
		if (isAlive == 1)
		{
			DrawGraph(
				this->posX - 32,
				this->posY - 32,
				FriendSoldier,
				true
			);
		}
	}
}

void Friend::Attack(Enemy*enemys[81]){
	if (AttackCooldown == 0)
	{
		int isAttack = 0;
		int whoAttack = 999;

		for (int i = 0; i < 81; i++) {
			if (
				isAttack == 0
				&&
				(enemys[i]->getPosX() - this->posX) * (enemys[i]->getPosX() - this->posX) +
				(enemys[i]->getPosY() - this->posY) * (enemys[i]->getPosY() - this->posY)
				<= (enemys[i]->getRadius() + this->radius) * (enemys[i]->getRadius() + this->radius)
				) {
				isAttack = 1;
				whoAttack = i;
			}
		}

		if (isAttack == 1)
		{
			enemys[whoAttack]->setHP(enemys[whoAttack]->getHP() - (this->ATK - enemys[whoAttack]->getDEF()));
			DrawFormatString(enemys[whoAttack]->getPosX(), enemys[whoAttack]->getPosY(), GetColor(255, 0, 0), "%d", this->ATK - enemys[whoAttack]->getDEF());
		}

		AttackCooldown = AttackHaste;
	}
	else
	{
		AttackCooldown--;
	}
}

void Friend::move() {
}


void Friend::death() {
	if (HP <= 0)
	{
		isAlive = 0;
		posX = 1000;
	}
	else
	{
		isAlive = 1;
	}
}