#include"OnePlayGame.h"
#include<DxLib.h>
#include"Play.h"
#include"MainLoop.h"

//�E�B���h�E�T�C�Y�w��
const int OnePlayGame::WINDOW_WIDTH = MainLoop::WINDOW_WIDTH;	//�E�B���h�E��
const int OnePlayGame::WINDOW_HEIGHT = MainLoop::WINDOW_HEIGHT;	//�E�B���h�E����
const int OnePlayGame::STATUS_HEIGHT = 50;	//�X�e�[�^�X�\����

//�{�[�h���W�w��
static const int BOARD_VALUE = 15;
const int OnePlayGame::BOARD_LEFT = BOARD_VALUE;
const int OnePlayGame::BOARD_RIGHT = WINDOW_WIDTH - BOARD_VALUE;
const int OnePlayGame::BOARD_TOP = BOARD_VALUE;
const int OnePlayGame::BOARD_BOTTOM = WINDOW_HEIGHT - STATUS_HEIGHT - BOARD_VALUE;

//�t�B�[���h���W�w��
static const int FIELD_VALUE = 20;
const int OnePlayGame::FIELD_LEFT = BOARD_LEFT + FIELD_VALUE;
const int OnePlayGame::FIELD_RIGHT = BOARD_RIGHT - FIELD_VALUE;
const int OnePlayGame::FIELD_TOP = BOARD_TOP + FIELD_VALUE;
const int OnePlayGame::FIELD_BOTTOM = BOARD_BOTTOM - FIELD_VALUE;

//�N�b�V�������W�w��
static const int CUSHION_VALUE = 20;
const int OnePlayGame::CUSHION_LEFT = FIELD_LEFT + CUSHION_VALUE;
const int OnePlayGame::CUSHION_RIGHT = FIELD_RIGHT - CUSHION_VALUE;
const int OnePlayGame::CUSHION_TOP = FIELD_TOP + CUSHION_VALUE;
const int OnePlayGame::CUSHION_BOTTOM = FIELD_BOTTOM - CUSHION_VALUE;
static const float CUSHION_SIZE = Pocket::SIZE + 8.0f;
static const float CUSHION_EDGE = 17.0f;
const Vector2d OnePlayGame::CUSHION_POSITION[][4] = {
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

OnePlayGame::OnePlayGame(){
	//�V�[�P���X����
	mChild = new Play(this);

	//�|�P�b�g�����ݒ�
	const int a = 10;
	mPockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_TOP + a));
	mPockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_TOP + a));
	mPockets.push_back(new Pocket(FIELD_LEFT + a, FIELD_BOTTOM - a));
	mPockets.push_back(new Pocket(FIELD_RIGHT - a, FIELD_BOTTOM - a));
	mPockets.push_back(new Pocket(WINDOW_WIDTH / 2, FIELD_TOP + a));
	mPockets.push_back(new Pocket(WINDOW_WIDTH / 2, FIELD_BOTTOM - a));

	//numShot�ݒ�
	mNumShot = 0;

	//�{�[�������ݒ�
	const int Red = GetColor(255, 0, 0);
	const Vector2d Center = Vector2d(MainLoop::WINDOW_WIDTH / 2, (BOARD_BOTTOM - BOARD_TOP) / 2 + BOARD_TOP);
	mBalls.push_back(new Ball(Center.x + 150, Center.y, Red));
	mBalls.push_back(new Ball(Center.x + 175, Center.y + 25, Red));
	mBalls.push_back(new Ball(Center.x + 175, Center.y - 25, Red));
	mBalls.push_back(new Ball(Center.x + 200, Center.y, Red));
	mBalls.push_back(new Ball(Center.x + 200, Center.y + 50, Red));
	mBalls.push_back(new Ball(Center.x + 200, Center.y - 50, Red));
	mBalls.push_back(new Ball(Center.x + 225, Center.y + 25, Red));
	mBalls.push_back(new Ball(Center.x + 225, Center.y - 25, Red));
	mBalls.push_back(new Ball(Center.x + 250, Center.y, Red));
	mNumColorBall = mBalls.size();

	//���{�[���i�v���C���[�j�����ݒ�
	mPlayer = new Player(200, (BOARD_BOTTOM - BOARD_TOP) / 2 + BOARD_TOP, GetColor(255, 255, 255));
	mBalls.push_back(mPlayer);
	mPlayerExist = true;

	//�V���b�g�p���[������
	mShotPower = 0.0f;

	//�t�H���g�ݒ�
	SetFontSize(40);
}

//�C�ӂ̎l�p�`��`��
void OnePlayGame::DrawSquare(const Vector2d position[4], int color){
	DrawTriangle(position[0].x, position[0].y, position[1].x, position[1].y, position[2].x, position[2].y, color, TRUE);
	DrawTriangle(position[1].x, position[1].y, position[2].x, position[2].y, position[3].x, position[3].y, color, TRUE);
}

