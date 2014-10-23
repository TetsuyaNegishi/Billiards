#include"Game.h"
#include<DxLib.h>

Game::Game(){}

void Game::init(){
	SetBackgroundColor(255, 255, 255), SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16); //�w�i�F�ݒ�ƃE�B���h�E�T�C�Y�ݒ�
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

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
	
	//�r�����[�h�Օ`��
	DrawBox(BOARD_LEFT, BOARD_TOP, BOARD_RIGHT, BOARD_BOTTOM, BROWN, TRUE);
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, FIELD_BOTTOM, DARK_GREEN, TRUE);
	//�N�b�V�����`��
	DrawBox(FIELD_LEFT, FIELD_TOP, CUSHION_LEFT, FIELD_BOTTOM, GREEN, TRUE);		//���N�b�V����
	DrawBox(FIELD_RIGHT, FIELD_TOP, CUSHION_RIGHT, FIELD_BOTTOM, GREEN, TRUE);		//�E�N�b�V����
	DrawBox(FIELD_LEFT, FIELD_TOP, FIELD_RIGHT, CUSHION_TOP, GREEN, TRUE);			//��N�b�V����
	DrawBox(FIELD_LEFT, FIELD_BOTTOM, FIELD_RIGHT, CUSHION_BOTTOM, GREEN, TRUE);	//���N�b�V����
	//�|�P�b�g�`��


}

void Game::main(){
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		boardShow();
	}
}

void Game::end(){
	DxLib_End(); // DX���C�u�����I������
}