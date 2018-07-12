// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

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

// 이해하면 주석 지워라

struct ST_BONE : public D3DXFRAME
{
	// 프레임 -> 자기행렬만 들고잇어서
	// 누적으로 계산된 행렬을 넣을 매트릭스
	D3DXMATRIX		CombinedTransformationMatrix;
};
// 기존 것을 상속 + @ ( 더 사용할 것들 정의 )

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	// 원본 메시를 저장할 공간
	// 계산할 때마다 메시가 바뀔거라 그럼
	LPD3DXMESH		pOrigMesh;

	// 메시에 영향을 주는 모든 본들의 정보
	D3DXMATRIX**	ppBoneMatrixPtrs;

	// 원본 메시를 월드 메트릭스 말고 로컬 스페이스로
	// 보내는 메트릭스를 넣을 공간
	D3DXMATRIX*		pBoneOffsetMatrices;

	// 현재 본에 계산된 원본 매트릭스를 저장할
	// 포인터 ( 본인 로컬에 곱해줄 누적된 메트릭스?)
	D3DXMATRIX*		pCurrentBoneMatrices;

	vector<D3DMATERIAL9>		vecMtl;
	vector<LPDIRECT3DTEXTURE9>	vecTex;

	// 속성 개수
	//DWORD			NumAttributeGroups;
	//D3DXATTRIBUTERANGE*			attributeTable;
};

// UI 와 관련된 구조체

struct ST_UI_SIZE
{
	int nWidth;
	int nHeight;

	ST_UI_SIZE() : nWidth(0), nHeight(0) {}
	ST_UI_SIZE(int w, int h) 
		: nWidth(w), nHeight(h) {}
};

struct ST_OBB // OBB구조체
{
	D3DXVECTOR3 vCenterPos; // 상자 중앙의 좌표
	D3DXVECTOR3 vAxisDir[3]; //상자에 평행한 세 축의 단위벡터
	float  fAxisLen[3]; // 상자의 평행한 세 축의 길이 fAxisLen[n]은 vAxisDir[n]에 각각 대응한다.
};

///////////////////////////////
//
// 메니져 클래스들
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
