#include "stdafx.h"
#include "cWeapon02.h"

#include "XMesh\cXLoader.h"
#include "XMesh\cXMesh.h"
#include "BoundingBox\cBoundingBox.h"

cWeapon02::cWeapon02()
{
}


cWeapon02::~cWeapon02()
{
	SAFE_DELETE(m_sName);
	SAFE_DELETE(m_pBody);
}

void cWeapon02::Setup()
{
	cXLoader loader;
	m_pBody = loader.xFimeLoad("XFile/Item/Weapon/TwoHandSword_03.X");
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

void cWeapon02::Update()
{
	cItemBase::Update();
}

void cWeapon02::Rendeer()
{
	cItemBase::Render();
}
