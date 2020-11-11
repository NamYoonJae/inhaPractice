#include "stdafx.h"
#include "TextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullpath)
{
	if (m_mapTexture.find(szFullpath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(g_pD3DDevice, szFullpath, &m_mapTexture[szFullpath]);
	}
	return m_mapTexture[szFullpath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string & sFullpath)
{
	return GetTexture((char*)sFullpath.c_str());
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SafeRelease(it.second);
	}
	m_mapTexture.clear();
}

