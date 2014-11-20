#include"Menu.h"
#include<DxLib.h>
#include"Play.h"
#include"Title.h"
#include"OnePlayGame.h"
#include"MainLoop.h"

Menu::Menu(OnePlayGame* parent) : mFontHandle(CreateFontToHandle("メイリオ", 30, 1)){
	mParent = parent;
}

Scene* Menu::Update(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, MainLoop::WINDOW_WIDTH, MainLoop::WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	int menuLeft = MainLoop::WINDOW_WIDTH / 2 - GetDrawStringWidth("[X-KEY]:START", strlen("[X-KEY]:START")) / 2;

	DrawFormatStringToHandle(menuLeft, MainLoop::WINDOW_HEIGHT / 2 - 50, GetColor(255, 255, 255), mFontHandle, "[Z-KEY]:RESUME");
	DrawFormatStringToHandle(menuLeft, MainLoop::WINDOW_HEIGHT / 2, GetColor(255, 255, 255), mFontHandle, "[X-KEY]:RESTART");
	DrawFormatStringToHandle(menuLeft, MainLoop::WINDOW_HEIGHT / 2 + 50, GetColor(255, 255, 255), mFontHandle, "[C-KEY]:TITLE");

	//シーケンス処理
	Scene* next = this;
	if (CheckHitKey(KEY_INPUT_Z) != 0){
		next = new Play(mParent);
	}
	else if (CheckHitKey(KEY_INPUT_X) != 0){
		next = new OnePlayGame();
	}
	else if (CheckHitKey(KEY_INPUT_C) != 0){
		next = new Title();
	}
	return next;
}