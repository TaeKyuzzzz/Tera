#pragma once
#include "cGameNode.h"
#include "Particle\cParticleSet.h"

#define BTNMAX 33
class cSprite;
class cGrid;

class cScenePaticleEdit : public cGameNode
{
private :
	cGrid*					m_pGrid;
	cSprite*					m_pSprite;

	LPDIRECT3DTEXTURE9			m_pTexture;

	char					m_sName[1024];

	cParticleSet*				m_pParticleSet;


	PARTICLE_TYPE			m_type;
	float					m_fTime;		// ��ƼŬ ����
	float					m_fSpeed;

	float					m_fAcc;			//4
	int						m_fAccMin;		//5
	int						m_fAccMax;		//6
											//
	float					m_fCurTime;		//
											//
	// �ʱ� ��ġ��							//
	int						m_fPositionX;	//7
	int						m_fRandPosXMin;	//8
	int						m_fRandPosXMax;	//9
											//
	int						m_fPositionY;	//10
	int						m_fRandPosYMin;	//11
	int						m_fRandPosYMax;	//12
											//
	int						m_fPositionZ;	//13
	int						m_fRandPosZMin;	//14
	int						m_fRandPosZMax;	//15
											//
	// ���� �� ( �����κ��� -1.0f ~ 1.0f )	 //
	int						m_fDirectionX;	//16
	int						m_fRandDirXMin;	//17
	int						m_fRandDirXMax;	//18
											//
	int						m_fDirectionY;	//19
	int						m_fRandDirYMin;	//20
	int						m_fRandDirYMax;	//21
											//
	int						m_fDirectionZ;	//22
	int						m_fRandDirZMin;	//23
	int						m_fRandDirZMax;	//24
											//
	char 					m_szFile[1024];	//25

	int						m_nAlpha;		//26
	int						m_nColorR;		//27
	int						m_nColorG;		//28
	int						m_nColorB;		//29
	///////////////////////////////////////

	// ui ���� �ؽ���

	int						x;
	int						y;				// ui ������
	
	cSprite*				m_pMainImamge;

	RECT					rc[BTNMAX];			// ��Ʈ��! 26����!

	POINT					beforeMouse;
	bool					isDrag;
public:
	cScenePaticleEdit();
	~cScenePaticleEdit();

	void Setup();
	void Release();
	void Update();
	void Render();


	void UISetup();
	void UIUpdate();
	void UIRender();

	void LoadTexture();
	void Play();
	void SaveParticle();
	void LoadParticle();
};

