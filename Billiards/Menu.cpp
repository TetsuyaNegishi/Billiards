#include"Menu.h"
#include<DxLib.h>
#include"Play.h"
#include"Title.h"

Menu::Menu(OnePlayGame* parent){
	mParent = parent;
}

Scene* Menu::Update(){
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