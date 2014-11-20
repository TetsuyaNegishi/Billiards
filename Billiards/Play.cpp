#include"Play.h"
#include<DxLib.h>
#include"Menu.h"
#include"Clear.h"

Play::Play(OnePlayGame* parent) : mCueSE(LoadSoundMem("SE/cue.mp3")){
	mParent = parent;
	mPrevMouseInput = false;
	mPowerUp = 0.2f;
}


//白ボールがポケットに落ちた時、白ボールを再度置き直す
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

//棒の描画
void Play::CueShow(Vector2d playerT, Vector2d direction){
	Vector2d tip;
	float cueWidth = 5;
	float cueHeight = 300;
	tip = playerT - (mParent->GetShotPower()*3+30)*direction;
	Vector2d positionA[2] = { tip + cueWidth*NormalVectorLeft(direction), tip - cueWidth*NormalVectorLeft(direction) };
	Vector2d positionB[2] = { positionA[0] - cueHeight*direction, positionA[1] - cueHeight*direction };
	DrawQuadrangle(positionA[0].x, positionA[0].y, positionA[1].x, positionA[1].y, positionB[1].x, positionB[1].y,
		positionB[0].x, positionB[0].y, GetColor(85, 107, 47), TRUE);
	DrawQuadrangle(positionA[0].x, positionA[0].y, positionA[1].x, positionA[1].y, positionB[1].x, positionB[1].y,
		positionB[0].x, positionB[0].y, GetColor(40, 50, 20), FALSE);
}

//白ボールを打つメソッド
void Play::ShotPlayer(){
	int x, y;
	float shotPower = mParent->GetShotPower();

	GetMousePoint(&x, &y);
	Vector2d direction = (Vector2d((float)x, (float)y) - mParent->GetPlayer()->getT()).getNormalizeVector();

	DrawLine(mParent->GetPlayer()->getX(), mParent->GetPlayer()->getY(), x, y, GetColor(255, 255, 255));
	CueShow(mParent->GetPlayer()->getT(), direction);

	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		if (!(mPrevMouseInput)){
			mPrevMouseInput = true;
			mParent->SetShotPower(0);
		}
		else{
			if (shotPower > OnePlayGame::MAX_POWER || shotPower < 0)
				mPowerUp *= -1;
			mParent->SetShotPower(shotPower + mPowerUp);
		}
	}
	else if (!(GetMouseInput() & MOUSE_INPUT_LEFT)){
		if (mPrevMouseInput){
			mPrevMouseInput = false;
			mParent->GetPlayer()->setV(shotPower * direction);
			mParent->NumShotPlaPla();
			PlaySoundMem(mCueSE, DX_PLAYTYPE_BACK);
		}
		else
			mParent->SetShotPower(0);
	}
}

Scene* Play::Update(){
	if (mParent->BallsMovingCheck()){
		mParent->BallsMove();
	}
	else{
		if (!mParent->GetPlayerExist())
			PutPlayer(); //白ボールがポケットに入った時
		else
			ShotPlayer();
	}

	//シーケンス処理
	Scene* next = this;
	if (mParent->GetNumColorBall() == 0){
		next = new Clear(mParent);
	}
	else if (CheckHitKey(KEY_INPUT_P) != 0){
		next = new Menu(mParent);
	}
	return next;
}