#pragma once

#define g_pShaderManager cShaderManager::GetInstance()

enum eShader
{
	Texture = 0,
	Specular,




	ShaderSize
};

class cShaderManager
{
private:
	Singletone(cShaderManager);
	vector<LPD3DXEFFECT> m_vecShader;

public:
	LPD3DXEFFECT GetShader(eShader type);
private:
	LPD3DXEFFECT LoadShader(const char* fullpath);
	LPD3DXEFFECT LoadShader(string fullpath);
};

