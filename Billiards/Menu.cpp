#include"Menu.h"
#include<DxLib.h>
#include"Play.h"
#include"Title.h"
#include"MainLoop.h"

Menu::Menu(OnePlayGame* parent){
	mParent = parent;
}

Scene* Menu::Update(){
	const int WIDTH = 100;
	const int HEIGHT = 100;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(MainLoop::WINDOW_WIDTH / 2 - WIDTH, MainLoop::WINDOW_HEIGHT / 2 - HEIGHT, 
		MainLoop::WINDOW_WIDTH / 2 + WIDTH, MainLoop::WINDOW_HEIGHT / 2 + HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(10, 10, GetColor(255, 255, 255), "Menu");


	//シーケンス処理
	Scene* next = this;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0){
		next = new Play(mParent);
	}
	if (CheckHitKey(KEY_INPUT_SPACE) != 0){
		next = new Title();
	}
	return next;
}