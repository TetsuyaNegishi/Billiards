#pragma once

#include"Vector2d.h"

class Pocket{
private:
	Vector2d t;
	static const int SIZE;
public:
	Pocket();
	Pocket(int x, int y);
	int getSize();
	float getX();
	float getY();
};