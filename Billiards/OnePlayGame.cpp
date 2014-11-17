#include"OnePlayGame.h"
#include<DxLib.h>
#include"Play.h"
#include"MainLoop.h"

//ウィンドウサイズ指定
const int OnePlayGame::WINDOW_WIDTH = MainLoop::WINDOW_WIDTH;	//ウィンドウ幅
const int OnePlayGame::WINDOW_HEIGHT = MainLoop::WINDOW_HEIGHT;	//ウィンドウ高さ
const int OnePlayGame::STATUS_HEIGHT = 50;	//ステータス表示幅

//ボード座標指定
static const int BOARD_VALUE = 15;
const int OnePlayGame::BOARD_LEFT = BOARD_VALUE;
const int OnePlayGame::BOARD_RIGHT = WINDOW_WIDTH - BOARD_VALUE;
const int OnePlayGame::BOARD_TOP = BOARD_VALUE;
const int OnePlayGame::BOARD_BOTTOM = WINDOW_HEIGHT - STATUS_HEIGHT - BOARD_VALUE;

//フィールド座標指定
static const int FIELD_VALUE = 20;
const int OnePlayGame::FIELD_LEFT = BOARD_LEFT + FIELD_VALUE;
const int OnePlayGame::FIELD_RIGHT = BOARD_RIGHT - FIELD_VALUE;
const int OnePlayGame::FIELD_TOP = BOARD_TOP + FIELD_VALUE;
const int OnePlayGame::FIELD_BOTTOM = BOARD_BOTTOM - FIELD_VALUE;

//クッション座標指定
static const int CUSHION_VALUE = 20;
const int OnePlayGame::CUSHION_LEFT = FIELD_LEFT + CUSHION_VALUE;
const int OnePlayGame::CUSHION_RIGHT = FIELD_RIGHT - CUSHION_VALUE;
const int OnePlayGame::CUSHION_TOP = FIELD_TOP + CUSHION_VALUE;
const int OnePlayGame::CUSHION_BOTTOM = FIELD_BOTTOM - CUSHION_VALUE;
static const float CUSHION_SIZE = Pocket::SIZE + 8.0f;
static const float CUSHION_EDGE = 17.0f;
const Vector2d OnePlayGame::CUSHION_POSITION[][4] = {
	//左クッション
		{ Vector2d((float)FIELD_LEFT, FIELD_TOP + CUSHION_SIZE), Vector2d((float)CUSHION_LEFT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE),
		Vector2d((float)FIELD_LEFT, FIELD_BOTTOM - CUSHION_SIZE), Vector2d((float)CUSHION_LEFT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE) },
		//右クッション
		{ Vector2d((float)FIELD_RIGHT, FIELD_TOP + CUSHION_SIZE), Vector2d((float)CUSHION_RIGHT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE),
		Vector2d((float)FIELD_RIGHT, FIELD_BOTTOM - CUSHION_SIZE), Vector2d((float)CUSHION_RIGHT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE) },
		//左上クッション
		{ Vector2d(FIELD_LEFT + CUSHION_SIZE, (float)FIELD_TOP), Vector2d(FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, (float)CUSHION_TOP),
		Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, (float)FIELD_TOP), Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, (float)CUSHION_TOP) },
		//右上クッション
		{ Vector2d(FIELD_RIGHT - CUSHION_SIZE, (float)FIELD_TOP), Vector2d(FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, (float)CUSHION_TOP),
		Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, (float)FIELD_TOP), Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, (float)CUSHION_TOP) },
		//左下クッション
		{ Vector2d(FIELD_LEFT + CUSHION_SIZE, (float)FIELD_BOTTOM), Vector2d(FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, (float)CUSHION_BOTTOM),
		Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, (float)FIELD_BOTTOM), Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, (float)CUSHION_BOTTOM) },
		//右下クッション
		{ Vector2d(FIELD_RIGHT - CUSHION_SIZE, (float)FIELD_BOTTOM), Vector2d(FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, (float)CUSHION_BOTTOM),
		Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, (float)FIELD_BOTTOM), Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, (float)CUSHION_BOTTOM) }
};

OnePlayGame::OnePlayGame(){
	//シーケンス処理
	mChild = new Play(this);

	//ポケット初期設定
	const int a = 10;
	mPockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_TOP + a));
	mPockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_TOP + a));
	mPockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_BOTTOM - a));
	mPockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_BOTTOM - a));
	mPockets.push_back(new Pocket(WINDOW_WIDTH / 2, FIELD_TOP + a));
	mPockets.push_back(new Pocket(WINDOW_WIDTH / 2, FIELD_BOTTOM - a));

	//startTime設定
	mStartTime = GetNowCount();

	//numShot設定
	mNumShot = 0;

	//白ボール（プレイヤー）初期設定
	mPlayer = new Player(100, (BOARD_BOTTOM - BOARD_TOP) / 2 + BOARD_TOP, GetColor(255, 255, 255));
	mBalls.push_back(mPlayer);
	mPlayerExist = true;

	//ボール初期設定
	mNumColorBall = 1;
	for (int i = 1; i <= mNumColorBall; i++)
		mBalls.push_back(new Ball(50 * i + 50.0f, 100.0f, GetColor(255, 0, 0)));

	//フォント設定
	SetFontSize(40);
}

//任意の四角形を描画
void OnePlayGame::DrawSquare(const Vector2d position[4], int color){
	DrawTriangle(position[0].x, position[0].y, position[1].x, position[1].y, position[2].x, position[2].y, color, TRUE);
	DrawTriangle(position[1].x, position[1].y, position[2].x, position[2].y, position[3].x, position[3].y, color, TRUE);
}

