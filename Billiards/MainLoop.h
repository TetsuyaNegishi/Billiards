#pragma once

#include"Scene.h"

class MainLoop : public Scene{
private:
	Scene* mChild;
public:
	void Initialize();
	virtual Scene* Update() override;
	static const int WINDOW_WIDTH;	//�E�B���h�E��
	static const int WINDOW_HEIGHT;	//�E�B���h�E����
};