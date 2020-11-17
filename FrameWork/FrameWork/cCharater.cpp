#include "stdafx.h"
#include "cCharater.h"
#include "EventManager.h"

cCharater::cCharater()
	:m_vRot(0,0,0)
	,m_vPos(0,0,0)
	,m_vDir(0,0,-1)
	,m_pMesh(NULL)
{
	
}


cCharater::~cCharater()
{
	SafeDelete(m_pMesh);
	
}

void cCharater::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, 3.0f, 30,
		10, &m_pMesh, NULL);

	ZeroMemory(&m_Mstl, sizeof(D3DMATERIAL9));
	m_Mstl.Ambient  = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_Mstl.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_Mstl.Diffuse  = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
}

void cCharater::Update(EventType message)
{

	if (message == EventType::EVENT_ARROW_UP)
	{
		m_vPos += m_vDir * 0.3f;
	}
	else if (message == EventType::EVENT_ARROW_DOWN)
	{
		m_vPos -= m_vDir * 0.3f;
	}
	else if (message == EventType::EVENT_ARROW_LEFT)
	{
		m_vRot.y += -0.3f;
	}
	else if (message == EventType::EVENT_ARROW_RIGHT)
	{
		m_vRot.y += +0.3f;
	}

	D3DXMATRIXA16 matRy;
	D3DXMatrixRotationY(&matRy, m_vRot.y);
	D3DXVec3TransformCoord(&m_vDir, &D3DXVECTOR3(0, 0, -1), &matRy);

}



void cCharater::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matWorld, matT, matR,
		matRx, matRy, matRz;

	D3DXMatrixIdentity(&matWorld);

	// rotation , position
	D3DXMatrixRotationX(&matRx, m_vRot.x);
	D3DXMatrixRotationY(&matRy, m_vRot.y);
	D3DXMatrixRotationZ(&matRz, m_vRot.z);

	matR = matRx * matRy * matRz;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	matWorld = matR * matT;

	if (pmat)
		matWorld *= *pmat;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_Mstl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMesh->DrawSubset(0);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	
}
