#pragma once

#include "cGameNode.h"
class cProgressBar;
class cSprite;

//�ε� ������ ����
enum LOAD_KIND
{
	LOAD_KIND_TEXTURE,
	LOAD_KIND_SOUND,
	LOAD_KIND_SKINNEDMESH,
	LOAD_KIND_STATICMESH,
	LOAD_KIND_END
};
//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	const char* fileName;	//���� �̸�
};
// ���� ���ҽ� ����ü
struct tagSoundResouce
{
	string keyName;
	const char* fileName;
	bool bgm;
	bool loop;
};

struct tagTextureResouce
{
	const char *  szFullPath;
};
struct tagSkinnedMeshResouce
{
	const char *  szFolderName;
	const char *  szFileName;
};

struct tagStaticMeshResouce
{
	const char * fileName;
};

class LoadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource		_imageResource;
	tagTextureResouce		_textureResource;
	tagSoundResouce			_soundResource;
	tagStaticMeshResouce	_staticMeshResource;
	tagSkinnedMeshResouce	_skinnedMeshResource;

public:

	// �ؽ���
	HRESULT InitForTexture(const char* szFullPath);
	// ��Ų�� �޽�
	HRESULT InitForSkinnedMesh(const char* szFolderName,const  char* szFileName);
	// ����ƽ �޽�
	HRESULT InitForStaticMesh(const char * szFileName);

	// Ű ������ ���� ���� �ʱ�ȭ
	HRESULT IniteForSound(string KeyName, const char* fileName, bool bgm = FALSE, bool Loop = false);

	//�ε� ������ ���� ��������
	LOAD_KIND GetLoadingKind() { return _kind; }
	//�̹��� ���ҽ� ��������
	tagImageResource GetImageResource() { return _imageResource; }
	tagSoundResouce GetSoundResource() { return _soundResource; }
	
	tagTextureResouce GetTextrueResource() { return _textureResource; }
	tagStaticMeshResouce GetStaticMeshResource() { return _staticMeshResource; }
	tagSkinnedMeshResouce GetSkinnedResource() { return _skinnedMeshResource; }

};

class cLoading :public cGameNode
{
private:
	typedef vector<LoadItem*> arrLoadItem;
private:
	arrLoadItem _vLoadItem;
	
	//�ε�ȭ�鿡�� ����� �̹��� �� �ε���
	cSprite*					m_pBackGround;
	//cSprite*					_loading;
	//cSprite*					_endLoading;
	cProgressBar*				_loadingBar;
	int							_currentGauge;

public:
	cLoading();
	~cLoading();

	void Setup(const char * backTexture);
	void Update();
	void Render();

	// �ؽ���
	HRESULT InitForTexture(const char* szFullPath);
	// ��Ų�� �޽�
	HRESULT InitForSkinnedMesh(const char* szFolderName, const char* szFileName);
	// ����ƽ �޽�
	HRESULT InitForStaticMesh(const char * szFileName);
	
	// ���� ����
	HRESULT InitForSound(string keyName, const char* fileName, bool bgm = false, bool loop = false);
	//�ε��� �Ϸ� ���???????(�ε� �Ϸ��� �� ����)
	BOOL LoadingDone();
	//�ε� ������ ���� ��������
	vector<LoadItem*> GetLoadItem() { return _vLoadItem; }
};

