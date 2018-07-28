#pragma once
class cSceneMapEdit;

class cBoundingBoxLoader
{
public:
	cBoundingBoxLoader();
	~cBoundingBoxLoader();

	cSceneMapEdit* m_pEditor;

	void Setup();
	void Update();
	void Render();
};

