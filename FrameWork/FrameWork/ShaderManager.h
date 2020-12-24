#pragma once

#define g_pShaderManager cShaderManager::GetInstance()

// D: DiffuseMap
// L: Light
// S: SpecularMap
// N: NormalMap
enum eShader
{
	Texture_D = 0,
	Texture_DL,
	Specular_DSL,
	Normal_DSNL,
	LavaEffect,
	FireBall,
	Swamp,
	Shader_DSNL,

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

