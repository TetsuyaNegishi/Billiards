#pragma once

#include "SceneMainLoopChild.h"

class Title : public SceneMainLoopChild{
public:
	virtual Scene* Update() override;
};