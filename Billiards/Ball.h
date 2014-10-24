#pragma once

#include"Vector2d.h"

class Ball{
protected:
	Vector2d t; //座標
	Vector2d v; //速度
	int color;
	static const int SIZE;
	static const float FRICTON_FORCE_SIZE;

public:
	Ball();
	Ball(float x, float y);
	Ball(float x, float y, int color);

	void setX(float x);
	float getX();
	int getXi();
	void setY(float y);
	float getY();
	int getYi();
	void setT(Vector2d);
	Vector2d getT();
	void setV(Vector2d vi);
	int getColor();
	int getSize();

	void move();
};