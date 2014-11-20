#pragma once

#include"SceneOnePlayGameChild.h"

class Menu : public SceneOnePlayGameChild{
private:
	const int mFontHandle;
public:
	Menu(OnePlayGame* parent);
	virtual Scene* Update() override;
};