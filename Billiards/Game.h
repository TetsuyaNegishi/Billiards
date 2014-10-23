#ifndef GAME_H
#define GAME_H

#include<DxLib.h>

class Game{
private:
	void boardShow();

public:
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 450;
	static const int STATUS_HEIGHT = 50;
	static const int a = 15;
	static const int BOARD_LEFT = a;
	static const int BOARD_RIGHT = WINDOW_WIDTH - a;
	static const int BOARD_TOP = a;
	static const int BOARD_BOTTOM = WINDOW_HEIGHT - STATUS_HEIGHT - a;
	static const int b = 30;
	static const int FIELD_LEFT = BOARD_LEFT + b;
	static const int FIELD_RIGHT = BOARD_RIGHT - b;
	static const int FIELD_TOP = BOARD_TOP + b;
	static const int FIELD_BOTTOM = BOARD_BOTTOM - b;
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

#endif