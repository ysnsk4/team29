#include<DxLib.h>
#include "Player.h"

// Constructor
Player::Player(int posX, int posY, int radius, int speed, int Range) {
	this->posX = posX;
	this->posY = posY;
	this->radius = radius;
	this->speed = speed;
	this->Range = Range;
	this->isGrab = 0;
	this->HP = 800;
	this->Gold = 0;
	this->playerGraph = LoadGraph("resource/player.png");
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
int Player::getHP() { return HP; }

// Setter
void Player::setPosX(int posX) { this->posX = posX; }
void Player::setPosY(int posY) { this->posY = posY; }
void Player::setRadius(int radius) { this->radius = radius; }
void Player::setSpeed(int speed) { this->speed = speed; }
void Player::setRange(int Range) { this->Range = Range; }
void Player::setHP(int HP) { this->HP=HP; }
// Member Function
void Player::update() {}

void Player::draw() {
	//DrawBox(
	//	posX - radius,
	//	posY - radius,
	//	posX + radius,
	//	posY + radius,
	//	GetColor(200, 200, 255),
	//	TRUE);
	DrawGraph(
		posX - radius,
		posY - radius,
		playerGraph,
		true
	);
}

void Player::move(char keys[255], int WIN_WIDTH, int WIN_HEIGHT) {
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

void Player::grabFriend(Friend* SolderF[64]) {
	int grabFlag = 0;
	oldMousePosX = MousePosX;
	oldMousePosY = MousePosY;
	oldMouseLeft = MouseLeft;
	GetMousePoint(&MousePosX, &MousePosY);
	GetMouseInput();
	MouseLeft = MOUSE_INPUT_LEFT;


	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		for (int i = 0; i < 64; i++) {
			if (
				(SolderF[i]->getPosX() - MousePosX) * (SolderF[i]->getPosX() - MousePosX) +
				(SolderF[i]->getPosY() - MousePosY) * (SolderF[i]->getPosY() - MousePosY)
				<= SolderF[i]->getRadius() * SolderF[i]->getRadius()
				&&
				grabFlag == 0
				) {

				SolderF[i]->setPosX(MousePosX);
				SolderF[i]->setPosY(MousePosY);
				grabFlag = 1;
			}
		}
	} else {
		grabFlag = 0;
	}

}

void Player::Defence(Enemy* enemy[72],int WIN_HEIGHT) {
	for (int i = 0; i < 72; i++) {
		if (
			enemy[i]->getPosY()
			>=WIN_HEIGHT-enemy[i]->getRadius()
			) 
		{
			this->HP--;
		}
	}
}