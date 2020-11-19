#include "stdafx.h"
#include "DragonSoulEater.h"
#include "SoulEaterState.h"
#include "cOBB.h"
DragonSoulEater::DragonSoulEater()
{
}


DragonSoulEater::~DragonSoulEater()
{
}

void DragonSoulEater::Update()
{
	// 플레이어와 통신
	// 상태에 대한 업데이트


	// 분노와 같은 상태를 강제로 바꿔야하는 경우 자신이 상태를 바꿔준다.
	{
		//SetState()
	}
	//m_pSkinnedUnit->Update();
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixScaling(&matWorld, 0.2f, 0.2f, 0.2f);
	//m_pOBB->Update(&matWorld);
	//if(m_pCurState)
	//{
	//	m_pCurState->Update();
	//}

}

void DragonSoulEater::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matWorld, matT,
	matR, matRx,matRy,matRz;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationX(&matRx,m_vRot.x);
	D3DXMatrixRotationY(&matRy,m_vRot.y);
	D3DXMatrixRotationZ(&matRz, m_vRot.z);
	matR = matRx * matRy * matRz;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	matWorld = matR * matT;
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
	m_pSkinnedUnit->Render();
	m_pOBB->OBBBOX_Render(D3DXCOLOR(0,1.0f,0,1.0f));

}

void DragonSoulEater::Setup(char* szFolder, char* szFileName)
{
	m_pSkinnedUnit = new cSkinnedMesh(szFolder, szFileName);
	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pSkinnedUnit);
}

void DragonSoulEater::SetState()
{
	if(true)
	{
		// 강제적으로 상태가 변화해야할때 분노후 페이즈 변화
	}
	else if(true)
	{
		
	}
	else
	{
		// 패턴을 정한다.
	}
}
