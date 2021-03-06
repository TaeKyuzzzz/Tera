#pragma once

#include "cGameNode.h"
class cProgressBar;
class cSprite;

//로드 아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_TEXTURE,
	LOAD_KIND_SOUND,
	LOAD_KIND_SKINNEDMESH,
	LOAD_KIND_STATICMESH,
	LOAD_KIND_PARTICLE,
	LOAD_KIND_END
};
//이미지 리소스 구조체
struct tagImageResource
{
	const char* fileName;	//파일 이름
};
// 사운드 리소스 구조체
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

struct tagParticleResource
{
	const char * fileName;
	string		 key;
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
	tagParticleResource		_particleResource;

public:

	// 텍스쳐
	HRESULT InitForTexture(const char* szFullPath);
	// 스킨드 메시
	HRESULT InitForSkinnedMesh(const char* szFolderName,const  char* szFileName);
	// 스태틱 메시
	HRESULT InitForStaticMesh(const char * szFileName);

	// 키 값으로 사운드 파일 초기화
	HRESULT IniteForSound(string KeyName, const char* fileName, bool bgm = FALSE, bool Loop = false);

	// 파티클
	HRESULT IniteForParticle(string key, const char * fileName);

	//로딩 아이템 종류 가져오기
	LOAD_KIND GetLoadingKind() { return _kind; }
	//이미지 리소스 가져오기
	tagImageResource GetImageResource() { return _imageResource; }
	tagSoundResouce GetSoundResource() { return _soundResource; }
	
	tagTextureResouce GetTextrueResource() { return _textureResource; }
	tagStaticMeshResouce GetStaticMeshResource() { return _staticMeshResource; }
	tagSkinnedMeshResouce GetSkinnedResource() { return _skinnedMeshResource; }
	tagParticleResource GetParticleResource() { return _particleResource; }
};

class cLoading :public cGameNode
{
private:
	typedef vector<LoadItem*> arrLoadItem;
private:
	arrLoadItem _vLoadItem;
	
	//로딩화면에서 사용할 이미지 및 로딩바
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

	// 텍스쳐
	HRESULT InitForTexture(const char* szFullPath);
	// 스킨드 메시
	HRESULT InitForSkinnedMesh(const char* szFolderName, const char* szFileName);
	// 스태틱 메시
	HRESULT InitForStaticMesh(const char * szFileName);
	
	HRESULT IniteForParticle(string key, const char * fileName);
	// 사운드 파일
	HRESULT InitForSound(string keyName, const char* fileName, bool bgm = false, bool loop = false);
	//로딩이 완료 됬니???????(로딩 완료휴 씬 변경)
	BOOL LoadingDone();
	//로드 아이템 벡터 가져오기
	vector<LoadItem*> GetLoadItem() { return _vLoadItem; }
};

