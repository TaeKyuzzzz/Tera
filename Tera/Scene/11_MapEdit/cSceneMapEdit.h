#pragma once
#include "cGameNode.h"

class cBoundingObject;
class cSpere;
class cXMesh;

class cTestMap;

//== 작업 object
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

	//== 작업 Object
	cTown_House* m_pTown_House;

public:
	//
	SYNTHESIZE_REF(vector<cBoundingObject*>, m_vecBObject, BObject); //볼과 박스들이 들어있는것의 집합체.

	std::vector<ST_PC_VERTEX> m_pLine; //선택면을 그릴 vector

	D3DMATERIAL9	material;

	bool			m_bIsSelected;	// box들중 선택된 것이 있는지만 판단.

	UINT			m_iNum_BSet;	//BSet중에 선택된 Bounding Set번호.
	UINT			m_iNum_group;	//group중에 선택된  box번호
	UINT			m_iNum_Face;	// 6개의 면중 선택된 면을 가리키는 번호

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