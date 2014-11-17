#pragma once

class Scene{
public:
	virtual ~Scene(){}
	virtual void Initialize(){}
	virtual void Finalize(){}
	virtual Scene* Update() = 0;
};