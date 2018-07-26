#include "stdafx.h"
#include "cGameObject.h"
#include "Spere\cSpere.h"
#include "BoundingBox\cBoundingBox.h"

cGameObject::cGameObject()
	: m_pSpere(NULL)
	, m_pBoundingBox(NULL)
	, SightBox(false)
	, SightSpere(false)
	, m_isPossibleDamaged(true)
{
}


cGameObject::~cGameObject()
{
	SAFE_DELETE(m_pSpere);
	SAFE_DELETE(m_pBoundingBox);
}

void cGameObject::Setup()
{
	m_eCondition = CDT_NORMAL;
}

void cGameObject::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('F'))
		SightBox = !SightBox;
	if (KEYMANAGER->IsOnceKeyDown('G'))
		SightSpere = !SightSpere;
}

void cGameObject::Render()
{
	// 바운딩 박스 렌더
	if (SightBox && m_pBoundingBox)
		m_pBoundingBox->Render();

	if (SightSpere && m_pSpere)
		m_pSpere->Render();
}

void cGameObject::Damaged(float damage, D3DXVECTOR3 pos)
{
}

void cGameObject::Damaged(float damage, D3DXVECTOR3 pos, CONDITION con, float per)
{

}

void cGameObject::CountPossibleDamaged(float time)
{
	m_PossbleDamagedTime += TIMEMANAGER->GetEllapsedTime();
	if (m_PossbleDamagedTime >= time)
	{
		m_isPossibleDamaged = true;
		m_PossbleDamagedTime = 0.0f;
	}
}
