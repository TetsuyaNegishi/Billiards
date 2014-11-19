#pragma once

#include"Scene.h"

class MainLoop : public Scene{
private:
	Scene* mChild;
public:
	void Initialize();
	virtual Scene* Update() override;
	static const int WINDOW_WIDTH;	//ウィンドウ幅
	static const int WINDOW_HEIGHT;	//ウィンドウ高さ
};