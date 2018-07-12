#pragma once

#define SCENEMANAGER cSceneManager::GetInstance()

class cGameNode;

class cSceneManager
{
private:

	SINGLETONE(cSceneManager);

	typedef map<string, cGameNode*> mSceneList;
	typedef map<string, cGameNode*>::iterator miSceneList;

	static cGameNode* _currentScene;  //ÇöÀç ¾À
	mSceneList _mSceneList;		  //¾À¸ñ·Ï

public:

	void Setup();
	void Update();
	void Render();

	//¾À Ãß°¡
	cGameNode* AddScene(string sceneName, cGameNode* scene);
	//¾À º¯°æ
	HRESULT ChangeScene(string sceneName);

	void Destroy();
};

