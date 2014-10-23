#include"Ball.h"

Ball::Ball(){
	v = Vector2d(0, 0);
}

Ball::Ball(float x, float y){
	Ball();
	t = Vector2d(x, y);
}

Ball::Ball(float x, float y, int color) : color(color){
	Ball(x, y);
}


void Ball::setX(float x){
	v.x = x;
}

float Ball::getX(){
	return t.x;
}

void Ball::setY(float y){
	v.y = y;
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
