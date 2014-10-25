#include"Player.h"
#include"Game.h"

Player::Player() : Ball(){}

Player::Player(float x, float y) : Ball(x, y){}

Player::Player(float x, float y, int color) : Ball(x, y, color){}