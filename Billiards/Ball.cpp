#include"Ball.h"

Ball::Ball(){
	v = Vector2d(0, 0);
}

Ball::Ball(float x, float y){
	Ball();
	t = Vector2d(x, y);
}

Ball::Ball(float x, float y, int color){
	Ball(x, y);
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

int Ball::getColor(){
	return color;
}

int Ball::getSize(){
	return SIZE;
}

void Ball::move(){
	t += v;
}
