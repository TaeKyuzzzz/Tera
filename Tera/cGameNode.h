#pragma once
class cGameNode
{
public:
	cGameNode();
	virtual~cGameNode();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

