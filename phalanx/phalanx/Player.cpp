#include<DxLib.h>
#include "Player.h"


// Constructor
Player::Player(int posX, int posY, int radius, int speed,int Range) {
	this->posX = posX;
	this->posY = posY;
	this->radius = radius;
	this->speed = speed;
	this->Range = Range;
	this->isGrab = 0;
}

// Destructor
Player::~Player() {
}

// Getter
int Player::getPosX() { return posX; }
int Player::getPosY() { return posY; }
int Player::getRadius() { return radius; }
int Player::getSpeed() { return speed; }
int Player::getRange() { return Range; }

// Setter
void Player::setPosX(int posX) { this->posX = posX; }
void Player::setPosY(int posY) { this->posY = posY; }
void Player::setRadius(int radius) { this->radius = radius; }
void Player::setSpeed(int speed) { this->speed = speed; }
void Player::setRange(int Range) { this->Range = Range; }
// Member Function
void Player::update() {}

void Player::draw() {
	DrawBox(
		posX - radius,
		posY - radius,
		posX + radius,
		posY + radius,
		GetColor(200, 200, 255),
		TRUE);
}

void Player::move(char keys[255], int WIN_WIDTH,int WIN_HEIGHT) {
	if (CheckHitKey(KEY_INPUT_W) == 1 && posY > 0 + radius)
	{
		posY -= speed;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1 && posY < WIN_HEIGHT - radius)
	{
		posY += speed;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1 && posX > 0 + radius)
	{
		posX -= speed;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1 && posX < WIN_WIDTH - radius)
	{
		posX += speed;
	}
}