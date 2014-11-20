#pragma once

#include"SceneOnePlayGameChild.h"

class Clear : public SceneOnePlayGameChild{
private:
	const int mFontHandle;
public:
	Clear(OnePlayGame* parent);
	virtual Scene* Update() override;
};