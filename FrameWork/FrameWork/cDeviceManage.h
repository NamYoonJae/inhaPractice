#pragma once

#define g_pDeviceManager cDeviceManage::GetInstance()
#define g_pD3DDevice cDeviceManage::GetInstance()->GetDevice()

class cDeviceManage
{

	Singletone(cDeviceManage);

private:
	LPDIRECT3D9		m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	LPDIRECT3DDEVICE9 GetDevice();
	void Destroy();


};

