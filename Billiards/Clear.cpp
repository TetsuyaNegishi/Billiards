#include"Clear.h"
#include"OnePlayGame.h"
#include"MainLoop.h"

Clear::Clear(OnePlayGame* parent){
	mParent = parent;
}

Scene* Clear::Update(){
	const int WIDTH = 100;
	const int HEIGHT = 100;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(MainLoop::WINDOW_WIDTH / 2 - WIDTH, MainLoop::WINDOW_HEIGHT / 2 - HEIGHT,
		MainLoop::WINDOW_WIDTH / 2 + WIDTH, MainLoop::WINDOW_HEIGHT / 2 + HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//シーケンス処理
	Scene* next = this;
	if (CheckHitKey(KEY_INPUT_SPACE) != 0){
		next = new OnePlayGame();
	}
	return next;
}