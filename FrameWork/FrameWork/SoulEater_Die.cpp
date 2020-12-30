#include "stdafx.h"
#include "SoulEater_Die.h"
#include "SkinnedMesh.h"
#include "SoundManager.h"
#include "DragonSoulEater.h"
#include "Scene.h"
#include "SceneManager.h"
#pragma once

cSoulEater_Die::cSoulEater_Die()
{
}

cSoulEater_Die::cSoulEater_Die(cDragonSoulEater *pDragon)
	:cSoulEaterState(pDragon)
	,m_dwStartTime(GetTickCount())
{
	cSkinnedMesh *pDieMesh 
		= new cSkinnedMesh("data/XFile/Dragon","Die.x");
	D3DXMATRIXA16 matWorld;
	D3DXMatrixScaling(&matWorld, 0.2f, 0.2f, 0.2f);
	pDieMesh->SetTransform(&matWorld);
	pDieMesh->SetAnimationIndex(0);
	pDieMesh->SetUsemstl(false);
	pDragon->GetSkinnedMesh() = *pDieMesh;
	g_pSoundManager->PlaySFX(eSoundList::Dragon_Die2);
}


cSoulEater_Die::~cSoulEater_Die()
{
}

void cSoulEater_Die::handle()
{
	if (GetTickCount() - m_dwStartTime > 1300.0f &&
		!m_pDragon->m_isDelete)
	{
		g_pSoundManager->PlaySFX(eSoundList::Dragon_Die1);
		m_pDragon->m_isDelete = true;
		g_pSceneManager->ChangeScene(SCENE_CLEAR);
		return;
	}
}
