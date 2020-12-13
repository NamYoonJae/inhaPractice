#include "stdafx.h"
#include "basic.h"
#include "ShaderManager.h"

cShaderManager::cShaderManager()
{
	m_vecShader.resize(eShader::ShaderSize);
}

cShaderManager::~cShaderManager()
{
	
}

LPD3DXEFFECT cShaderManager::GetShader(eShader type)
{
	if(m_vecShader[type] == NULL)
	{
		switch(type)
		{
		case Texture_D:
			m_vecShader[type] = LoadShader("data/Shader/TextureMapping.fx");
			break;
		case Specular_DSL:
			m_vecShader[type] = LoadShader("data/Shader/SpecularMapping.fx");
			break;
		case Normal_DSNL:
			m_vecShader[type] = LoadShader("data/Shader/NormalMapping.fx");
			break;
		case LavaEffect:
			m_vecShader[type] = LoadShader("data/Shader/Lava.fx");
			break;
		case FireBall:
			m_vecShader[type] = LoadShader("data/Shader/fireBall.fx");
		default:
			cout << "Invailed Shader Type!" << endl;
			break;
		}
	}

	return m_vecShader[type];
}

LPD3DXEFFECT cShaderManager::LoadShader(const char* fullpath)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(g_pD3DDevice, fullpath,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void* ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugStringA(str);
			delete[] str;
		}

		cout << fullpath << " Load Failed!" << endl;
	}

	return ret;
}

LPD3DXEFFECT cShaderManager::LoadShader(string fullpath)
{
	return LoadShader(fullpath.c_str());
}
