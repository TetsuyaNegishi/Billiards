#include"Clear.h"
#include"OnePlayGame.h"
#include"MainLoop.h"
#include"Title.h"

Clear::Clear(OnePlayGame* parent) : mFontHandle(CreateFontToHandle("メイリオ", 30, 1)){
	mParent = parent;
}

Scene* Clear::Update(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, MainLoop::WINDOW_WIDTH, MainLoop::WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int gameClearLeft = MainLoop::WINDOW_WIDTH / 2 - GetDrawStringWidthToHandle("GAME CLEAR", strlen("GAME CLEAR"), mFontHandle) / 2;
	int numShotLeft = MainLoop::WINDOW_WIDTH / 2 - GetDrawStringWidthToHandle("打数：00", strlen("打数：00"), mFontHandle) / 2;
	int menuLeft = MainLoop::WINDOW_WIDTH / 2 - GetDrawStringWidthToHandle("[X-KEY]:RESTART", strlen("[X-KEY]:RESTART"), mFontHandle) / 2;

	DrawFormatStringToHandle(gameClearLeft, MainLoop::WINDOW_HEIGHT / 2 - 50, GetColor(255, 255, 255), mFontHandle, "GAME CLEAR");
	DrawFormatStringToHandle(numShotLeft, MainLoop::WINDOW_HEIGHT / 2, GetColor(255, 255, 255), mFontHandle, "打数：%d", mParent->GetNumShot());
	DrawFormatStringToHandle(menuLeft, MainLoop::WINDOW_HEIGHT / 2 + 50, GetColor(255, 255, 255), mFontHandle, "[X-KEY]:RESTART");
	DrawFormatStringToHandle(menuLeft, MainLoop::WINDOW_HEIGHT / 2 + 100, GetColor(255, 255, 255), mFontHandle, "[C-KEY]:TITLE");

	//シーケンス処理
	Scene* next = this;
	if (CheckHitKey(KEY_INPUT_X) != 0){
		next = new OnePlayGame();
	}
	else if (CheckHitKey(KEY_INPUT_C) != 0){
		next = new Title();
	}
	return next;
}