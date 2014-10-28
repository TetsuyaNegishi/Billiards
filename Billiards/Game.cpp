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
	
	for (int i = 1; i <= 9; i++){
		auto ball = new Ball(50*i + 50, 100, GetColor(255, 0, 255));
		//ball->setV(Vector2d(0.5, 0.5));
		//movingBalls.push_back(ball);
		balls.push_back(ball);
	}
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
	for (std::vector<Ball*>::iterator ball = balls.begin(); ball != balls.end(); ball++)
		DrawCircle((*ball)->getXi(), (*ball)->getYi(), (*ball)->getSize(), (*ball)->getColor());
}

Ball* Game::collision(Ball* movingBall){
	Ball* addMovingBall = 0;
	Vector2d sigmentBallThis, movingBallV, ballV;
	float dotMovingBall, dotBall;
	for (std::vector<Ball*>::iterator ball = balls.begin(); ball != balls.end(); ball++){
		if (movingBall == (*ball))
			continue;
		if ((movingBall->getT() - (*ball)->getT()).norm2() < pow(movingBall->getSize() + (*ball)->getSize(), 2)){
			sigmentBallThis = (movingBall->getT() - (*ball)->getT()).getNormalizeVector();
			dotMovingBall = ((*ball)->getV() - movingBall->getV()) * sigmentBallThis;
			dotBall = (movingBall->getV() - (*ball)->getV()) * sigmentBallThis;
			movingBallV = dotMovingBall * sigmentBallThis + movingBall->getV();
			ballV = dotBall * sigmentBallThis + (*ball)->getV();
			movingBall->setV(movingBallV);
			(*ball)->setV(ballV);
			addMovingBall = *ball;
			break;
		}
	}
	return addMovingBall;
}

void Game::update(){
	Vector2d sigmentIJ, iV, jV;
	float dotI, dotJ;
	for (unsigned int i = 0; i < balls.size(); i++){
		for (unsigned int j = i+1; j < balls.size(); j++){
			if ((balls[i]->getT() - balls[j]->getT()).norm2() < pow(balls[i]->getSize() + balls[j]->getSize(), 2)){
				sigmentIJ= (balls[i]->getT() - balls[j]->getT()).getNormalizeVector();
				dotI = (balls[j]->getV() - balls[i]->getV()) * sigmentIJ;
				dotJ = (balls[i]->getV() - balls[j]->getV()) * sigmentIJ;
				iV = dotI * sigmentIJ + balls[i]->getV();
				jV = dotJ * sigmentIJ + balls[j]->getV();
				balls[i]->setV(iV);
				balls[j]->setV(jV);
			}
		}
		if (balls[i]->movingCheck() == TRUE)
			balls[i]->move();
	}
	/*
	std::vector<Ball*> addMovingBalls;
	Ball* addMovingBall = 0;
	for (std::vector<Ball*>::iterator movingBall = movingBalls.begin(); movingBall != movingBalls.end();){
		(*movingBall)->move();
		addMovingBall = collision(*movingBall);
		if (addMovingBall != NULL)
			addMovingBalls.push_back(addMovingBall);
		if ((*movingBall)->movingCheck() == false)
			movingBall = movingBalls.erase(movingBall);
		else
			movingBall++;
	}
	for (std::vector<Ball*>::iterator movingBall = addMovingBalls.begin(); movingBall != addMovingBalls.end(); movingBall++){
		movingBalls.push_back(*movingBall);
	}
	*/
}

void Game::clickCheck(){
	int x, y;
	Vector2d direction;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		GetMousePoint(&x, &y);
		direction = Vector2d((float)x, (float)y) - player.getT();
		direction.normalize();
		player.setV(5 * direction);
		movingBalls.push_back(&player);
	}
}

void Game::main(){
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		boardShow();
		ballShow();
		//if (movingBalls.size() == 0)
			clickCheck();
		//else
			update();
	}
}

void Game::end(){
	DxLib_End(); // DXライブラリ終了処理
}