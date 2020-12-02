#include "stdafx.h"
#include "basic.h"
#include "ShaderLoader.h"


LPD3DXEFFECT LoadShader(const char* fullpath)
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

		cout << "Shader Load Failed!" << endl;
	}

	return ret;
}

LPD3DXEFFECT LoadShader(string fullpath)
{
	return LoadShader(fullpath.c_str());
}
