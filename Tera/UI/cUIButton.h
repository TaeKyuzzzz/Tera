#pragma once
#include "cUIObject.h"

class iButtonDelegate
{
public :
//	virtual void OnClick(cUIButton* pSender) = 0;// 누가 호출을 하였는가?
};

class cUIButton : public cUIObject
{
protected :
	enum eButtonSate
	{
		BT_UP,
		BT_OVER,
		BT_DOWN,
		BT_STATE_COUNT
	};

	LPDIRECT3DTEXTURE9		m_arrTexture[BT_STATE_COUNT];
	eButtonSate				m_buttonState;

	iButtonDelegate * m_pDelegate;

public:
	cUIButton();
	virtual~cUIButton();

	virtual void SetTexture(const char * szUp,const char * szOver, const char * szDown );
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};

