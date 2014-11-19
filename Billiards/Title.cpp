#include"Title.h"
#include<DxLib.h>
#include"OnePlayGame.h"

Title::Title() : handle(CreateFontToHandle("���C���I", 40, 3, DX_FONTTYPE_NORMAL)){
}

Scene* Title::Update(){
	//int handle = CreateFontToHandle("���C���I", 40, 3, DX_FONTTYPE_NORMAL);

	DrawFormatStringToHandle(10, 10, GetColor(255, 255, 255), handle, "title");

	
	//�V�[�P���X����
	Scene* next = this;
	if (CheckHitKey(KEY_INPUT_LEFT) != 0){
		next = new OnePlayGame();
	}
	return next;
}