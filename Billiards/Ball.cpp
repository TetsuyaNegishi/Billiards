#include"Ball.h"

Ball::Ball(){
	t = Vector2d(0, 0);
}

Ball::Ball(float x, float y){
	t = Vector2d(x, y);
}

float Ball::getX(){
	return t.x;
}

float Ball::getY(){
	return t.y;
}

void Ball::move(){
	t += v;
}
