#pragma once

#include"SceneOnePlayGameChild.h"

class Clear : public SceneOnePlayGameChild{
public:
	Clear(OnePlayGame* parent);
	virtual Scene* Update() override;
};