#pragma once

#include "SceneMainLoopChild.h"

class Title : public SceneMainLoopChild{
private:
	const int handle;

public:
	Title();
	virtual Scene* Update() override;
};