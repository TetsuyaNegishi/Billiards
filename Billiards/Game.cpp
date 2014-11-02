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
static const int CUSHION_VALUE = 20;
const int Game::CUSHION_LEFT = FIELD_LEFT + CUSHION_VALUE;
const int Game::CUSHION_RIGHT = FIELD_RIGHT - CUSHION_VALUE;
const int Game::CUSHION_TOP = FIELD_TOP + CUSHION_VALUE;
const int Game::CUSHION_BOTTOM = FIELD_BOTTOM - CUSHION_VALUE;
static const float CUSHION_SIZE = Pocket::SIZE + 8.0f;
static const float CUSHION_EDGE = 17.0f;
const Vector2d Game::CUSHION_POSITION[][4] = { 
		//���N�b�V����
		{ Vector2d((float)FIELD_LEFT, FIELD_TOP + CUSHION_SIZE), Vector2d((float)CUSHION_LEFT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE), 
		Vector2d((float)FIELD_LEFT, FIELD_BOTTOM - CUSHION_SIZE), Vector2d((float)CUSHION_LEFT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE) },
		//�E�N�b�V����
		{ Vector2d((float)FIELD_RIGHT, FIELD_TOP + CUSHION_SIZE), Vector2d((float)CUSHION_RIGHT, FIELD_TOP + CUSHION_SIZE + CUSHION_EDGE),
		Vector2d((float)FIELD_RIGHT, FIELD_BOTTOM - CUSHION_SIZE), Vector2d((float)CUSHION_RIGHT, FIELD_BOTTOM - CUSHION_SIZE - CUSHION_EDGE) },
		//����N�b�V����
		{ Vector2d(FIELD_LEFT + CUSHION_SIZE, (float)FIELD_TOP), Vector2d(FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, (float)CUSHION_TOP),
		Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, (float)FIELD_TOP), Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, (float)CUSHION_TOP) },
		//�E��N�b�V����
		{ Vector2d(FIELD_RIGHT - CUSHION_SIZE, (float)FIELD_TOP), Vector2d(FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, (float)CUSHION_TOP),
		Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, (float)FIELD_TOP), Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, (float)CUSHION_TOP) },
		//�����N�b�V����
		{ Vector2d(FIELD_LEFT + CUSHION_SIZE, (float)FIELD_BOTTOM), Vector2d(FIELD_LEFT + CUSHION_SIZE + CUSHION_EDGE, (float)CUSHION_BOTTOM),
		Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10, (float)FIELD_BOTTOM), Vector2d(WINDOW_WIDTH / 2 - CUSHION_SIZE + 10 - CUSHION_EDGE, (float)CUSHION_BOTTOM) },
		//�E���N�b�V����
		{ Vector2d(FIELD_RIGHT - CUSHION_SIZE, (float)FIELD_BOTTOM), Vector2d(FIELD_RIGHT - CUSHION_SIZE - CUSHION_EDGE, (float)CUSHION_BOTTOM),
		Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10, (float)FIELD_BOTTOM), Vector2d(WINDOW_WIDTH / 2 + CUSHION_SIZE - 10 + CUSHION_EDGE, (float)CUSHION_BOTTOM) }
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

	//startTime�ݒ�
	startTime = GetNowCount();
	SetFontSize(20);

	//���{�[���i�v���C���[�j�����ݒ�
	player = Player(100, (BOARD_BOTTOM-BOARD_TOP)/2 + BOARD_TOP, GetColor(255, 255, 255));
	balls.push_back(&player);
	playerExist = true;

	//�{�[�������ݒ�
	for (int i = 1; i <= 9; i++)
		balls.push_back(new Ball(50 * i + 50.0f, 100.0f, GetColor(255, 0, 255)));
}


//�C�ӂ̎l�p�`��`��
void DrawSquare(const Vector2d position[4], int color){
	DrawTriangle(position[0].x, position[0].y, position[1].x, position[1].y, position[2].x, position[2].y, color, TRUE);
	DrawTriangle(position[1].x, position[1].y, position[2].x, position[2].y, position[3].x, position[3].y, color, TRUE);
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
		(*ball)->display();
}

//�^�C���̕`��
void Game::timeShow(){
	DrawFormatString(20, BOARD_BOTTOM + 10, GetColor(0, 0, 0), "%d�b", (GetNowCount() - startTime) / 1000);
}

//�����̃{�[�����|�P�b�g�ɓ��������ǂ������肷��B
bool Game::pocketInCheck(Ball* ball){
	for (std::vector<Pocket*>::iterator pocket = pockets.begin(); pocket != pockets.end(); pocket++){
		if (((*ball).getT() - (*pocket)->getT()).norm2() < pow((*pocket)->getSize(), 2)){
			return true;
		}
	}
	return false;
}


//�{�[�����m�̏Փ˔�����܂߂��{�[���̈ړ��������s���B
void Game::update(){
	Vector2d sigmentIJ, iV, jV;
	float dotI, dotJ;
	for (unsigned int i = 0; i < balls.size(); i++){

		//�|�P�b�g�Ƀ{�[�������������`�F�b�N
		if (pocketInCheck(balls[i]) == true){
			if (balls[i] == &player)
				playerExist = false;
			balls.erase(balls.begin() + i);
			i--;
			continue;
		}

		//�{�[�����m�̏Փ˃`�F�b�N
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

//�N���b�N���������֔��{�[����łB���{�[���̑����͔��{�[���ƃN���b�N���W�Ƃ̋����Ō��肷��B
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

//�{�[������ł������Ă����true,���ׂē����Ă��Ȃ����false��Ԃ�
bool Game::ballsMovingCheck(){
	for (std::vector<Ball*>::iterator ball = balls.begin(); ball != balls.end(); ball++){
		if ((*ball)->movingCheck() == true)
			return true;
	}
	return false;
}


//���{�[�����|�P�b�g�ɓ����Ă��܂����ꍇ�̏���
//�}�E�X�J�[�\���ɔ��{�[�������Ă���
//�}�E�X���N���b�N���ė������ʒu�ɔ��{�[����z�u����B
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


//���C���֐�
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
				playerSet(&prevMouseInput); //���{�[�����|�P�b�g�ɓ�������
			else
				clickCheck(&ballsMoving);
		}
	}
}

void Game::end(){
	DxLib_End(); // DX���C�u�����I������
}