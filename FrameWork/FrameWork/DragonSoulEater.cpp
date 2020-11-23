#include "stdafx.h"
#include "TextureManager.h"
#include "DragonSoulEater.h"
#include "SoulEaterState.h"
#include "cOBB.h"
DragonSoulEater::DragonSoulEater()
	:m_pSkinnedUnit(NULL)
	,m_pCurState(NULL)
{
	m_pOBB = NULL;
}


DragonSoulEater::~DragonSoulEater()
{
	SafeDelete(m_pOBB);
	SafeDelete(m_pCurState);
	SafeDelete(m_pSkinnedUnit);
}

void DragonSoulEater::Update()
{
	// 플레이어와 통신
	// 상태에 대한 업데이트


	// 분노와 같은 상태를 강제로 바꿔야하는 경우 자신이 상태를 바꿔준다.
	{
		//SetState()
	}
	static DWORD  dwTime = GetTickCount();

	//if(GetTickCount() - dwTime > 5000.0f)
		m_pSkinnedUnit->Update();

	D3DXMATRIXA16 matBone;
	D3DXMATRIXA16* matT = m_pSkinnedUnit->GetCombineMatrix();

	matBone = *(D3DXMATRIXA16*)m_pSkinnedUnit->CurrentBoneMatrices;
	
	//D3DXMATRIXA16 matOBB,matR, matT;
	//D3DXMatrixScaling(&matOBB, 0.05, 0.05, 0.05);
	//D3DXMatrixRotationX(&matR, D3DX_PI * 0.5);
	//D3DXMatrixTranslation(&matT, 0,30, 0);
	//matOBB = matOBB * matR * matT;
	m_pOBB->Update(&matBone);
	
	
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
	m_pTexture = g_pTextureManager->GetTexture("data/XFile/Dragon/BlueHP.png");
	g_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pSkinnedUnit->Render();
	g_pD3DDevice->SetTexture(0, NULL);
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

void DragonSoulEater::GetWorldMatrix(D3DXMATRIXA16* matWorld)
{
	m_matWorld = *matWorld;
}