//ビリヤード盤の描画
void OnePlayGame::BoardShow(){
	const int BROWN = GetColor(153, 76, 0);
	const int DARK_GREEN = GetColor(0, 100, 0);
	const int GREEN = GetColor(0, 200, 0);
	const int BLACK = GetColor(0, 0, 0);

	//ビリヤード盤描画
	DrawBox(BOARD_LEFT, BOARD_TOP, BOARD_RIGHT, BOARD_BOTTOM, BROWN, TRUE);
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, FIELD_BOTTOM, DARK_GREEN, TRUE);

	//クッション描画
	DrawSquare(CUSHION_POSITION[0], GREEN);
	DrawSquare(CUSHION_POSITION[1], GREEN);
	DrawSquare(CUSHION_POSITION[2], GREEN);
	DrawSquare(CUSHION_POSITION[3], GREEN);
	DrawSquare(CUSHION_POSITION[4], GREEN);
	DrawSquare(CUSHION_POSITION[5], GREEN);
	DrawSquare(CUSHION_POSITION[6], GREEN);
	DrawSquare(CUSHION_POSITION[7], GREEN);

	//ポケット描画
	for (std::vector<Pocket*>::iterator pocket = mPockets.begin(); pocket != mPockets.end(); pocket++){
		DrawCircle((int)(*pocket)->getX(), (int)(*pocket)->getY(), (*pocket)->getSize(), BLACK);
	}
}

//ボールの描画
void OnePlayGame::BallShow(){
	for (std::vector<Ball*>::iterator ball = mBalls.begin(); ball != mBalls.end(); ball++)
		(*ball)->display();
}

//タイムの描画
void OnePlayGame::TimeShow(){
	DrawFormatString(20, BOARD_BOTTOM + 10, GetColor(255, 255, 255), "%d秒", (GetNowCount() - mStartTime) / 1000);
}

//打数の描画
void OnePlayGame::NumShotShow(){
	DrawFormatString(20, BOARD_BOTTOM + 10, GetColor(255, 255, 255), "打数：%d", mNumShot);
}

//ボール・タイム・打数の描画
void OnePlayGame::Display(){
	BoardShow();
	BallShow();
	NumShotShow();
}

//ボールが一つでも動いていればtrue,すべて動いていなければfalseを返す
bool OnePlayGame::BallsMovingCheck(){
	for (std::vector<Ball*>::iterator ball = mBalls.begin(); ball != mBalls.end(); ball++){
		if ((*ball)->movingCheck() == true)
			return true;
	}
	return false;
}

//引数のボールがポケットに入ったかどうか判定する。
bool OnePlayGame::PocketInCheck(Ball* ball){
	for (std::vector<Pocket*>::iterator pocket = mPockets.begin(); pocket != mPockets.end(); pocket++){
		if (((*ball).getT() - (*pocket)->getT()).norm2() < pow((*pocket)->getSize(), 2)){
			return true;
		}
	}
	return false;
}

//ボールの移動処理を行う。
void OnePlayGame::BallsMove(){
	Vector2d sigmentIJ, iV, jV;
	float dotI, dotJ;
	Ball* iBall;
	for (unsigned int i = 0; i < mBalls.size(); i++){
		iBall = mBalls[i];
		iBall->move();

		//ポケットにボールが入ったかチェック
		if (PocketInCheck(mBalls[i]) == true){
			//白ボールがポケットに入ったかチェック
			//白ボールがポケットに入ったらnumShotを＋３
			if (iBall == mPlayer){
				mPlayerExist = false;
				mNumShot = mNumShot + 3;
			}
			else
				mNumColorBall--;
			mBalls.erase(mBalls.begin() + i);
			i--;
			continue;
		}

		//ボール同士の衝突チェック
		Ball* jBall;
		for (unsigned int j = i + 1; j < mBalls.size(); j++){
			jBall = mBalls[j];
			if (((iBall->getT() + iBall->getV()) - (jBall->getT() + jBall->getV())).norm2() < pow(iBall->getSize() + jBall->getSize(), 2)){
				sigmentIJ = (iBall->getT() - jBall->getT()).getNormalizeVector();
				dotI = (jBall->getV() - iBall->getV()) * sigmentIJ;
				dotJ = (iBall->getV() - jBall->getV()) * sigmentIJ;
				iV = dotI * sigmentIJ + iBall->getV();
				jV = dotJ * sigmentIJ + jBall->getV();
				iBall->setV(iV);
				jBall->setV(jV);
			}
		}
	}
}


//白ボールがポケットに入った後の白ボールを置く処理
void OnePlayGame::PlayerSet(int x, int y){
	mPlayer->setT(Vector2d(x, y));
	mPlayer->setV(Vector2d(0, 0));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	mPlayer->display();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//PlayerExitの取得
bool OnePlayGame::GetPlayerExist(){
	return mPlayerExist;
}

//白ボールを置いた時の処理。
void OnePlayGame::PutPlayer(){
	mBalls.push_back(mPlayer);
	mPlayerExist = true;
}

//打数をインクリメント
void OnePlayGame::NumShotPlaPla(){
	mNumShot++;
}

Player* OnePlayGame::GetPlayer(){
	return mPlayer;
}

Scene* OnePlayGame::Update(){
	Display();

	//シーケンス処理
	Scene* next = this;
	Scene* nextChild = mChild->Update();
	if (nextChild != mChild){
		SceneOnePlayGameChild* sceneOnePlayGameChild = dynamic_cast<SceneOnePlayGameChild*>(nextChild);
		if (sceneOnePlayGameChild){
			delete mChild;
			mChild = sceneOnePlayGameChild;
		}
		else{
			next = nextChild;
		}
	}
	return next;
}