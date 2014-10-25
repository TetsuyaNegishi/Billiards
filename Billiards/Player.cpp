#include"Player.h"
#include"Game.h"

Player::Player() : Ball(){}

Player::Player(float x, float y) : Ball(x, y){}

Player::Player(float x, float y, int color) : Ball(x, y, color){}

void Player::move(){
	Vector2d check = t + v;
	if (Game::CUSHION_LEFT > (check.x - SIZE) || Game::CUSHION_RIGHT < (check.x + SIZE))
		v.x *= -1;
	if (Game::CUSHION_TOP >(check.y - SIZE) || Game::CUSHION_BOTTOM < (check.y + SIZE))
		v.y *= -1;
	t += v;

	v = FRICTON_FORCE_SIZE*v;
}