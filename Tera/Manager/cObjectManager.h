#pragma once
#include "GameObject\cGameObject.h"

#define OBJECTMANAGER cObjectManager::GetInstance()

class cGameObject;
class cSpere;
class cBoundingBox;

class cObjectManager
{
private:
	SINGLETONE(cObjectManager);

private:

	SYNTHESIZE(cGameObject*, m_pPlayer, Player);

	vector<cGameObject*>		m_vecObject;
	vector<cGameObject*>		m_vecCharacter;
	vector<cGameObject*>		m_vecMonster;
public:

	void AddObject(cGameObject* obj);
	void AddCharaObject(cGameObject* obj);
	void AddMonsterObject(cGameObject* obj);

	bool IsCollision(cGameObject * obj1, cGameObject * obj2);
	bool IsCollision(cGameObject * obj1);

	bool GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos);
	bool GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos, CONDITION con, float percent);

	bool GiveDamagedMonster(cBoundingBox * box, float Damage);

	bool OBBCollision(ST_OBB * Box1, ST_OBB * Box2);

	void VecClear();
};
