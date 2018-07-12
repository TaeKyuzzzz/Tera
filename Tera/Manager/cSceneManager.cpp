#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameNode.h"

cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
	miSceneList iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//삭제
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene)
				SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();
}

cGameNode* cSceneManager::_currentScene = NULL;

void cSceneManager::Setup()
{
}

//void cSceneManager::Release()
//{
//	miSceneList iter = _mSceneList.begin();
//	for (iter; iter != _mSceneList.end();)
//	{
//		//삭제
//		if (iter->second != NULL)
//		{
//			if (iter->second == _currentScene)
//				delete iter->second;
//			SAFE_DELETE(iter->second);
//			iter = _mSceneList.erase(iter);
//		}
//		else
//		{
//			++iter;
//		}
//	}
//	_mSceneList.clear();
//
//	delete this;
//}

void cSceneManager::Update()
{
	if (_currentScene) _currentScene->Update();
}

void cSceneManager::Render()
{
	if (_currentScene) _currentScene->Render();
}

cGameNode * cSceneManager::AddScene(string sceneName, cGameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

HRESULT cSceneManager::ChangeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);
	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return E_FAIL;

	find->second->Setup();

	// 원래 이부분은 위의 find->second->Setup(); 이 성공해야 실행되는 곳
	if (_currentScene) delete(_currentScene);
	_currentScene = find->second;
	return S_OK;

	return E_FAIL;
}

void cSceneManager::Destroy()
{
	miSceneList iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//삭제
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene)
				delete iter->second;
			//SAFE_RELEASE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();

	//delete this;
}
