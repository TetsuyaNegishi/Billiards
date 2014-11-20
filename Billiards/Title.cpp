#include"Title.h"
#include<DxLib.h>
#include"OnePlayGame.h"
#include"MainLoop.h"

Title::Title(){
	SetFontSize(30);
	ChangeFont("���C���I");
	SetFontThickness(1);
}

Scene* Title::Update(){
	int titleLeft = MainLoop::WINDOW_WIDTH / 2 - GetDrawStringWidth("[SPACE]:START", strlen("[SPACE]:START")) / 2;
	DrawFormatString(titleLeft, MainLoop::WINDOW_HEIGHT / 2 - 50, GetColor(255, 255, 255), "[SPACE]:START");
	DrawFormatString(titleLeft, MainLoop::WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "[P-KEY]:POSE");

	//�V�[�P���X����
	Scene* next = this;
	if (CheckHitKey(KEY_INPUT_SPACE) != 0){
		next = new OnePlayGame();
	}
	return next;
}