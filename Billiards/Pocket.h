#pragma once

#include"Vector2d.h"

class Pocket{
private:
	Vector2d t;

public:
	static const int SIZE;

	Pocket();
	Pocket(int x, int y);
	int getSize();
	float getX();
	float getY();
	Vector2d getT();
};