#include"Game.h"
#include<DxLib.h>
#include<vector>

Game::Game(){}

void Game::init(){
	SetBackgroundColor(255, 255, 255), SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16); //�w�i�F�ݒ�ƃE�B���h�E�T�C�Y�ݒ�
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	const int a = 10;
	pockets.push_back(Pocket(FIELD_LEFT + a, FIELD_TOP + a));
	pockets.push_back(Pocket(FIELD_RIGHT - a, FIELD_TOP + a));
	pockets.push_back(Pocket(FIELD_LEFT + a, FIELD_BOTTOM - a));
	pockets.push_back(Pocket(FIELD_RIGHT - a, FIELD_BOTTOM - a));
	pockets.push_back(Pocket(WINDOW_WIDTH/2, FIELD_TOP + a));
	pockets.push_back(Pocket(WINDOW_WIDTH/2, FIELD_BOTTOM - a));

	player = Player(200, 200, GetColor(255, 255, 255));
}

void Game::boardShow(){
	const int BROWN = GetColor(153, 76, 0);
	const int DARK_GREEN = GetColor(0, 100, 0);
	const int GREEN = GetColor(0, 200, 0);
	const int BLACK = GetColor(0, 0, 0);

	//�r�����[�h�Օ`��
	DrawBox(BOARD_LEFT, BOARD_TOP, BOARD_RIGHT, BOARD_BOTTOM, BROWN, TRUE);
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, FIELD_BOTTOM, DARK_GREEN, TRUE);
	//�N�b�V�����`��
	DrawBox(FIELD_LEFT, FIELD_TOP, CUSHION_LEFT, FIELD_BOTTOM, GREEN, TRUE);		//���N�b�V����
	DrawBox(FIELD_RIGHT, FIELD_TOP, CUSHION_RIGHT, FIELD_BOTTOM, GREEN, TRUE);		//�E�N�b�V����
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, CUSHION_TOP, GREEN, TRUE);			//��N�b�V����
	DrawBox(FIELD_LEFT, FIELD_BOTTOM, FIELD_RIGHT, CUSHION_BOTTOM, GREEN, TRUE);	//���N�b�V����
	//�|�P�b�g�`��
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
	std::vector<Ball*> moveBallsClone = moveBalls;
	for (std::vector<Ball*>::iterator moveBall = moveBallsClone.begin(); moveBall != moveBallsClone.end(); moveBall++){
		(*moveBall)->move();
		if ((*moveBall)->movingCheck() == false)
			moveBalls.erase(moveBall);
	}
}

void Game::clickCheck(){
	int x, y;
	Vector2d direction;
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && moveBalls.size() == 0){
		GetMousePoint(&x, &y);
		direction = Vector2d(x, y) - player.getT();
		direction.normalize();
		player.setV(5*direction);
	}
}

void Game::main(){
	player.setV(Vector2d(2, 2));
	moveBalls.push_back(&player);
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		boardShow();
		ballShow();
		clickCheck();
		update();
	}
}

void Game::end(){
	DxLib_End(); // DX���C�u�����I������
}