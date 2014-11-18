#include"Menu.h"
#include<DxLib.h>
#include"Play.h"
#include"Title.h"
#include"MainLoop.h"

Menu::Menu(OnePlayGame* parent){
	mParent = parent;
}

Scene* Menu::Update(){

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(100, 100, 300, 300, GetColor(0, 0, 0), TRUE);
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