#pragma once
#include "UI\cUIObject.h"
class cUIImageView : public cUIObject
{
protected:
	LPDIRECT3DTEXTURE9		m_pTexture;

public:
	cUIImageView();
	virtual~cUIImageView();

	virtual void SetTexture(const char * szFullPath);
	virtual void Render(LPD3DXSPRITE pPprite);
};

