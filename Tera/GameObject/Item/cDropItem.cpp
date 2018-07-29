#include "stdafx.h"
#include "cDropItem.h"

#include "GameObject\cGameObject.h"
#include "Sprite\cSprite.h"
#include "iMap.h"
#include "GameObject\Item\cItem.h"
#include "Particle\cParticleSet.h"
#include "GameObject\Item/cItemInfo.h"

#include "Spere\cSpere.h"


cDropItem::cDropItem()
{
}


cDropItem::~cDropItem()
{
}

void cDropItem::Setup(const char * name, D3DXVECTOR3 pos)
{
	m_sName = name;
	m_vPosition = pos;

	// 备 面倒 康开 积己
	m_pSpere = new cSpere;
	m_pSpere->Setup(D3DXVECTOR3(0, 0, 0), 20);
}

void cDropItem::Update()
{
	PlusMapHeight(); // 臭捞甘 利侩

}

void cDropItem::Render()
{
}

void cDropItem::PlusMapHeight()
{
	if (m_pMap)
		m_pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void cDropItem::SetItemInfo(const char * name)
{
}
