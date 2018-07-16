#include "stdafx.h"
#include "cBoundingObject.h"
#include "Spere\cSpere.h"
#include "BoundingBox\cBoundingBox.h"


cBoundingObject::cBoundingObject()
	: m_pSpere(NULL)
	, m_pBoundingBox(NULL)
	, SightBox(true)
	, SightSpere(true)
{
}


cBoundingObject::~cBoundingObject()
{
	SAFE_DELETE(m_pSpere);
	SAFE_DELETE(m_pBoundingBox);

	for (auto b : m_vecBBoxGroup)
	{
		SAFE_DELETE(b);
	}
	delete this;
}

void cBoundingObject::Setup()
{
}

void cBoundingObject::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('['))
		SightBox = !SightBox;
	if (KEYMANAGER->IsOnceKeyDown(']'))
		SightSpere = !SightSpere;

	if (!m_vecBBoxGroup.empty()) // SightBox && m_vecBBoxGroup.size()
	{
		for (auto g : m_vecBBoxGroup)
		{
			g->Update();
		}
	}

	if (SightSpere && m_pSpere)
		m_pSpere->Update();
}

void cBoundingObject::Render()
{
	// 바운딩 박스 렌더
	if (SightBox && !m_vecBBoxGroup.empty()) 
	{
		for (auto g : m_vecBBoxGroup)
		{
			g->Render();
		}
	}

	if(SightSpere && m_pSpere)
		m_pSpere->Render();
}

void cBoundingObject::Destroy_g()
{
	if (!m_vecBBoxGroup.empty())
	{
		for (auto g : m_vecBBoxGroup)
		{
			SAFE_DELETE(g);
		}
		delete this;
	}
}
