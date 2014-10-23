#pragma once

#include"Vector2d.h"

class Ball{
private:
	Vector2d t; //ç¿ïW
	Vector2d v; //ë¨ìx
	const int color;
	static const int SIZE = 10;

public:
	Ball();
	Ball(float x, float y);
	Ball(float x, float y, int color);
	
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	int getColor();
	int getSize();

	void move();
};
