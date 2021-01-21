#include "Enemy.h"
#include<DxLib.h>

// Constructor
Enemy::Enemy(int posX, int posY, int radius, int speed, int HP, int DEF, int ATK, int Range,int isAlive) {
	this->posX = posX;
	this->posY = posY;
	this->radius = radius;
	this->speed = speed;
	this->HP = HP;
	this->DEF = DEF;
	this->ATK = ATK;
	this->Range = Range;
	this->isAlive;
	EnemyCount++;
}

// Destructor
Enemy::~Enemy() {
	EnemyCount--;
}

// Getter
int Enemy::getPosX() { return posX; }
int Enemy::getPosY() { return posY; }
int Enemy::getRadius() { return radius; }
int Enemy::getSpeed() { return speed; }
int Enemy::getHP() { return HP; }
int Enemy::getDEF() { return DEF; }
int Enemy::getATK() { return ATK; }
int Enemy::getRange() { return Range; }
int Enemy::getisAlive() { return isAlive; }


// Setter
void Enemy::setPosX(int posX) { this->posX = posX; }
void Enemy::setPosY(int posY) { this->posY = posY; }
void Enemy::setRadius(int radius) { this->radius = radius; }
void Enemy::setSpeed(int speed) { this->speed = speed; }
void Enemy::setHP(int HP) { this->HP = HP; }
void Enemy::setDEF(int DEF) { this->DEF = DEF; }
void Enemy::setATK(int ATK) { this->ATK = ATK; }
void Enemy::setRange(int Range) { this->Range = Range; }
void Enemy::setisAlive(int isAlive) { this->isAlive=isAlive; }
// Member Function
void Enemy::update() {}

void Enemy::draw() {
	if (this->isAlive == 1) {
		DrawBox(
		this->posX - this->radius,
		this->posY - this->radius,
		this->posX + this->radius,
		this->posY + this->radius,
		GetColor(200, 0, 5),
		TRUE);
	}
}

void Enemy::Attack() {
}

void Enemy::move() {
	if (this->isAlive == 1) {
		posY += speed;
	}
}