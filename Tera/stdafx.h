// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include <cstring>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include <d3dx9.h>

#include <xnamath.h>
#include <fstream>
#include <conio.h>
#include <map>
#include <list>
//#include <timeapi.h>

#pragma comment(lib,"d3d9.lib")

#pragma comment(lib, "d3dx9.lib")

extern POINT ptMouse;
extern int Wheel;
extern D3DXVECTOR3* g_vPlayerPos;
extern HINSTANCE hInst;
extern HWND g_hWnd;
extern D3DXVECTOR3 g_vCamera;

//#define WINSIZEX 1920 // 1600
//#define WINSIZEY 1080 // 900

#define WINSIZEX 1600 // 1600
#define WINSIZEY 900 // 900

#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)	{ if (p) p->Release(); p = NULL; }


#define SINGLETONE(class_name)\
private:\
	class_name();\
	virtual~class_name();\
public:\
	static class_name * GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: varType Get##funName(void) { return varName; }\
public: void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_REF(varType, varName, funName)\
protected: varType varName;\
public: varType& Get##funName(void) { return varName; }\
public: void Set##funName(varType& var) { varName = var; }

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_TEX1
	};
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

struct ST_PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1
	};
};

// �����ϸ� �ּ� ������

struct ST_BONE : public D3DXFRAME
{
	// ������ -> �ڱ���ĸ� ����վ
	// �������� ���� ����� ���� ��Ʈ����
	D3DXMATRIX		CombinedTransformationMatrix;
};
// ���� ���� ��� + @ ( �� ����� �͵� ���� )

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	// ���� �޽ø� ������ ����
	// ����� ������ �޽ð� �ٲ�Ŷ� �׷�
	LPD3DXMESH		pOrigMesh;

	// �޽ÿ� ������ �ִ� ��� ������ ����
	D3DXMATRIX**	ppBoneMatrixPtrs;

	// ���� �޽ø� ���� ��Ʈ���� ���� ���� �����̽���
	// ������ ��Ʈ������ ���� ����
	D3DXMATRIX*		pBoneOffsetMatrices;

	// ���� ���� ���� ���� ��Ʈ������ ������
	// ������ ( ���� ���ÿ� ������ ������ ��Ʈ����?)
	D3DXMATRIX*		pCurrentBoneMatrices;

	vector<D3DMATERIAL9>		vecMtl;
	vector<LPDIRECT3DTEXTURE9>	vecTex;

	// �Ӽ� ����
	//DWORD			NumAttributeGroups;
	//D3DXATTRIBUTERANGE*			attributeTable;
};

// UI �� ���õ� ����ü

struct ST_UI_SIZE
{
	int nWidth;
	int nHeight;

	ST_UI_SIZE() : nWidth(0), nHeight(0) {}
	ST_UI_SIZE(int w, int h)
		: nWidth(w), nHeight(h) {}
};

struct ST_OBB // OBB����ü
{
	D3DXVECTOR3 vCenterPos; // ���� �߾��� ��ǥ
	D3DXVECTOR3 vAxisDir[3]; //���ڿ� ������ �� ���� ��������
	float  fAxisLen[3]; // ������ ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.
};

///////////////////////////////
//
// �޴��� Ŭ������
//
////////////////////////////////


#include "Manager/cDeviceManager.h"

#include "MacroFunction.h"

#include "Manager/cFontManager.h"
#include "Manager/cKeyManager.h"
#include "Manager/cSceneManager.h"
#include "Manager/cSoundManager.h"
#include "Manager/cTextureManager.h"
#include "Manager/cTimeManager.h"
#include "Manager/cObjectManager.h"
#include "Manager/cSkinnedMeshManager.h"
#include "Manager/cStaticMeshManager.h"
