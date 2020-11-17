#pragma once

#define g_pTextureManager cTextureManager::GetInstance()
class cTextureManager
{
protected:
	Singletone(cTextureManager);

	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, D3DXIMAGE_INFO> m_mapImageInfo;

public:

	/*cTextureManager();
	~cTextureManager();*/
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullpath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string &sFullpath);




	D3DXIMAGE_INFO GetImageInfo(char* path);
	D3DXIMAGE_INFO GetImageInfo(string path);

	void AddImageInfo(char* path, D3DXIMAGE_INFO info);
	void AddImageInfo(string& path, D3DXIMAGE_INFO info);

	void AddTexture(char* path, LPDIRECT3DTEXTURE9 texture);
	void AddTexture(string& path, LPDIRECT3DTEXTURE9 texture);

	void Destroy();

};

