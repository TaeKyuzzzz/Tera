#pragma once
#include "../cGameObject.h"

class cSprite;
class iMap;
class cItemInfo;

class cDropItem : public cGameObject
{

private :

	const char *	m_sName;

	D3DXMATRIX		m_matWorld;
	D3DXVECTOR3		m_vPosition;

	SYNTHESIZE(iMap*, m_pMap, Map);

	float			m_fRotY;
	float			m_fOverLand;


	cSprite*		m_pBodySprite;

	tagItemInfo		m_stItemInfo;

public:
	cDropItem();
	~cDropItem();

	void Setup(const char * name, D3DXVECTOR3 pos);
	void Update();
	void Render();
	
	void PlusMapHeight();


	void SetItemInfo(const char * name);
};

