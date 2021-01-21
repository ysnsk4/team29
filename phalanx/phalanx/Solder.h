#pragma once
class Solder
{
protected:
	int posX;
	int posY;
	int radius;
	int speed;
	int HP;
	int DEF;
	int ATK;
	int Range;
public:
	virtual void draw();
};

