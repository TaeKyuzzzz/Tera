#include "stdafx.h"
#include "cObjectManager.h"

#include "GameObject\cGameObject.h"
#include "Spere\cSpere.h"
#include "BoundingBox\cBoundingBox.h"
#include "GameObject\Character\cCharacter.h"

#include "Scene/11_MapEdit/cBoundingObject.h"

cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::AddObject(cGameObject * obj)
{
	m_vecObject.push_back(obj);
}

void cObjectManager::AddCharaObject(cGameObject * obj)
{
	m_vecCharacter.push_back(obj);
}

void cObjectManager::AddObject(vector<cBoundingObject*> obj)
{
	m_vecObjectB = obj;
}

void cObjectManager::AddMonsterObject(cGameObject * obj)
{
	m_vecMonster.push_back(obj);
}

bool cObjectManager::IsCollision(cGameObject * obj1, cGameObject * obj2)
{
	// 구 충돌 여부 부터

	float lengh = D3DXVec3Length(&(obj1->GetSpere()->GetPosition() - obj2->GetSpere()->GetPosition()));
	float distance = obj1->GetSpere()->GetRadius() + obj2->GetSpere()->GetRadius();

	if (lengh >= distance) return false;

	// OBB 충돌 체크을 해야한 합니다.

	return OBBCollision(&obj1->GetBoundingBox()->GetOBB(),
		&obj2->GetBoundingBox()->GetOBB());
}

bool cObjectManager::IsCollision(cGameObject * obj1)
{
	bool result = false;

	for (int i = 0; i < m_vecObject.size(); i++)
	{
		result = IsCollision(obj1, m_vecObject[i]);

		if (result)
			return result;
	}

	return false;
}

bool cObjectManager::IsCollision(cGameObject * obj1, cBoundingObject* obj2)
{
	// 구 충돌 여부 부터
	float lengh = D3DXVec3Length(&(obj1->GetSpere()->GetPosition() - obj2->GetSpere()->GetPosition()));
	float distance = obj1->GetSpere()->GetRadius() + obj2->GetSpere()->GetRadius();

	if (lengh >= distance) return false;

	// OBB 충돌 체크을 해야한 합니다.

	for (UINT g = 0; g < obj2->GetvecBBoxGroup().size(); g++)
	{
		if (OBBCollision(&obj1->GetBoundingBox()->GetOBB(),
			&obj2->GetvecBBoxGroup()[g]->GetOBB()))
		{
			if (g == obj2->GetvecBBoxGroup().size() - 1) return true;
		}
	}
	return false;
}

bool cObjectManager::GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos)
{
	for (int i = 0; i < m_vecCharacter.size(); i++)
	{

		cGameObject * obj1 = m_vecCharacter[i];

		float lengh = D3DXVec3Length(&(obj1->GetSpere()->GetPosition() - spere->GetPosition()));
		float distance = obj1->GetSpere()->GetRadius() + spere->GetRadius();

		if (lengh < distance)
		{
			obj1->Damaged(Damage, pos);
			return true;
		}
	}
	return false;
}

bool cObjectManager::GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos, CONDITION con, float percent)
{
	for (int i = 0; i < m_vecCharacter.size(); i++)
	{

		cGameObject * obj1 = m_vecCharacter[i];
		D3DXVECTOR3 vec1, vec2;
		vec1 = obj1->GetSpere()->GetPosition();
		vec1.y = 0;
		vec2 = spere->GetPosition();
		vec2.y = 0;
		float lengh = D3DXVec3Length(&(vec1 - vec2));
		float distance = obj1->GetSpere()->GetRadius() + spere->GetRadius();

		if (lengh < distance)
		{
			obj1->Damaged(Damage, pos, con, percent);

			return true;
		}
	}
	return false;
}

bool cObjectManager::GiveDamagedChara(cSpere * spere, float Damage, D3DXVECTOR3 pos, CONDITION con, float percent, DAMAGED_TYPE type)
{
	for (int i = 0; i < m_vecCharacter.size(); i++)
	{
		cGameObject * obj1 = m_vecCharacter[i];
		D3DXVECTOR3 vec1, vec2;
		vec1 = obj1->GetSpere()->GetPosition();
		vec1.y = 0;
		vec2 = spere->GetPosition();
		vec2.y = 0;
		float lengh = D3DXVec3Length(&(vec1 - vec2));
		float distance = obj1->GetSpere()->GetRadius() + spere->GetRadius();

		if (lengh < distance)
		{
			obj1->Damaged(Damage, pos, con, percent, type);

			return true;
		}
	}
	return false;
}

bool cObjectManager::GiveDamagedMonster(cBoundingBox * box, float Damage)
{
	for (int i = 0; i < m_vecMonster.size(); i++)
	{

		cGameObject * obj1 = m_vecMonster[i];

		if (OBBCollision(&(obj1->GetBoundingBox()->GetOBB()), &(box->GetOBB())))
		{
			//몬스터에서는 넉백을 고려안했으므로 그냥 일단 벡터값 아무거나 줬엉.
			obj1->Damaged(Damage, D3DXVECTOR3(0, 0, 0));
			return true;
		}
	}
	return false;
}

