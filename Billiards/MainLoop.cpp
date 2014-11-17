#include"MainLoop.h"
#include"Title.h"

const int MainLoop::WINDOW_WIDTH = 800;	//�E�B���h�E��
const int MainLoop::WINDOW_HEIGHT = 450;	//�E�B���h�E����

void MainLoop::Initialize(){
	mChild = new Title();
}

Scene* MainLoop::Update(){
	//�V�[�P���X����
	Scene* next = mChild->Update();
	if (next != mChild){
		delete mChild;
		mChild = next;
	}
	return this;
}