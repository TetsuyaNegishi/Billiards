#include"Game.h"
#include<DxLib.h>
#include<vector>

Game::Game(){}

void Game::init(){
	SetBackgroundColor(255, 255, 255), SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16); //背景色設定とウィンドウサイズ設定
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	const int a = 10;
	pockets.push_back(Pocket(FIELD_LEFT + a, FIELD_TOP + a));
	pockets.push_back(Pocket(FIELD_RIGHT - a, FIELD_TOP + a));
	pockets.push_back(Pocket(FIELD_LEFT + a, FIELD_BOTTOM - a));
	pockets.push_back(Pocket(FIELD_RIGHT - a, FIELD_BOTTOM - a));
	pockets.push_back(Pocket(WINDOW_WIDTH/2, FIELD_TOP + a));
	pockets.push_back(Pocket(WINDOW_WIDTH/2, FIELD_BOTTOM - a));

	player = Player(200, 200, GetColor(255, 255, 255));
	balls.push_back(&player);
	
	Ball ball = Ball(600, 200, GetColor(255, 0, 0));
	balls.push_back(&ball);
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
	for (unsigned int i = 0; i < pockets.size(); i++){
		pocket = pockets[i];
		DrawCircle((int)pocket.getX(), (int)pocket.getY(), pocket.getSize(), BLACK);
	}
}

void Game::ballShow(){
	DrawCircle(player.getXi(), player.getYi(), player.getSize(), player.getColor());
}

void Game::update(){
	for (std::vector<Ball*>::iterator movingBall = movingBalls.begin(); movingBall != movingBalls.end();){
		(*movingBall)->move();
		if ((*movingBall)->movingCheck() == false)
			movingBall = movingBalls.erase(movingBall);
		else
			movingBall++;
	}
}

void Game::clickCheck(){
	int x, y;
	Vector2d direction;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		GetMousePoint(&x, &y);
		direction = Vector2d(x, y) - player.getT();
		direction.normalize();
		player.setV(4 * direction);
		movingBalls.push_back(&player);
	}
}

void Game::main(){
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		boardShow();
		ballShow();
		if (movingBalls.size() == 0)
			clickCheck();
		else
			update();
	}
}

void Game::end(){
	DxLib_End(); // DXライブラリ終了処理
}