//�r�����[�h�Ղ̕`��
void OnePlayGame::BoardShow(){
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
	for (std::vector<Pocket*>::iterator pocket = mPockets.begin(); pocket != mPockets.end(); pocket++){
		DrawCircle((int)(*pocket)->getX(), (int)(*pocket)->getY(), (*pocket)->getSize(), BLACK);
	}
}

//�{�[���̕`��
void OnePlayGame::BallShow(){
	for (std::vector<Ball*>::iterator ball = mBalls.begin(); ball != mBalls.end(); ball++)
		(*ball)->display();
}

//�Ő��̕`��
void OnePlayGame::NumShotShow(){
	DrawFormatString(20, BOARD_BOTTOM + 10, GetColor(255, 255, 255), "�Ő��F%d", mNumShot);
}

void OnePlayGame::ShotPowerShow(){
	DrawFormatString(MainLoop::WINDOW_WIDTH/2, BOARD_BOTTOM + 10, GetColor(255, 255, 255), "�́F%d", (int)mShotPower);
}

//�{�[���E�^�C���E�Ő��̕`��
void OnePlayGame::Display(){
	BoardShow();
	BallShow();
	NumShotShow();
	ShotPowerShow();
}

//�{�[������ł������Ă����true,���ׂē����Ă��Ȃ����false��Ԃ�
bool OnePlayGame::BallsMovingCheck(){
	for (std::vector<Ball*>::iterator ball = mBalls.begin(); ball != mBalls.end(); ball++){
		if ((*ball)->movingCheck() == true)
			return true;
	}
	return false;
}

//�����̃{�[�����|�P�b�g�ɓ��������ǂ������肷��B
bool OnePlayGame::PocketInCheck(Ball* ball){
	for (std::vector<Pocket*>::iterator pocket = mPockets.begin(); pocket != mPockets.end(); pocket++){
		if (((*ball).getT() - (*pocket)->getT()).norm2() < pow((*pocket)->getSize(), 2)){
			return true;
		}
	}
	return false;
}

//wallPosition�����񂾐����ball������Δ������������Atrue��Ԃ�
bool OnePlayGame::wallCollisionCheck(Ball* ball, Vector2d wallPosition1, Vector2d wallPosition2){
	Vector2d wallVector;
	float crossProduct, sin;
	wallVector = (wallPosition1 - wallPosition2).getNormalizeVector();
	crossProduct = Cross(wallVector, ball->getT() - wallPosition1);
	if (fabs(crossProduct) < ball->getSize()){
		//sin = Cross(ball->getV(), wallVector) / ( ball->getV().norm()*wallVector.norm());
		//ball->setT(ball->getT() - (crossProduct / sin + ball->getSize()) * ball->getV().getNormalizeVector());
		//ball->setT(ball->getT() + crossProduct * NormalVectorLeft(wallVector));
		ball->setV(ball->getV() - 2 * (NormalVectorLeft(wallVector)*ball->getV()) * NormalVectorLeft(wallVector));
		return true;
	}
	return false;
}


