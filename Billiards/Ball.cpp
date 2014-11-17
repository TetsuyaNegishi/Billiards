#include"Ball.h"
#include"Game.h"
#include<math.h>
#include<DxLib.h>

const int Ball::SIZE = 15;
const float Ball::FRICTON_FORCE_SIZE = 0.99f;

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

bool wallCollisionCheck(Ball* ball, Vector2d wallPosition1, Vector2d wallPosition2){
	Vector2d wallVector, t, v;
	float crossProduct;
	t = ball->getT();
	v = ball->getV();
	wallVector = (wallPosition1 - wallPosition2).getNormalizeVector();
	crossProduct = Cross(wallVector, t + v - wallPosition1);//t+víçà”
	if (fabs(crossProduct) < ball->getSize()){
		(*ball).setV(v - 2 * (NormalVectorLeft(wallVector)*v) * NormalVectorLeft(wallVector));
		return true;
	}
	return false;
}

void Ball::move(){
	Vector2d check = t + v;
	Vector2d wallPosition[2],wallVector;
	
	//è„ÉNÉbÉVÉáÉìè’ìÀîªíË
	if (Game::CUSHION_TOP > (check.y - SIZE)){
		//ç∂äpîªíË
		if (Game::CUSHION_POSITION[2][1].x > getX()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[2][0], Game::CUSHION_POSITION[2][1]))
				return;
		}
		//íÜâõäpîªíË
		else if (Game::CUSHION_POSITION[2][3].x < t.x && Game::CUSHION_POSITION[3][3].x > t.x){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[2][2], Game::CUSHION_POSITION[2][3]))
				return;
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[3][2], Game::CUSHION_POSITION[3][3]))
				return;			
		}
		//âEäpîªíË
		else if (Game::CUSHION_POSITION[3][1].x < getX()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[3][0], Game::CUSHION_POSITION[3][1]))
				return;
		}
		else{ v.y *= -1; }
	}
	//â∫ÉNÉbÉVÉáÉìîªíË
	else if (Game::CUSHION_BOTTOM < (check.y + SIZE)){
		//ç∂äpîªíË
		if (Game::CUSHION_POSITION[4][1].x > getX()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[4][0], Game::CUSHION_POSITION[4][1]))
				return;
		}
		//íÜâõäpîªíË
		else if (Game::CUSHION_POSITION[4][3].x < t.x && Game::CUSHION_POSITION[5][3].x > t.x){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[4][2], Game::CUSHION_POSITION[4][3]))
				return;
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[5][2], Game::CUSHION_POSITION[5][3]))
				return;
		}
		//âEäpîªíË
		else if (Game::CUSHION_POSITION[5][1].x < getX()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[5][0], Game::CUSHION_POSITION[5][1]))
				return;
		}
		else{ v.y *= -1; }
	}
	else{}

	//ç∂ÉNÉbÉVÉáÉìîªíË
	if (Game::CUSHION_LEFT > (check.x - SIZE)){
		//è„äpîªíË
		if (Game::CUSHION_POSITION[0][1].y > getY()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[0][0], Game::CUSHION_POSITION[0][1]))
				return;
		}
		//â∫äpîªíË
		else if (Game::CUSHION_POSITION[0][3].y < getY()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[0][2], Game::CUSHION_POSITION[0][3]))
				return;
		}
		else{ v.x *= -1; }
	}
	//âEÉNÉbÉVÉáÉìîªíË
	else if (Game::CUSHION_RIGHT < (check.x + SIZE)){
		//è„äpîªíË
		if (Game::CUSHION_POSITION[1][1].y > getY()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[1][0], Game::CUSHION_POSITION[1][1]))
				return;
		}
		//â∫äpîªíË
		else if (Game::CUSHION_POSITION[1][3].y < getY()){
			if (wallCollisionCheck(this, Game::CUSHION_POSITION[1][2], Game::CUSHION_POSITION[1][3]))
				return;
		}
		else{ v.x *= -1; }
	}
	else {}

	t += v;

	if ((FRICTON_FORCE_SIZE*v).norm() < 0.2)
		v = Vector2d(0, 0);
	else
		v = FRICTON_FORCE_SIZE*v;

}

void Ball::display(){
	DrawCircle(this->getXi(), this->getYi(), this->getSize(), this->getColor());
}