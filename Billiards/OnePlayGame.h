#pragma once

#include<DxLib.h>
#include<vector>
#include"Pocket.h"
#include"Player.h"
#include"SceneMainLoopChild.h"

class OnePlayGame : public SceneMainLoopChild{
private:
	Player* mPlayer;
	bool mPlayerExist;

	int mNumShot;
	int mNumColorBall;

	std::vector<Pocket*> mPockets;
	std::vector<Ball*> mBalls;
	void BoardShow();
	void BallShow();
	void NumShotShow();
	void DrawSquare(const Vector2d position[4], int color);
	bool PocketInCheck(Ball* ball);
	bool wallCollisionCheck(Ball* ball, Vector2d wallPosition1, Vector2d wallPosition2);
	void CushionCollision(Ball* ball);


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

	void Display();
	
	bool BallsMovingCheck();
	void BallsMove();
	void PlayerSet(int x, int y);
	bool GetPlayerExist();
	void PutPlayer();
	void NumShotPlaPla();
	Player* GetPlayer();

	//�V�[�P���X�����p
private:
	Scene* mChild;
public:
	OnePlayGame();
	virtual Scene* Update() override;
};