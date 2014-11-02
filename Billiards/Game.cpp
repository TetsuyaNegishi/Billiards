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
static const int CUSHION_VALUE = 20;
const int Game::CUSHION_LEFT = FIELD_LEFT + CUSHION_VALUE;
const int Game::CUSHION_RIGHT = FIELD_RIGHT - CUSHION_VALUE;
const int Game::CUSHION_TOP = FIELD_TOP + CUSHION_VALUE;
const int Game::CUSHION_BOTTOM = FIELD_BOTTOM - CUSHION_VALUE;
static const float CUSHION_SIZE = Pocket::SIZE + 8.0f;
static const float CUSHION_EDGE = 17.0f;
const Vector2d Game::CUSHION_POSITION[][4] = { 
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


//ゲームの初期化
void Game::init(){
	SetBackgroundColor(255, 255, 255), SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16); //背景色設定とウィンドウサイズ設定
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	//ポケット初期設定
	const int a = 10;
	pockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_TOP + a));
	pockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_TOP + a));
	pockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_BOTTOM - a));
	pockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_BOTTOM - a));
	pockets.push_back(new Pocket(WINDOW_WIDTH/2, FIELD_TOP + a));
	pockets.push_back(new Pocket(WINDOW_WIDTH/2, FIELD_BOTTOM - a));

	//startTime設定
	startTime = GetNowCount();
	SetFontSize(20);

	//白ボール（プレイヤー）初期設定
	player = Player(100, (BOARD_BOTTOM-BOARD_TOP)/2 + BOARD_TOP, GetColor(255, 255, 255));
	balls.push_back(&player);
	playerExist = true;

	//ボール初期設定
	for (int i = 1; i <= 9; i++)
		balls.push_back(new Ball(50 * i + 50.0f, 100.0f, GetColor(255, 0, 255)));
}


//任意の四角形を描画
void DrawSquare(const Vector2d position[4], int color){
	DrawTriangle(position[0].x, position[0].y, position[1].x, position[1].y, position[2].x, position[2].y, color, TRUE);
	DrawTriangle(position[1].x, position[1].y, position[2].x, position[2].y, position[3].x, position[3].y, color, TRUE);
}

//ビリヤード盤の描画
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
	for (std::vector<Pocket*>::iterator pocket = pockets.begin(); pocket != pockets.end(); pocket++){
		DrawCircle((int)(*pocket)->getX(), (int)(*pocket)->getY(), (*pocket)->getSize(), BLACK);
	}
}

//ボールの描画
void Game::ballShow(){
	for (std::vector<Ball*>::iterator ball = balls.begin(); ball != balls.end(); ball++)
		(*ball)->display();
}

//タイムの描画
void Game::timeShow(){
	DrawFormatString(20, BOARD_BOTTOM + 10, GetColor(0, 0, 0), "%d秒", (GetNowCount() - startTime) / 1000);
}

//引数のボールがポケットに入ったかどうか判定する。
bool Game::pocketInCheck(Ball* ball){
	for (std::vector<Pocket*>::iterator pocket = pockets.begin(); pocket != pockets.end(); pocket++){
		if (((*ball).getT() - (*pocket)->getT()).norm2() < pow((*pocket)->getSize(), 2)){
			return true;
		}
	}
	return false;
}


//ボール同士の衝突判定を含めたボールの移動処理を行う。
void Game::update(){
	Vector2d sigmentIJ, iV, jV;
	float dotI, dotJ;
	for (unsigned int i = 0; i < balls.size(); i++){

		//ポケットにボールが入ったかチェック
		if (pocketInCheck(balls[i]) == true){
			if (balls[i] == &player)
				playerExist = false;
			balls.erase(balls.begin() + i);
			i--;
			continue;
		}

		//ボール同士の衝突チェック
		for (unsigned int j = i+1; j < balls.size(); j++){
			if (((balls[i]->getT()+balls[i]->getV()) - (balls[j]->getT()+balls[j]->getV())).norm2() < pow(balls[i]->getSize() + balls[j]->getSize(), 2)){
				sigmentIJ= (balls[i]->getT() - balls[j]->getT()).getNormalizeVector();
				dotI = (balls[j]->getV() - balls[i]->getV()) * sigmentIJ;
				dotJ = (balls[i]->getV() - balls[j]->getV()) * sigmentIJ;
				iV = dotI * sigmentIJ + balls[i]->getV();
				jV = dotJ * sigmentIJ + balls[j]->getV();
				balls[i]->setV(iV);
				balls[j]->setV(jV);
			}
		}

		balls[i]->move();
	}
}

//クリックした方向へ白ボールを打つ。白ボールの速さは白ボールとクリック座標との距離で決定する。
void Game::clickCheck(bool* ballsMoving){
	int x, y;
	float speedSize;
	Vector2d direction;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		GetMousePoint(&x, &y);
		direction = Vector2d((float)x, (float)y) - player.getT();
		speedSize = direction.norm() / 5;
		if (speedSize >= 20) speedSize = 20;
		direction.normalize();
		player.setV(speedSize * direction);
		*ballsMoving = true;
	}
}

//ボールが一つでも動いていればtrue,すべて動いていなければfalseを返す
bool Game::ballsMovingCheck(){
	for (std::vector<Ball*>::iterator ball = balls.begin(); ball != balls.end(); ball++){
		if ((*ball)->movingCheck() == true)
			return true;
	}
	return false;
}


//白ボールがポケットに入ってしまった場合の処理
//マウスカーソルに白ボールがついてくる
//マウスをクリックして離した位置に白ボールを配置する。
void Game::playerSet(bool* prevMouseInput){
	int x, y;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		if (!(*prevMouseInput))
			*prevMouseInput = true;
	}
	if (!(GetMouseInput() & MOUSE_INPUT_LEFT)){
		if (*prevMouseInput){
			*prevMouseInput = false;
			balls.push_back(&player);
			playerExist = true;
		}
	}
	GetMousePoint(&x, &y);
	player.setT(Vector2d(x, y));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	player.display();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


//メイン関数
void Game::main(){
	bool ballsMoving = false;
	bool prevMouseInput = false;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		boardShow();
		ballShow();
		timeShow();
		if (ballsMoving == true){
			update();
			ballsMoving = ballsMovingCheck();
		}else{
			if (!playerExist)
				playerSet(&prevMouseInput); //白ボールがポケットに入った時
			else
				clickCheck(&ballsMoving);
		}
	}
}

void Game::end(){
	DxLib_End(); // DXライブラリ終了処理
}