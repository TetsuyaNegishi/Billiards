#include"Game.h"

Game::Game(){}

//�E�B���h�E�T�C�Y�w��
const int Game::WINDOW_WIDTH = 800;	//�E�B���h�E��
const int Game::WINDOW_HEIGHT = 450;	//�E�B���h�E����
const int Game::STATUS_HEIGHT = 50;	//�X�e�[�^�X�\����

//�{�[�h���W�w��
static const int BOARD_VALUE = 15;
const int Game::BOARD_LEFT = BOARD_VALUE;
const int Game::BOARD_RIGHT = WINDOW_WIDTH - BOARD_VALUE;
const int Game::BOARD_TOP = BOARD_VALUE;
const int Game::BOARD_BOTTOM = WINDOW_HEIGHT - STATUS_HEIGHT - BOARD_VALUE;

//�t�B�[���h���W�w��
static const int FIELD_VALUE = 20;
const int Game::FIELD_LEFT = BOARD_LEFT + FIELD_VALUE;
const int Game::FIELD_RIGHT = BOARD_RIGHT - FIELD_VALUE;
const int Game::FIELD_TOP = BOARD_TOP + FIELD_VALUE;
const int Game::FIELD_BOTTOM = BOARD_BOTTOM - FIELD_VALUE;

//�N�b�V�������W�w��
static const int CUSHION_VALUE = 15;
const int Game::CUSHION_LEFT = FIELD_LEFT + CUSHION_VALUE;
const int Game::CUSHION_RIGHT = FIELD_RIGHT - CUSHION_VALUE;
const int Game::CUSHION_TOP = FIELD_TOP + CUSHION_VALUE;
const int Game::CUSHION_BOTTOM = FIELD_BOTTOM - CUSHION_VALUE;
static const int CUSHION_SIZE = Pocket::SIZE + 8;
static const int CUSHION_EDGE = 17;
const int Game::CUSHION_POSITION[][8] = { 
		//���N�b�V����
		{ FIELD_LEFT, FIELD_TOP + CUSHION_SIZE, CUSHION_LEFT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE, 
		FIELD_LEFT, FIELD_BOTTOM - CUSHION_SIZE, CUSHION_LEFT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE },
		//�E�N�b�V����
		{ FIELD_RIGHT, FIELD_TOP + CUSHION_SIZE, CUSHION_RIGHT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE,
		FIELD_RIGHT, FIELD_BOTTOM - CUSHION_SIZE, CUSHION_RIGHT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE },
		//����N�b�V����
		{ FIELD_LEFT + CUSHION_SIZE, FIELD_TOP, FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, CUSHION_TOP, 
		WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, FIELD_TOP, WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, CUSHION_TOP },
		//�E��N�b�V����
		{ FIELD_RIGHT - CUSHION_SIZE, FIELD_TOP, FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, CUSHION_TOP, 
		WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, FIELD_TOP, WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, CUSHION_TOP },
		//�����N�b�V����
		{ FIELD_LEFT + CUSHION_SIZE, FIELD_BOTTOM, FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, CUSHION_BOTTOM, 
		WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, FIELD_BOTTOM, WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, CUSHION_BOTTOM },
		//�E���N�b�V����
		{ FIELD_RIGHT - CUSHION_SIZE, FIELD_BOTTOM, FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, CUSHION_BOTTOM, 
		WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, FIELD_BOTTOM, WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, CUSHION_BOTTOM }
};


//�Q�[���̏�����
void Game::init(){
	SetBackgroundColor(255, 255, 255), SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16); //�w�i�F�ݒ�ƃE�B���h�E�T�C�Y�ݒ�
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	//�|�P�b�g�����ݒ�
	const int a = 10;
	pockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_TOP + a));
	pockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_TOP + a));
	pockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_BOTTOM - a));
	pockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_BOTTOM - a));
	pockets.push_back(new Pocket(WINDOW_WIDTH/2, FIELD_TOP + a));
	pockets.push_back(new Pocket(WINDOW_WIDTH/2, FIELD_BOTTOM - a));

	//���{�[���i�v���C���[�j�����ݒ�
	player = Player(200, 200, GetColor(255, 255, 255));
	balls.push_back(&player);
	
	//�{�[�������ݒ�
	for (int i = 1; i <= 9; i++)
		balls.push_back(new Ball(50 * i + 50.0f, 100.0f, GetColor(255, 0, 255)));
}


