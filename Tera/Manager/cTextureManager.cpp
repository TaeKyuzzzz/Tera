#include "stdafx.h"
#include "cTextureManager.h"
#include "Sprite\cSprite.h"

cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const char * szFullPath)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		wchar_t wtext[1024];
		size_t outSize;
		mbstowcs_s(&outSize, wtext, strlen(szFullPath) + 1, szFullPath, strlen(szFullPath));
		
		//D3DXCreateTextureFromFile(g_pD3DDevice, wtext, &m_mapTexture[szFullPath]);
		
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			wtext,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[szFullPath],
			0,
			&m_mapTexture[szFullPath]);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const char * szFullPath, D3DXIMAGE_INFO * pImageInfo)
{

	if (m_mapTexture.find(szFullPath) == m_mapTexture.end() ||
		m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		wchar_t wtext[1024];
		size_t outSize;
		mbstowcs_s(&outSize, wtext, strlen(szFullPath) + 1, szFullPath, strlen(szFullPath));

		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			wtext,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[szFullPath],
			0,
			&m_mapTexture[szFullPath]);
	}

	*pImageInfo = m_mapImageInfo[szFullPath];

	return m_mapTexture[szFullPath];
}

cSprite * cTextureManager::GetSprite(const char * szFullPath)
{
	cSprite * sprite = new cSprite;

	if (m_mapTexture.find(szFullPath) == m_mapTexture.end() ||
		m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		wchar_t wtext[1024];
		size_t outSize;
		mbstowcs_s(&outSize, wtext, strlen(szFullPath) + 1, szFullPath, strlen(szFullPath));

		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			wtext,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[szFullPath],
			0,
			&m_mapTexture[szFullPath]);
	}

	sprite->texture = m_mapTexture[szFullPath];
	sprite->textureInfo = m_mapImageInfo[szFullPath];

	return sprite;
}

void cTextureManager::AddTexture(const char * szFullPath)
{
	wchar_t wtext[1024];
	size_t outSize;
	mbstowcs_s(&outSize, wtext, strlen(szFullPath) + 1, szFullPath, strlen(szFullPath));

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		wtext,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_mapImageInfo[szFullPath],
		0,
		&m_mapTexture[szFullPath]);
}

void cTextureManager::Destroy()
{
	for (auto p : m_mapTexture)
	{
		if(p.second)
			SAFE_RELEASE(p.second);
	}
	m_mapTexture.clear();
}
