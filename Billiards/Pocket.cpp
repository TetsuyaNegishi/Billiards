#include"Pocket.h"

const int Pocket::SIZE = 25;

Pocket::Pocket(){
	t = Vector2d(0, 0);
}

Pocket::Pocket(int x, int y){
	t = Vector2d((float)x, (float)y);
}

int Pocket::getSize(){
	return SIZE;
}

float Pocket::getX(){
	return t.x;
}

float Pocket::getY(){
	return t.y;
}

Vector2d Pocket::getT(){
	return t;
}