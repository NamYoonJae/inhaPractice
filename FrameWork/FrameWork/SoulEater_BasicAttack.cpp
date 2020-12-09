#include "stdafx.h"
#include "SoulEater_BasicAttack.h"
#include "DragonSoulEater.h"

cSoulEater_BasicAttack::cSoulEater_BasicAttack()
	:cSoulEaterState()
{
	m_nCurentIndex = 1;
}

cSoulEater_BasicAttack::cSoulEater_BasicAttack(cDragonSoulEater *pDragon)
	:cSoulEaterState(pDragon)
{

}

cSoulEater_BasicAttack::~cSoulEater_BasicAttack()
{
}

void cSoulEater_BasicAttack::handle()
{
	// 함수로 만들자
	if (m_pDragon == NULL ) return;
	
	if (m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		TargetCapture();
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Walk);
	}

	D3DXVECTOR3 pos = m_pDragon->GetPos();
	
	//
	float distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));

	if (distance <= 10.0f)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Basic_Attack);
		m_pDragon->Request();
		// 딜레이 줘야하는데 어떻게하면좋을까
		return;
	}
	else
	{
		pos += m_vDir * 0.01f;
	}
}
