#include "stdafx.h"
#include "cDeviceManage.h"


cDeviceManage::cDeviceManage()
	:m_pD3D(NULL)
	, m_pDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);


	D3DCAPS9 stCaps;
	int nVertexProcessing;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}


	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));

	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, nVertexProcessing, &stD3DPP, &m_pDevice);


}


cDeviceManage::~cDeviceManage()
{
}


LPDIRECT3DDEVICE9 cDeviceManage::GetDevice()
{
	return m_pDevice;
}

void cDeviceManage::Destroy()
{
	SafeRelease(m_pD3D);
	SafeRelease(m_pDevice);
}
