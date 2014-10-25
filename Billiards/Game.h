#pragma once

#include<DxLib.h>
#include<vector>
#include"Pocket.h"
#include"Player.h"

class Game{
private:
	Player player;
	std::vector<Pocket> pockets;
	std::vector<Ball> balls;
	std::vector<Ball*> moveBalls;
	void boardShow();
	void ballShow();
	void update();
	void clickCheck();

public:
	static const int WINDOW_WIDTH = 800;	//ウィンドウ幅
	static const int WINDOW_HEIGHT = 450;	//ウィンドウ高さ
	static const int STATUS_HEIGHT = 50;	//ステータス表示幅
	//ボード座標指定
	static const int a = 15;
	static const int BOARD_LEFT = a;
	static const int BOARD_RIGHT = WINDOW_WIDTH - a;
	static const int BOARD_TOP = a;
	static const int BOARD_BOTTOM = WINDOW_HEIGHT - STATUS_HEIGHT - a;
	//フィールド座標指定
	static const int b = 30;
	static const int FIELD_LEFT = BOARD_LEFT + b;
	static const int FIELD_RIGHT = BOARD_RIGHT - b;
	static const int FIELD_TOP = BOARD_TOP + b;
	static const int FIELD_BOTTOM = BOARD_BOTTOM - b;
	//クッション座標指定
	static const int c = 15;
	static const int CUSHION_LEFT = FIELD_LEFT + c;
	static const int CUSHION_RIGHT = FIELD_RIGHT - c;
	static const int CUSHION_TOP = FIELD_TOP + c;
	static const int CUSHION_BOTTOM = FIELD_BOTTOM - c;

	Game();
	void init();
	void main();
	void end();
};