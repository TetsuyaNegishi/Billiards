#ifndef BALL_H
#define BALL_H

#include"Vector2d.h"

class Ball{
public:
	Vector2d t; //���W
	Vector2d v; //���x

	Ball();
	Ball(float x, float y);
	
	float getX();
	float getY();
	void move();
};

#endif