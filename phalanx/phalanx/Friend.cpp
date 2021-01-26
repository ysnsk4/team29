#include "Friend.h"
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
void Friend::update() {}

void Friend::draw() {
	if (1) {
		/*DrawBox(
			this->posX - this->radius,
			this->posY - this->radius,
			this->posX + this->radius,
			this->posY + this->radius,
			GetColor(5, 200, 5),
			TRUE);*/
		DrawGraph(
			this->posX - 32,
			this->posY - 32,
			FriendSoldier,
			true
		);
	}
}

void Friend::Attack() {

}

void Friend::move() {
	if (1) {
		posY += speed;
	}
}