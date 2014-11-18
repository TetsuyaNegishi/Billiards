#include"Title.h"
#include<DxLib.h>
#include"OnePlayGame.h"

Scene* Title::Update(){
	DrawFormatString(10, 10, GetColor(255, 255, 255), "title");


	//シーケンス処理
	Scene* next = this;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0){
		next = new OnePlayGame();
	}
	return next;
}