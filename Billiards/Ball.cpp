#include"Ball.h"
#include"Game.h"
#include<math.h>

const int Ball::SIZE = 10;
const float Ball::FRICTON_FORCE_SIZE = 0.99;

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

int Ball::getXi(){
	return (int)round(t.x);
}

void Ball::setY(float y){
	t.y = y;
}

float Ball::getY(){
	return t.y;
}

int Ball::getYi(){
	return (int)round(t.y);
}

void Ball::setT(Vector2d t){
	this->t = t;
}

Vector2d Ball::getT(){
	return t;
}

void Ball::setV(Vector2d vi){
	v = vi;
}

Vector2d Ball::getV(){
	return v;
}

void Ball::setColor(int color){
	this->color = color;
}

int Ball::getColor(){
	return color;
}

int Ball::getSize(){
	return SIZE;
}

bool Ball::movingCheck(){
	if (v.norm() == 0.0)
		return false;
	else
		return true;
}

void Ball::move(){
	Vector2d check = t + v;
	if (Game::CUSHION_LEFT > (check.x - SIZE) || Game::CUSHION_RIGHT < (check.x + SIZE))
		v.x *= -1;
	if (Game::CUSHION_TOP >(check.y - SIZE) || Game::CUSHION_BOTTOM < (check.y + SIZE))
		v.y *= -1;
	t += v;

	if ((FRICTON_FORCE_SIZE*v).norm() < pow(10, -2))
		v = Vector2d(0, 0);
	else
		v = FRICTON_FORCE_SIZE*v;
}

void Ball::collision(std::vector<Ball*>* balls, std::vector<Ball*>* movingBalls){
	//std::vector<Ball*> collisionBall;
	Vector2d sigmentBallThis, thisV, ballV;
	float dotThis, dotBall;
	for (std::vector<Ball*>::iterator ball = (*balls).begin(); ball != (*balls).end(); ball++){
		if (this == (*ball))
			continue;
		if ((this->getT() - (*ball)->getT()).norm2() < pow(this->getSize()+(*ball)->getSize(), 2)){
			sigmentBallThis = (this->getT() - (*ball)->getT()).getNormalizeVector();
			dotThis = this->getV() * sigmentBallThis;
			dotBall = (*ball)->getV() * sigmentBallThis;
			thisV = this->getV() + (dotBall - dotThis) * sigmentBallThis;
			ballV = (*ball)->getV() + (dotThis - dotBall) * sigmentBallThis;
			this->setV(thisV);
			(*ball)->setV(ballV);
			movingBalls->push_back(*ball);
			break;
			//	collisionBall.push_back(*ball);
		}
	}

}
