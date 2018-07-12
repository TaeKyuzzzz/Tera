#pragma once
#include "GameObject\Character\cCharacterClass03.h"
#include "GameObject\Character\cCharacter.h"

class cSkinnedMesh;

class cItemBase;
class cXMesh;

class cCharaPopori : public cCharacterClass03
{
private :
	
private:

	cSkinnedMesh*			m_pBody;	
	
	cSkinnedMesh*			m_pHair;
	cSkinnedMesh*			m_pHand;
	cSkinnedMesh*			m_pLeg;
	
	CHARA_STATE				m_currState;
	ST_BONE*				m_pWeaponHand;
	ST_BONE*				m_pDummyRoot;
	ST_BONE*				m_pHead;
	
	cItemBase*				m_pWeapon;

	int						m_nWeaponNum = 0;
	int						m_nBodyNum = 0;
	int						m_nHandNum = 0;
	int						m_nLegNum = 0;

public:
	cCharaPopori();
	~cCharaPopori();

	void Setup();
	void Update();
	void Render();

	bool isUseLocalAnim();


	void ChangeWeapon(); // 인벤, 장비 이전 예비 함수
	void ChangeBody();
	void ChangeHand();
	void ChangeLeg();
};

/*
char szTemp[1024];
sprintf_s(szTemp, sizeof(szTemp),"%f %f %d", m_pDummyRoot->TransformationMatrix._41
,D3DXVec3Length(&m_vPosition), m_state);
RECT rc;
SetRect(&rc, 100, 100, 200, 100);
wchar_t wtext[1024];
HDC hdc = GetDC(g_hWnd);

TextOutA(hdc, 100, 100, szTemp, strlen(szTemp));
*/