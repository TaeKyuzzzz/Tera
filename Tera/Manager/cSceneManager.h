#pragma once

#define SCENEMANAGER cSceneManager::GetInstance()

class cGameNode;

class cSceneManager
{
private:

	SINGLETONE(cSceneManager);

	typedef map<string, cGameNode*> mSceneList;
	typedef map<string, cGameNode*>::iterator miSceneList;

	static cGameNode* _currentScene;  //���� ��
	mSceneList _mSceneList;		  //�����

public:

	void Setup();
	void Update();
	void Render();

	//�� �߰�
	cGameNode* AddScene(string sceneName, cGameNode* scene);
	//�� ����
	HRESULT ChangeScene(string sceneName);

	void Destroy();
};