//�C�ӂ̎l�p�`��`��
void DrawSquare(const int position[8], int color){
	DrawTriangle(position[0], position[1], position[2], position[3], position[4], position[5], color, TRUE);
	DrawTriangle(position[2], position[3], position[4], position[5], position[6], position[7], color, TRUE);
}

//�r�����[�h�Ղ̕`��
void Game::boardShow(){
	const int BROWN = GetColor(153, 76, 0);
	const int DARK_GREEN = GetColor(0, 100, 0);
	const int GREEN = GetColor(0, 200, 0);
	const int BLACK = GetColor(0, 0, 0);

	//�r�����[�h�Օ`��
	DrawBox(BOARD_LEFT, BOARD_TOP, BOARD_RIGHT, BOARD_BOTTOM, BROWN, TRUE);
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, FIELD_BOTTOM, DARK_GREEN, TRUE);

	//�N�b�V�����`��
	DrawSquare(CUSHION_POSITION[0], GREEN);
	DrawSquare(CUSHION_POSITION[1], GREEN);
	DrawSquare(CUSHION_POSITION[2], GREEN);
	DrawSquare(CUSHION_POSITION[3], GREEN);
	DrawSquare(CUSHION_POSITION[4], GREEN);
	DrawSquare(CUSHION_POSITION[5], GREEN);
	DrawSquare(CUSHION_POSITION[6], GREEN);
	DrawSquare(CUSHION_POSITION[7], GREEN);

	//�|�P�b�g�`��
	for (std::vector<Pocket*>::iterator pocket = pockets.begin(); pocket != pockets.end(); pocket++){
		DrawCircle((int)(*pocket)->getX(), (int)(*pocket)->getY(), (*pocket)->getSize(), BLACK);
	}
}

//�{�[���̕`��
void Game::ballShow(){
	for (std::vector<Ball*>::iterator ball = balls.begin(); ball != balls.end(); ball++)
		DrawCircle((*ball)->getXi(), (*ball)->getYi(), (*ball)->getSize(), (*ball)->getColor());
}

bool Game::pocketInCheck(Ball* ball){
	for (std::vector<Pocket*>::iterator pocket = pockets.begin(); pocket != pockets.end(); pocket++){
		if (((*ball).getT() - (*pocket)->getT()).norm2() < pow((*pocket)->getSize(), 2)){
			//balls.erase(ball);
			return true;
		}
	}
	return false;
}

//�Փ˔�����܂߂��{�[���̈ړ��������s���B
void Game::update(){
	Vector2d sigmentIJ, iV, jV;
	float dotI, dotJ;
	for (unsigned int i = 0; i < balls.size(); i++){
		if (pocketInCheck(balls[i]) == true){
			//if (balls[i] == player)
			balls.erase(balls.begin() + i);
			i--;
			continue;
		}
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

//�N���b�N���������֔��{�[����łB���{�[���̑����͔��{�[���ƃN���b�N���W�Ƃ̋����Ō��肷��B
void Game::clickCheck(bool* ballsMoving){
	int x, y;
	float speedSize;
	Vector2d direction;
	if (GetMouseInput() & MOUSE_INPUT_LEFT){
		GetMousePoint(&x, &y);
		direction = Vector2d((float)x, (float)y) - player.getT();
		speedSize = direction.norm() / 5;
		if (speedSize >= 15) speedSize = 15;
		direction.normalize();
		player.setV(speedSize * direction);
		*ballsMoving = true;
	}
}

//�{�[������ł������Ă����true,���ׂē����Ă��Ȃ����false��Ԃ�
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
	DxLib_End(); // DX���C�u�����I������
}