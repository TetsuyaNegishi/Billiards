#pragma once

#include"Vector2d.h"

class Ball{
public:
	Vector2d t; //ç¿ïW
	Vector2d v; //ë¨ìx

	Ball();
	Ball(float x, float y);
	
	float getX();
	float getY();
	void move();
};
