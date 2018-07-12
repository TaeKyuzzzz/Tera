#include "stdafx.h"
#include "cGameObject.h"
#include "Spere\cSpere.h"
#include "BoundingBox\cBoundingBox.h"

cGameObject::cGameObject()
	: m_pSpere(NULL)
	, m_pBoundingBox(NULL)
	, SightBox(false)
	, SightSpere(false)
{
}


cGameObject::~cGameObject()
{
	SAFE_DELETE(m_pSpere);
	SAFE_DELETE(m_pBoundingBox);
}

void cGameObject::Setup()
{
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
	if(SightBox && m_pBoundingBox)
		m_pBoundingBox->Render();
	
	if(SightSpere && m_pSpere)
		m_pSpere->Render();
}
