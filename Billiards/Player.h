#pragma once

#include"Ball.h"

class Player : public Ball{
public:
	Player();
	Player(float x, float y);
	Player(float x, float y, int color);
};