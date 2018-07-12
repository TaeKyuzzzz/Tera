#pragma once

#define TEXTUREMANAGER cTextureManager::GetInstance()

class cSprite;

class cTextureManager
{
private:
	SINGLETONE(cTextureManager);
	map<string, LPDIRECT3DTEXTURE9>	m_mapTexture;
	map<string, D3DXIMAGE_INFO>		m_mapImageInfo;



public:
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFullPath, D3DXIMAGE_INFO* pImageInfo);
	cSprite * GetSprite(const char* szFullPath);
	
	void AddTexture(const char * szFullPath);

	void Destroy();
};

