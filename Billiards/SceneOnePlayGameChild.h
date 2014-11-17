#pragma once

#include"Scene.h"
#include"OnePlayGame.h"

class SceneOnePlayGameChild : public Scene{
public:
	OnePlayGame* mParent;
};