#include "stdafx.h"
#include "cWeapon03.h"


#include "XMesh\cXLoader.h"
#include "XMesh\cXMesh.h"
#include "BoundingBox\cBoundingBox.h"

cWeapon03::cWeapon03()
{
}


cWeapon03::~cWeapon03()
{
	SAFE_DELETE(m_sName);
	SAFE_DELETE(m_pBody);
}

void cWeapon03::Setup()
{
	cXLoader loader;
	m_pBody = loader.xFimeLoad("XFile/Item/Weapon/TwoHandSword_04.X");
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

void cWeapon03::Update()
{
	cItemBase::Update();
}

void cWeapon03::Rendeer()
{
	cItemBase::Render();
}
