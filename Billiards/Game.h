#pragma once

#include<DxLib.h>
#include<vector>
#include"Pocket.h"
#include"Player.h"

class Game{
private:
	Player player;
	bool playerExist;
	std::vector<Pocket*> pockets;
	std::vector<Ball*> balls;
	void boardShow();
	void ballShow();
	void update();
	void clickCheck(bool* ballsMoving);
	bool ballsMovingCheck();
	bool pocketInCheck(Ball* ball);
	void playerSet(bool* prevMouseInput);



public:
	//�E�B���h�E�T�C�Y�w��
	static const int WINDOW_WIDTH;	//�E�B���h�E��
	static const int WINDOW_HEIGHT;	//�E�B���h�E����
	static const int STATUS_HEIGHT;	//�X�e�[�^�X�\����

	//�{�[�h���W�w��
	static const int BOARD_LEFT;
	static const int BOARD_RIGHT;
	static const int BOARD_TOP;
	static const int BOARD_BOTTOM;

	//�t�B�[���h���W�w��
	static const int FIELD_LEFT;
	static const int FIELD_RIGHT;
	static const int FIELD_TOP;
	static const int FIELD_BOTTOM;

	//�N�b�V�������W�w��
	static const int CUSHION_LEFT;
	static const int CUSHION_RIGHT;
	static const int CUSHION_TOP;
	static const int CUSHION_BOTTOM;
	static const Vector2d CUSHION_POSITION[][4];

	Game();
	void init();
	void main();
	void end();
};