#pragma once

#include"Vector2d.h"
#include<vector>

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
	Vector2d getV();
	void setColor(int color);
	int getColor();
	int getSize();

	bool movingCheck();
	void move();
	void display();

	void collision(std::vector<Ball*>* balls, std::vector<Ball*>* movingBalls);
};