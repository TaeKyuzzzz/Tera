#pragma once

#define OBJECTMANAGER cObjectManager::GetInstance()

class cGameObject;
class cSpere;

class cObjectManager
{
private :
	SINGLETONE(cObjectManager);

private :

	vector<cGameObject*>		m_vecObject;
	vector<cGameObject*>		m_vecCharacter;
	vector<cGameObject*>		m_vecMonster;
public :

	void AddObject(cGameObject* obj);
	void AddCharaObject(cGameObject* obj);
	bool IsCollision(cGameObject * obj1, cGameObject * obj2);
	bool IsCollision(cGameObject * obj1);

	bool GiveDamagedChara(cSpere * spere, float Damage);

	bool OBBCollision(ST_OBB * Box1, ST_OBB * Box2);
};

