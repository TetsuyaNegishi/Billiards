#include"Game.h"
#include<DxLib.h>

Game::Game(){}

void Game::init(){
	SetBackgroundColor(255, 255, 255), SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16); //背景色設定とウィンドウサイズ設定
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	pockets.push_back(Pocket(FIELD_LEFT, FIELD_TOP));
	pockets.push_back(Pocket(FIELD_RIGHT, FIELD_TOP));
	pockets.push_back(Pocket(FIELD_LEFT, FIELD_BOTTOM));
	pockets.push_back(Pocket(FIELD_RIGHT, FIELD_BOTTOM));
	pockets.push_back(Pocket(WINDOW_WIDTH/2, FIELD_TOP));
	pockets.push_back(Pocket(WINDOW_WIDTH/2, FIELD_BOTTOM));
}

void Game::boardShow(){
	const int BROWN = GetColor(153, 76, 0);
	const int DARK_GREEN = GetColor(0, 100, 0);
	const int GREEN = GetColor(0, 200, 0);
	const int BLACK = GetColor(0, 0, 0);
	
	//ビリヤード盤描画
	DrawBox(BOARD_LEFT, BOARD_TOP, BOARD_RIGHT, BOARD_BOTTOM, BROWN, TRUE);
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, FIELD_BOTTOM, DARK_GREEN, TRUE);
	//クッション描画
	DrawBox(FIELD_LEFT, FIELD_TOP, CUSHION_LEFT, FIELD_BOTTOM, GREEN, TRUE);		//左クッション
	DrawBox(FIELD_RIGHT, FIELD_TOP, CUSHION_RIGHT, FIELD_BOTTOM, GREEN, TRUE);		//右クッション
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, CUSHION_TOP, GREEN, TRUE);			//上クッション
	DrawBox(FIELD_LEFT, FIELD_BOTTOM, FIELD_RIGHT, CUSHION_BOTTOM, GREEN, TRUE);	//下クッション
	//ポケット描画
	Pocket pocket;
	for (int i = 0; i < pockets.size(); i++){
		pocket = pockets[i];
		DrawCircle(pocket.getX(), pocket.getY(), pocket.getSize(), BLACK);
	}

}

void Game::main(){
	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		boardShow();
	}
}

void Game::end(){
	DxLib_End(); // DXライブラリ終了処理
}