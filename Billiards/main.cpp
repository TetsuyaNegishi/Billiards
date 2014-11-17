#include "DxLib.h"
#include "Game.h"
#include "MainLoop.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	//Game game;
	//game.init();
	//game.main();
	//game.end();
	SetGraphMode(MainLoop::WINDOW_WIDTH, MainLoop::WINDOW_HEIGHT, 16);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	MainLoop mainLoop;
	mainLoop.Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		mainLoop.Update();
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}