//�N�b�V�����Ƃ̏Փˏ���
void OnePlayGame::CushionCollision(Ball* ball){
	Vector2d check = ball->getT();

	//��N�b�V�����Փ˔���
	if (OnePlayGame::CUSHION_TOP > (check.y - ball->getSize())){
		//���p����
		if (OnePlayGame::CUSHION_POSITION[2][1].x > ball->getX()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[2][0], OnePlayGame::CUSHION_POSITION[2][1]))
				return;
		}
		//�����p����
		else if (OnePlayGame::CUSHION_POSITION[2][3].x < ball->getX() && OnePlayGame::CUSHION_POSITION[3][3].x > ball->getX()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[2][2], OnePlayGame::CUSHION_POSITION[2][3]))
				return;
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[3][2], OnePlayGame::CUSHION_POSITION[3][3]))
				return;
		}
		//�E�p����
		else if (OnePlayGame::CUSHION_POSITION[3][1].x < ball->getX()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[3][0], OnePlayGame::CUSHION_POSITION[3][1]))
				return;
		}
		else{
			ball->setV( Vector2d(ball->getV().x, ball->getV().y * -1) );
			ball->setY(OnePlayGame::CUSHION_TOP + ball->getSize());
		}
	}

	//���N�b�V��������
	else if (OnePlayGame::CUSHION_BOTTOM < (check.y + ball->getSize())){
		//���p����
		if (OnePlayGame::CUSHION_POSITION[4][1].x > ball->getX()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[4][0], OnePlayGame::CUSHION_POSITION[4][1]))
				return;
		}
		//�����p����
		else if (OnePlayGame::CUSHION_POSITION[4][3].x < ball->getX() && OnePlayGame::CUSHION_POSITION[5][3].x > ball->getX()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[4][2], OnePlayGame::CUSHION_POSITION[4][3]))
				return;
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[5][2], OnePlayGame::CUSHION_POSITION[5][3]))
				return;
		}
		//�E�p����
		else if (OnePlayGame::CUSHION_POSITION[5][1].x < ball->getX()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[5][0], OnePlayGame::CUSHION_POSITION[5][1]))
				return;
		}
		else{
			ball->setV(Vector2d(ball->getV().x, ball->getV().y * -1));
			ball->setY(OnePlayGame::CUSHION_BOTTOM - ball->getSize());
		}
	}

	//���N�b�V��������
	if (OnePlayGame::CUSHION_LEFT > (check.x - ball->getSize())){
		//��p����
		if (OnePlayGame::CUSHION_POSITION[0][1].y > ball->getY()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[0][0], OnePlayGame::CUSHION_POSITION[0][1]))
				return;
		}
		//���p����
		else if (OnePlayGame::CUSHION_POSITION[0][3].y < ball->getY()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[0][2], OnePlayGame::CUSHION_POSITION[0][3]))
				return;
		}
		else{
			ball->setV(Vector2d(ball->getV().x * -1, ball->getV().y));
			ball->setX(OnePlayGame::CUSHION_LEFT + ball->getSize());
		}
	}

	//�E�N�b�V��������
	else if (OnePlayGame::CUSHION_RIGHT < (check.x + ball->getSize())){
		//��p����
		if (OnePlayGame::CUSHION_POSITION[1][1].y > ball->getY()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[1][0], OnePlayGame::CUSHION_POSITION[1][1]))
				return;
		}
		//���p����
		else if (OnePlayGame::CUSHION_POSITION[1][3].y < ball->getY()){
			if (wallCollisionCheck(ball, OnePlayGame::CUSHION_POSITION[1][2], OnePlayGame::CUSHION_POSITION[1][3]))
				return;
		}
		else{
			ball->setV(Vector2d(ball->getV().x * -1, ball->getV().y));
			ball->setX(OnePlayGame::CUSHION_RIGHT - ball->getSize());
		}
	}
}

//�{�[���̈ړ��������s���B
void OnePlayGame::BallsMove(){
	Vector2d sigmentIJ, iV, jV;
	float dotI, dotJ;
	Ball* iBall;
	for (unsigned int i = 0; i < mBalls.size(); i++){
		iBall = mBalls[i];
		iBall->move();

		CushionCollision(iBall);

		//�|�P�b�g�Ƀ{�[�������������`�F�b�N
		if (PocketInCheck(mBalls[i]) == true){
			//���{�[�����|�P�b�g�ɓ��������`�F�b�N
			//���{�[�����|�P�b�g�ɓ�������numShot���{�R
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

		//�{�[�����m�̏Փ˃`�F�b�N
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


//���{�[�����|�P�b�g�ɓ�������̔��{�[����u������
void OnePlayGame::PlayerSet(int x, int y){
	mPlayer->setT(Vector2d(x, y));
	mPlayer->setV(Vector2d(0, 0));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	mPlayer->display();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//PlayerExit�̎擾
bool OnePlayGame::GetPlayerExist(){
	return mPlayerExist;
}

//���{�[����u�������̏����B�N���b�N���ɌĂ΂��B
void OnePlayGame::PutPlayer(){
	if (CUSHION_LEFT < mPlayer->getX() - mPlayer->getSize() && mPlayer->getX() + mPlayer->getSize() < CUSHION_RIGHT      
		&& CUSHION_TOP < mPlayer->getY() - mPlayer->getSize() && mPlayer->getY() + mPlayer->getSize() < CUSHION_BOTTOM){
		for (std::vector<Ball*>::iterator ball = mBalls.begin(); ball != mBalls.end(); ball++){
			if ( ((*ball)->getT() - mPlayer->getT()).norm() < (*ball)->getSize() + mPlayer->getSize() )
				return;
		}
		mBalls.push_back(mPlayer);
		mPlayerExist = true;
	}
}

//�Ő����C���N�������g
void OnePlayGame::NumShotPlaPla(){
	mNumShot++;
}

Player* OnePlayGame::GetPlayer(){
	return mPlayer;
}

int OnePlayGame::GetNumColorBall(){
	return mNumColorBall;
}

void OnePlayGame::SetShotPower(float power){
	mShotPower = power;
}

float OnePlayGame::GetShotPower(){
	return mShotPower;
}

Scene* OnePlayGame::Update(){
	Display();

	//�V�[�P���X����
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