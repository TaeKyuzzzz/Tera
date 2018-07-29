#pragma once
#include "GameObject\cGameObject.h"

#define OBJECTMANAGER cObjectManager::GetInstance()

class cGameObject;
class cSpere;
class cBoundingBox;
class cBoundingObject; //lsc

class cObjectManager
{
private:
	SINGLETONE(cObjectManager);

private:

	SYNTHESIZE(cGameObject*, m_pPlayer, Player);

	vector<cGameObject*>		m_vecObject;
	vector<cGameObject*>		m_vecCharacter;
	vector<cGameObject*>		m_vecMonster;

	vector<cBoundingObject*>	m_vecObjectB; //lsc
public:

	void AddObject(cGameObject* obj);
	void AddCharaObject(cGameObject* obj);
	void AddMonsterObject(cGameObject* obj);
	void AddObject(vector<cBoundingObject*> obj); //lsc

	bool IsCollision(cGameObject * obj1, cGameObject * obj2);
	bool IsCollision(cGameObject * obj1);
	bool IsCollision(cGameObject * obj1, cBoundingObject* obj2); //lsc

	bool GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos);
	bool GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos, CONDITION con, float percent);
	bool GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos, CONDITION con, float percent, DAMAGED_TYPE type);

	bool GiveDamagedMonster(cBoundingBox * box, float Damage);

	bool OBBCollision(ST_OBB * Box1, ST_OBB * Box2);

	void VecClear();

	void PickObject();
};
