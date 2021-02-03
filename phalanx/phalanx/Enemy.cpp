#include "Enemy.h"
#include"Friend.h"
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
	AttackHaste = 50;
	AttackCooldown = AttackHaste;
	EnemySolder = LoadGraph("resource/enemy4.png");
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
void Enemy::update(Friend* SolderF[9]) {
	death();
	Attack(SolderF);
	collide(SolderF);
	move();
}

void Enemy::draw() {
	if (this->isAlive == 1) {
		/*DrawBox(
		this->posX - this->radius,
		this->posY - this->radius,
		this->posX + this->radius,
		this->posY + this->radius,
		GetColor(200, 0, 5),
		TRUE);*/
		DrawGraph(
			this->posX - 32,
			this->posY - 32,
			EnemySolder,
			true
		);
	}
}

void Enemy::Attack(Friend* SolderF[9]) {
	if (AttackCooldown == 0)
	{
		int isAttack = 0;
		int whoAttack = 999;

		for (int i = 0; i < 9; i++) {
			if (
				isAttack == 0
				&&
				(SolderF[i]->getPosX() - this->posX) * (SolderF[i]->getPosX() - this->posX) +
				(SolderF[i]->getPosY() - this->posY) * (SolderF[i]->getPosY() - this->posY)
				<= (SolderF[i]->getRadius() + this->radius) * (SolderF[i]->getRadius() + this->radius)
				) {
				isAttack = 1;
				whoAttack = i;
			}
		}

		if (isAttack == 1)
		{
			SolderF[whoAttack]->setHP(SolderF[whoAttack]->getHP() - (this->ATK - SolderF[whoAttack]->getDEF()));
			DrawFormatString(SolderF[whoAttack]->getPosX(), SolderF[whoAttack]->getPosY(), GetColor(255, 0, 0), "%d", this->ATK - SolderF[whoAttack]->getDEF());
		}

		AttackCooldown = AttackHaste;
	}
	else
	{
		AttackCooldown--;
	}

}

void Enemy::move() {
	if (this->isAlive == 1) {
		posY += speed;
	}
}


void Enemy::collide(Friend* SolderF[9]) {

	int isCollide = 0;

	for (int i = 0; i < 9; i++) {
		if (
			(SolderF[i]->getPosX() - this->posX) * (SolderF[i]->getPosX() - this->posX) +
			(SolderF[i]->getPosY() - this->posY) * (SolderF[i]->getPosY() - this->posY)
			<= (SolderF[i]->getRadius()+this->radius )*( SolderF[i]->getRadius()+this->radius)
			) {
			isCollide = 1;
		}
	}

	if (isCollide==1)
	{
		this->speed = 0;
	}
	else
	{
		this->speed = 8;
	}
}

void Enemy::death() {
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