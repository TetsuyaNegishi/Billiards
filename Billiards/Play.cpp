#include"Play.h"
#include<DxLib.h>
#include"Menu.h"

Play::Play(OnePlayGame* parent){
	mParent = parent;
	mPrevMouseInput = false;
}

//���{�[�����|�P�b�g�ɗ��������A���{�[�����ēx�u������
void Play::PutPlayer(){
	int x, y;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		if (!(mPrevMouseInput))
			mPrevMouseInput = true;
	}else if (!(GetMouseInput() & MOUSE_INPUT_LEFT)){
		if (mPrevMouseInput){
			mPrevMouseInput = false;
			mParent->PutPlayer();
		}
	}
	GetMousePoint(&x, &y);
	mParent->PlayerSet(x, y);
}

//���{�[����ł��\�b�h
void Play::ShotPlayer(){
	int x, y;
	float speedSize;
	Vector2d direction;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		if (!(mPrevMouseInput)){
			mPrevMouseInput = true;
		}
	}else if (!(GetMouseInput() & MOUSE_INPUT_LEFT)){
		if (mPrevMouseInput){
			mPrevMouseInput = false;
			GetMousePoint(&x, &y);
			direction = Vector2d((float)x, (float)y) - mParent->GetPlayer()->getT();
			speedSize = direction.norm() / 5;
			if (speedSize >= 20)
				speedSize = 20;
			direction.normalize();
			mParent->GetPlayer()->setV(speedSize * direction);
			mParent->NumShotPlaPla();
		}
	}
}

Scene* Play::Update(){
	if (mParent->BallsMovingCheck()){
		mParent->BallsMove();
	}
	else{
		if (!mParent->GetPlayerExist())
			PutPlayer(); //���{�[�����|�P�b�g�ɓ�������
		else
			ShotPlayer();
	}

	//�V�[�P���X����
	Scene* next = this;
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Play");
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0){
		next = new Menu(mParent);
	}
	return next;
}