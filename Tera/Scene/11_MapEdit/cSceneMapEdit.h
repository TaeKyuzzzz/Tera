#pragma once
#include "cGameNode.h"

class cBoundingObject;
class cSpere;
class cXMesh;

class cTestMap;

//== �۾� object
class cTown_House;

class cSceneMapEdit : public cGameNode
{
private:
	SYNTHESIZE(D3DXMATRIX, m_matWorld, World);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

	cBoundingObject* m_pGameObject;
	cSpere* m_pSphere;

	//
	cTestMap*	m_pMap;
	string m_sFileName;

	//== �۾� Object
	cTown_House* m_pTown_House;

public:
	//
	SYNTHESIZE_REF(vector<cBoundingObject*>, m_vecBObject, BObject); //���� �ڽ����� ����ִ°��� ����ü.

	std::vector<ST_PC_VERTEX> m_pLine; //���ø��� �׸� vector

	D3DMATERIAL9	material;

	bool			m_bIsSelected;	// box���� ���õ� ���� �ִ����� �Ǵ�.

	UINT			m_iNum_BSet;	//BSet�߿� ���õ� Bounding Set��ȣ.
	UINT			m_iNum_group;	//group�߿� ���õ�  box��ȣ
	UINT			m_iNum_Face;	// 6���� ���� ���õ� ���� ����Ű�� ��ȣ

	bool m_bRenderMode_Object; //true: solid , false: wireframe

	D3DXVECTOR3 m_vPosToCamera;

public:
	cSceneMapEdit();
	virtual ~cSceneMapEdit();

	void Setup();
	void Update();
	void Render();

	void FaceControl();
	void KeyMoveWASDRF();
	void RaytoCube();

	void CreateBox(D3DXVECTOR3 pos);
	void ResizeSphere();
	void Destroy();

	void ObjectSave(string fileName);
	void ObjectLoad();
	void FG_Sight();
};