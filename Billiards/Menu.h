#pragma once

#include"SceneOnePlayGameChild.h"

class Menu : public SceneOnePlayGameChild{
public:
	Menu(OnePlayGame* parent);
	virtual Scene* Update() override;
};