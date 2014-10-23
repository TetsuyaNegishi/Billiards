#include "DxLib.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	Game game;

	game.init(); 
	game.main();
	game.end();

	return 0;
}