#pragma once

#include"SceneOnePlayGameChild.h"
#include"OnePlayGame.h"

class Play : public SceneOnePlayGameChild{
private:
	bool mPrevMouseInput;
	void PutPlayer();
	void ShotPlayer();

public:
	Play(OnePlayGame* parent);
	virtual Scene* Update() override;
};