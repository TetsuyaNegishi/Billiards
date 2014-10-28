#include"Game.h"

Game::Game(){}

//ウィンドウサイズ指定
const int Game::WINDOW_WIDTH = 800;	//ウィンドウ幅
const int Game::WINDOW_HEIGHT = 450;	//ウィンドウ高さ
const int Game::STATUS_HEIGHT = 50;	//ステータス表示幅

//ボード座標指定
static const int BOARD_VALUE = 15;
const int Game::BOARD_LEFT = BOARD_VALUE;
const int Game::BOARD_RIGHT = WINDOW_WIDTH - BOARD_VALUE;
const int Game::BOARD_TOP = BOARD_VALUE;
const int Game::BOARD_BOTTOM = WINDOW_HEIGHT - STATUS_HEIGHT - BOARD_VALUE;

//フィールド座標指定
static const int FIELD_VALUE = 20;
const int Game::FIELD_LEFT = BOARD_LEFT + FIELD_VALUE;
const int Game::FIELD_RIGHT = BOARD_RIGHT - FIELD_VALUE;
const int Game::FIELD_TOP = BOARD_TOP + FIELD_VALUE;
const int Game::FIELD_BOTTOM = BOARD_BOTTOM - FIELD_VALUE;

//クッション座標指定
static const int CUSHION_VALUE = 15;
const int Game::CUSHION_LEFT = FIELD_LEFT + CUSHION_VALUE;
const int Game::CUSHION_RIGHT = FIELD_RIGHT - CUSHION_VALUE;
const int Game::CUSHION_TOP = FIELD_TOP + CUSHION_VALUE;
const int Game::CUSHION_BOTTOM = FIELD_BOTTOM - CUSHION_VALUE;
static const int CUSHION_SIZE = Pocket::SIZE + 8;
static const int CUSHION_EDGE = 17;
const int Game::CUSHION_POSITION[][8] = { 
		//左クッション
		{ FIELD_LEFT, FIELD_TOP + CUSHION_SIZE, CUSHION_LEFT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE, 
		FIELD_LEFT, FIELD_BOTTOM - CUSHION_SIZE, CUSHION_LEFT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE },
		//右クッション
		{ FIELD_RIGHT, FIELD_TOP + CUSHION_SIZE, CUSHION_RIGHT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE,
		FIELD_RIGHT, FIELD_BOTTOM - CUSHION_SIZE, CUSHION_RIGHT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE },
		//左上クッション
		{ FIELD_LEFT + CUSHION_SIZE, FIELD_TOP, FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, CUSHION_TOP, 
		WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, FIELD_TOP, WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, CUSHION_TOP },
		//右上クッション
		{ FIELD_RIGHT - CUSHION_SIZE, FIELD_TOP, FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, CUSHION_TOP, 
		WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, FIELD_TOP, WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, CUSHION_TOP },
		//左下クッション
		{ FIELD_LEFT + CUSHION_SIZE, FIELD_BOTTOM, FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, CUSHION_BOTTOM, 
		WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, FIELD_BOTTOM, WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, CUSHION_BOTTOM },
		//右下クッション
		{ FIELD_RIGHT - CUSHION_SIZE, FIELD_BOTTOM, FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, CUSHION_BOTTOM, 
		WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, FIELD_BOTTOM, WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, CUSHION_BOTTOM }
};

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
		auto ball = new Ball(50*i + 50.0f, 100.0f, GetColor(255, 0, 255));
		balls.push_back(ball);
	}
}

void DrawSquare(const int position[8], int color){
	DrawTriangle(position[0], position[1], position[2], position[3], position[4], position[5], color, TRUE);
	DrawTriangle(position[2], position[3], position[4], position[5], position[6], position[7], color, TRUE);
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
	DrawSquare(CUSHION_POSITION[0], GREEN);
	DrawSquare(CUSHION_POSITION[1], GREEN);
	DrawSquare(CUSHION_POSITION[2], GREEN);
	DrawSquare(CUSHION_POSITION[3], GREEN);
	DrawSquare(CUSHION_POSITION[4], GREEN);
	DrawSquare(CUSHION_POSITION[5], GREEN);
	DrawSquare(CUSHION_POSITION[6], GREEN);
	DrawSquare(CUSHION_POSITION[7], GREEN);

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

void Game::update(){
	Vector2d sigmentIJ, iV, jV;
	float dotI, dotJ;
	for (unsigned int i = 0; i < balls.size(); i++){
		balls[i]->move();
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
	}
}

void Game::clickCheck(bool* ballsMoving){
	int x, y;
	Vector2d direction;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		GetMousePoint(&x, &y);
		direction = Vector2d((float)x, (float)y) - player.getT();
		direction.normalize();
		player.setV(10 * direction);
		*ballsMoving = true;
	}
}

bool Game::ballsMovingCheck(){
	for (std::vector<Ball*>::iterator ball = balls.begin(); ball != balls.end(); ball++){
		if ((*ball)->movingCheck() == true)
			return true;
	}
	return false;
}

void Game::main(){
	bool ballsMoving = false;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		boardShow();
		ballShow();
		if (ballsMoving == true){
			update();
			ballsMoving = ballsMovingCheck();
		}else{
			clickCheck(&ballsMoving);
		}
	}
}

void Game::end(){
	DxLib_End(); // DXライブラリ終了処理
}