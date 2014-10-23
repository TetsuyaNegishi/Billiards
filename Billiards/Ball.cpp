#include"Ball.h"
#include"Game.h"

Ball::Ball(){
	v = Vector2d(0, 0);
}

Ball::Ball(float x, float y){
	v = Vector2d(0, 0);
	t = Vector2d(x, y);
}

Ball::Ball(float x, float y, int color){
	v = Vector2d(0, 0);
	t = Vector2d(x, y);
	this->color = color;
}


void Ball::setX(float x){
	t.x = x;
}

float Ball::getX(){
	return t.x;
}

void Ball::setY(float y){
	t.y = y;
}

float Ball::getY(){
	return t.y;
}

void Ball::setV(Vector2d vi){
	v = vi;
}

int Ball::getColor(){
	return color;
}

int Ball::getSize(){
	return SIZE;
}

void Ball::move(){
	Vector2d check = t + v;
	if (Game::CUSHION_LEFT > (check.x - SIZE) || Game::CUSHION_RIGHT < (check.x + SIZE))
		v.x *= -1;
	if (Game::CUSHION_TOP > (check.y - SIZE) || Game::CUSHION_BOTTOM < (check.y + SIZE))
		v.y *= -1;
	t += v;
}