bool cObjectManager::OBBCollision(ST_OBB * Box1, ST_OBB * Box2)
{
	double c[3][3];
	double absC[3][3];
	double d[3];

	double r0, r1, r;
	int i;

	const double cutoff = 0.999999;
	bool existsParallelPair = false;

	D3DXVECTOR3 diff = Box1->vCenterPos - Box2->vCenterPos;

	for (i = 0; i < 3; ++i)
	{
		c[0][i] = D3DXVec3Dot(&Box1->vAxisDir[0], &Box2->vAxisDir[i]);
		absC[0][i] = abs(c[0][i]);
		if (absC[0][i] > cutoff)
			existsParallelPair = true;
	}
	d[0] = D3DXVec3Dot(&diff, &Box1->vAxisDir[0]);
	r = abs(d[0]);
	r0 = Box1->fAxisLen[0];
	r1 = Box2->fAxisLen[0] * absC[0][0] + Box2->fAxisLen[1] * absC[0][1] + Box2->fAxisLen[2] * absC[0][2];

	if (r > r0 + r1)
		return FALSE;

	for (i = 0; i < 3; ++i)
	{
		c[1][i] = D3DXVec3Dot(&Box1->vAxisDir[1], &Box2->vAxisDir[i]);
		absC[1][i] = abs(c[1][i]);
		if (absC[1][i] > cutoff)
			existsParallelPair = true;
	}
	d[1] = D3DXVec3Dot(&diff, &Box1->vAxisDir[1]);
	r = abs(d[1]);
	r0 = Box1->fAxisLen[1];
	r1 = Box2->fAxisLen[0] * absC[1][0] + Box2->fAxisLen[1] * absC[1][1] + Box2->fAxisLen[2] * absC[1][2];

	if (r > r0 + r1)
		return FALSE;

	for (i = 0; i < 3; ++i)
	{
		c[2][i] = D3DXVec3Dot(&Box1->vAxisDir[2], &Box2->vAxisDir[i]);
		absC[2][i] = abs(c[2][i]);
		if (absC[2][i] > cutoff)
			existsParallelPair = true;
	}
	d[2] = D3DXVec3Dot(&diff, &Box1->vAxisDir[2]);
	r = abs(d[2]);
	r0 = Box1->fAxisLen[2];
	r1 = Box2->fAxisLen[0] * absC[2][0] + Box2->fAxisLen[1] * absC[2][1] + Box2->fAxisLen[2] * absC[2][2];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &Box2->vAxisDir[0]));
	r0 = Box1->fAxisLen[0] * absC[0][0] + Box1->fAxisLen[1] * absC[1][0] + Box1->fAxisLen[2] * absC[2][0];
	r1 = Box2->fAxisLen[0];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &Box2->vAxisDir[1]));
	r0 = Box1->fAxisLen[0] * absC[0][1] + Box1->fAxisLen[1] * absC[1][1] + Box1->fAxisLen[2] * absC[2][1];
	r1 = Box2->fAxisLen[1];

	if (r > r0 + r1)
		return FALSE;

	r = abs(D3DXVec3Dot(&diff, &Box2->vAxisDir[2]));
	r0 = Box1->fAxisLen[0] * absC[0][2] + Box1->fAxisLen[1] * absC[1][2] + Box1->fAxisLen[2] * absC[2][2];
	r1 = Box2->fAxisLen[2];

	if (r > r0 + r1)
		return FALSE;

	if (existsParallelPair == true)
		return TRUE;

	r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
	r0 = Box1->fAxisLen[1] * absC[2][0] + Box1->fAxisLen[2] * absC[1][0];
	r1 = Box2->fAxisLen[1] * absC[0][2] + Box2->fAxisLen[2] * absC[0][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
	r0 = Box1->fAxisLen[1] * absC[2][1] + Box1->fAxisLen[2] * absC[1][1];
	r1 = Box2->fAxisLen[0] * absC[0][2] + Box2->fAxisLen[2] * absC[0][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
	r0 = Box1->fAxisLen[1] * absC[2][2] + Box1->fAxisLen[2] * absC[1][2];
	r1 = Box2->fAxisLen[0] * absC[0][1] + Box2->fAxisLen[1] * absC[0][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
	r0 = Box1->fAxisLen[0] * absC[2][0] + Box1->fAxisLen[2] * absC[0][0];
	r1 = Box2->fAxisLen[1] * absC[1][2] + Box2->fAxisLen[2] * absC[1][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
	r0 = Box1->fAxisLen[0] * absC[2][1] + Box1->fAxisLen[2] * absC[0][1];
	r1 = Box2->fAxisLen[0] * absC[1][2] + Box2->fAxisLen[2] * absC[1][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
	r0 = Box1->fAxisLen[0] * absC[2][2] + Box1->fAxisLen[2] * absC[0][2];
	r1 = Box2->fAxisLen[0] * absC[1][1] + Box2->fAxisLen[1] * absC[1][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][0] - d[0] * c[1][0]);
	r0 = Box1->fAxisLen[0] * absC[1][0] + Box1->fAxisLen[1] * absC[0][0];
	r1 = Box2->fAxisLen[1] * absC[2][2] + Box2->fAxisLen[2] * absC[2][1];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][1] - d[0] * c[1][1]);
	r0 = Box1->fAxisLen[0] * absC[1][1] + Box1->fAxisLen[1] * absC[0][1];
	r1 = Box2->fAxisLen[0] * absC[2][2] + Box2->fAxisLen[2] * absC[2][0];
	if (r > r0 + r1)
		return FALSE;

	r = abs(d[1] * c[0][2] - d[0] * c[1][2]);
	r0 = Box1->fAxisLen[0] * absC[1][2] + Box1->fAxisLen[1] * absC[0][2];
	r1 = Box2->fAxisLen[0] * absC[2][1] + Box2->fAxisLen[1] * absC[2][0];
	if (r > r0 + r1)
		return FALSE;

	return TRUE;
}

void cObjectManager::VecClear()
{
	m_vecObject.clear();
	m_vecCharacter.clear();
	m_vecMonster.clear();
}
