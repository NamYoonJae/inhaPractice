#include "stdafx.h"
#include "SoulEaterState.h"
#include "DragonSoulEater.h"

#pragma once

cSoulEaterState::cSoulEaterState()
	: m_pDragon(NULL)
	, m_vTarget(0,0,0)
	, m_vDir(0,0,0)
{
}

cSoulEaterState::cSoulEaterState(cDragonSoulEater *pDragon)
			: m_vTarget(0, 0, 0)
			, m_vDir(0,0,0)
{
	m_pDragon = pDragon;
}


cSoulEaterState::~cSoulEaterState()
{
}

void cSoulEaterState::SetDragon(cDragonSoulEater* pDragon)
{
	m_pDragon = pDragon;
}

void cSoulEaterState::TargetCapture()
{
	if (m_pDragon == NULL) return;

	D3DXVECTOR3 pos = m_pDragon->GetPos();

	if (m_pDragon->GetTarget() && m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		m_vTarget = *m_pDragon->GetTarget();
		m_vDir = m_vTarget - m_pDragon->GetPos();


		D3DXMATRIXA16 matR, matRy;
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &(m_vTarget - pos), &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixRotationY(&matRy, D3DX_PI);
		m_pDragon->SetRotation((D3DXMATRIXA16*)&(matR * matRy));

	}
	//

}
