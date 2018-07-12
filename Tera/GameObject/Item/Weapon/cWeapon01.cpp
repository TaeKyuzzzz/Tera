#include "stdafx.h"
#include "cWeapon01.h"

#include "XMesh\cXLoader.h"
#include "XMesh\cXMesh.h"
#include "BoundingBox\cBoundingBox.h"


cWeapon01::cWeapon01()
{
}


cWeapon01::~cWeapon01()
{
	SAFE_DELETE(m_sName);
	SAFE_DELETE(m_pBody);
}

void cWeapon01::Setup()
{
	cXLoader loader;
	m_pBody = loader.xFimeLoad("XFile/Item/Weapon/TwoHandSword_02.X");
	//iceSword
	//TwoHand00_SM
	//TwoHandSword_02
	// TwoHandSword_03
	// TwoHandSword_04
	m_pBoundingBox = new cBoundingBox;
	m_pBoundingBox->Setup(
		D3DXVECTOR3(-5, -10, -5),
		D3DXVECTOR3(5, 50, 5));
}

void cWeapon01::Update()
{
	cItemBase::Update();
}

void cWeapon01::Rendeer()
{
	cItemBase::Render();
}
