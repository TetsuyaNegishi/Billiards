#pragma once

#include<DxLib.h>
#include<vector>
#include"Pocket.h"
#include"Player.h"

class Game{
private:
	Player player;
	std::vector<Pocket*> pockets;
	std::vector<Ball*> balls;
	void boardShow();
	void ballShow();
	void update();
	void clickCheck(bool* ballsMoving);
	bool ballsMovingCheck();
	bool pocketInCheck(Ball* ball);


public:
	//ウィンドウサイズ指定
	static const int WINDOW_WIDTH;	//ウィンドウ幅
	static const int WINDOW_HEIGHT;	//ウィンドウ高さ
	static const int STATUS_HEIGHT;	//ステータス表示幅

	//ボード座標指定
	static const int BOARD_LEFT;
	static const int BOARD_RIGHT;
	static const int BOARD_TOP;
	static const int BOARD_BOTTOM;

	//フィールド座標指定
	static const int FIELD_LEFT;
	static const int FIELD_RIGHT;
	static const int FIELD_TOP;
	static const int FIELD_BOTTOM;

	//クッション座標指定
	static const int CUSHION_LEFT;
	static const int CUSHION_RIGHT;
	static const int CUSHION_TOP;
	static const int CUSHION_BOTTOM;
	static const int CUSHION_POSITION[][8];

	Game();
	void init();
	void main();
	void end();
};