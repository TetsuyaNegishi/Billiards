#pragma once

#include"SceneOnePlayGameChild.h"
#include"OnePlayGame.h"

class Play : public SceneOnePlayGameChild{
private:
	bool mPrevMouseInput;
	void PutPlayer();
	void ShotPlayer();
	float mPowerUp;
	void CueShow(Vector2d playerT, Vector2d direction);

	const int mCueSE;

public:
	Play(OnePlayGame* parent);
	virtual Scene* Update() override;
	
};