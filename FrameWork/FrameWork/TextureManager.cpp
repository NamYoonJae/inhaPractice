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

D3DXIMAGE_INFO cTextureManager::GetImageInfo(char * path)
{
	if (m_mapImageInfo.find(path) == m_mapImageInfo.end())
	{
		return D3DXIMAGE_INFO();
	}

	return m_mapImageInfo[path];
}

D3DXIMAGE_INFO cTextureManager::GetImageInfo(string path)
{
	return GetImageInfo((char*) path.c_str());
}

void cTextureManager::AddImageInfo(char * path, D3DXIMAGE_INFO info)
{
	if (m_mapImageInfo.find(path) == m_mapImageInfo.end())
		m_mapImageInfo[path] = info;
}

void cTextureManager::AddImageInfo(string & path, D3DXIMAGE_INFO info)
{
	return AddImageInfo((char*)path.c_str(), info);
}

void cTextureManager::AddTexture(char * path, LPDIRECT3DTEXTURE9 texture)
{
	if (m_mapTexture.find(path) == m_mapTexture.end())
		m_mapTexture[path] = texture;
}

void cTextureManager::AddTexture(string & path, LPDIRECT3DTEXTURE9 texture)
{
	return AddTexture((char*)path.c_str(), texture);
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SafeRelease(it.second);
	}
	m_mapTexture.clear();
}

