#pragma once

#define g_pTextureManager cTextureManager::GetInstance()
class cTextureManager
{
protected:
	Singletone(cTextureManager);

	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;

public:

	/*cTextureManager();
	~cTextureManager();*/
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullpath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string &sFullpath);
	void Destroy();

};

