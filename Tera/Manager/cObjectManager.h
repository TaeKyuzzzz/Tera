#pragma once

#define OBJECTMANAGER cObjectManager::GetInstance()

class cGameObject;

class cObjectManager
{
private :
	SINGLETONE(cObjectManager);

private :

	vector<cGameObject*>		m_vecObject;

public :

	void AddObject(cGameObject* obj);

	bool IsCollision(cGameObject * obj1, cGameObject * obj2);
	bool IsCollision(cGameObject * obj1);

	bool OBBCollision(ST_OBB * Box1, ST_OBB * Box2);
};

