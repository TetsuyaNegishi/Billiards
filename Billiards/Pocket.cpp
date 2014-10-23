#include"Pocket.h"

Pocket::Pocket(){
	t = Vector2d(0, 0);
}

Pocket::Pocket(int x, int y){
	t = Vector2d(x,y);
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