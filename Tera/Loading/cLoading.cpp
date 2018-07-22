#include "stdafx.h"
//
#include "cLoading.h"
#include "../ProgressBar/cProgressBar.h"
#include "Sprite\cSprite.h"

HRESULT LoadItem::InitForTexture(const char * szFullPath)
{
	_kind = LOAD_KIND_TEXTURE;

	memset(&_textureResource, 0, sizeof(tagTextureResouce));
	_textureResource.szFullPath = szFullPath;
	return S_OK;
}

HRESULT LoadItem::InitForSkinnedMesh(const char * szFolderName,const  char * szFileName)
{
	_kind = LOAD_KIND_SKINNEDMESH;

//	char str[1024] = "asdasdasd";
//	char asd[1024];
//	strcpy(str, asd);

	memset(&_skinnedMeshResource, 0, sizeof(tagSkinnedMeshResouce));
	_skinnedMeshResource.szFolderName = szFolderName;
	_skinnedMeshResource.szFileName = szFileName;
	
	return S_OK;
}

HRESULT LoadItem::InitForStaticMesh(const char * szFileName)
{
	_kind = LOAD_KIND_STATICMESH;

	memset(&_staticMeshResource, 0, sizeof(tagStaticMeshResouce));
	_staticMeshResource.fileName = szFileName;

	return S_OK;
}

HRESULT LoadItem::IniteForSound(string KeyName, const char* fileName, bool bgm, bool Loop)
{
	_kind = LOAD_KIND_SOUND;

	memset(&_soundResource, 0, sizeof(tagSoundResouce));
	_soundResource.keyName = (string)KeyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = Loop;

	return S_OK;
}

HRESULT LoadItem::IniteForParticle(string key, const char * fileName)
{
	_kind = LOAD_KIND_PARTICLE;
	memset(&_particleResource, 0, sizeof(tagParticleResource));
	_particleResource.key = (string)key;
	_particleResource.fileName = fileName;
	return S_OK;
}

cLoading::cLoading()
	: m_pBackGround(NULL)
	, _loadingBar(NULL)
{
}

cLoading::~cLoading()
{
	SAFE_DELETE(m_pBackGround);
	SAFE_DELETE(_loadingBar);
}

void cLoading::Setup(const char * backTexture)
{
	//�ε�ȭ�� ��׶��� �ʱ�ȭ
	m_pBackGround = TEXTUREMANAGER->GetSprite(backTexture);

	//_loading = IMAGEMANAGER->AddImage("endLoading", "images/intro/console_loading.bmp", WINSIZEX / 2 - 96, 500, 192, 46, true, RGB(255, 0, 255));
	//_endLoading = IMAGEMANAGER->AddImage("loading", "images/intro/continue.bmp",
	//	WINSIZEX / 2 - 220, 500, 440, 36, true, RGB(255, 0, 255));



	//�ε��� �ʱ�ȭ
	_loadingBar = new cProgressBar;
	_loadingBar->Setup(
		"Texture/SceneTexture/LoadingBar.png",
		"Texture/SceneTexture/BGLoadingBar.png",
		WINSIZEX / 2 - WINSIZEX * 3.0f / 8.0f, WINSIZEY - 100, WINSIZEX * 3.0f / 4.0f, 28
	);
	//
	_loadingBar->SetGauge(0, 0);

	////�ε��� ������ �ʱ�ȭ
	_currentGauge = 0;
	
}

void  cLoading::Update()
{
	_loadingBar->Update();
}
void  cLoading::Render()
{
	m_pBackGround->Render(D3DXVECTOR3(m_pBackGround->textureInfo.Width / 2, 0, 0), 
		D3DXVECTOR3(WINSIZEX / 2, 0, 0));

	LoadingDone();
	_loadingBar->Render();
	// ���׶��� 
}


HRESULT cLoading::InitForTexture(const char * szFullPath)
{
	LoadItem * item = new LoadItem;
	item->InitForTexture(szFullPath);
	_vLoadItem.push_back(item);
	return S_OK;
}

HRESULT cLoading::InitForSkinnedMesh(const char * szFolderName, const  char * szFileName)
{
	LoadItem * item = new LoadItem;
	item->InitForSkinnedMesh(szFolderName, szFileName);
	_vLoadItem.push_back(item);
	return S_OK;
}

HRESULT cLoading::InitForStaticMesh(const char * szFileName)
{
	LoadItem * item = new LoadItem;
	item->InitForStaticMesh(szFileName);
	_vLoadItem.push_back(item);
	return S_OK;
}

HRESULT cLoading::IniteForParticle(string key, const char * fileName)
{
	LoadItem * item = new LoadItem;
	item->IniteForParticle(key, fileName);
	_vLoadItem.push_back(item);

	return S_OK;
}

HRESULT cLoading::InitForSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	LoadItem * item = new LoadItem;
	item->IniteForSound(keyName, fileName, bgm, loop);

	_vLoadItem.push_back(item);
	return S_OK;
}

// Ű������ ������ �̹��� ���� �ʱ�ȭ

//�ε��� �Ϸ� ���???????(�ε� �Ϸ��� �� ����)
BOOL  cLoading::LoadingDone()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	LoadItem * item = _vLoadItem[_currentGauge];
	
	tagImageResource img;
	tagTextureResouce texture;
	tagStaticMeshResouce staticMesh;
	tagSkinnedMeshResouce skinnedMesh;
	tagSoundResouce sound;
	tagParticleResource particle;

	switch (item->GetLoadingKind())
	{
	case LOAD_KIND_TEXTURE :
		texture = item->GetTextrueResource();
		TEXTUREMANAGER->AddTexture(texture.szFullPath);
		break;
	case LOAD_KIND_SOUND :
		sound = item->GetSoundResource();
		SOUNDMANAGER->AddSound(sound.keyName, sound.fileName, sound.bgm, sound.loop);
		break;
	case LOAD_KIND_SKINNEDMESH :
		skinnedMesh = item->GetSkinnedResource();
		SKINNEDMESHMANAGER->AddSkinnedMesh(skinnedMesh.szFolderName, skinnedMesh.szFileName);
		break;
	case LOAD_KIND_STATICMESH :
		staticMesh = item->GetStaticMeshResource();
		STATICMESHMANAGER->AddStaticMesh(staticMesh.fileName);
		break;
	case LOAD_KIND_PARTICLE :
		particle = item->GetParticleResource();
		PARTICLEMANAGER->AddParticle(particle.key, particle.fileName);
	}

	//// �ε��� �̹��� ����
	_loadingBar->SetGauge(_currentGauge, _vLoadItem.size());
	////ī��Ʈ
	_currentGauge++;

	return false;
}