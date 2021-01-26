#pragma once
class Player
{
private:
	int posX;
	int posY;
	int radius;
	int speed;
	int Range;
	int isGrab;
public:
	Player(int posX, int posY, int radius, int speed,int Range);
	~Player();

	void update();
	void draw();

	void move(char keys[255], int WIN_WIDTH, int WIN_HEIGHT);

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

