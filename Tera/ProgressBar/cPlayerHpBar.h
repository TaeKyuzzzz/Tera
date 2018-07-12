#pragma once

class cSprite;

class cPlayerHpBar
{
private :

	RECT			m_rcHpCur;
	RECT			m_rcHpBack;
	RECT			m_rcMpCur;
	RECT			m_rcMpBack;

	cSprite*		m_pHpCur;
	cSprite*		m_pHpBack;
	cSprite*		m_pMpCur;
	cSprite*		m_pMpBack;


public:
	cPlayerHpBar();
	~cPlayerHpBar();

	void Setup();

	void Update();
	void Render();

	void SetGauge(float currentGauge, float maxGauge);
};

