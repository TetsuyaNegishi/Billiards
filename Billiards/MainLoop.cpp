#include"MainLoop.h"
#include"Title.h"

const int MainLoop::WINDOW_WIDTH = 800;	//ウィンドウ幅
const int MainLoop::WINDOW_HEIGHT = 450;	//ウィンドウ高さ

void MainLoop::Initialize(){
	mChild = new Title();
}

Scene* MainLoop::Update(){
	//シーケンス処理
	Scene* next = mChild->Update();
	if (next != mChild){
		delete mChild;
		mChild = next;
	}
	return this;
}