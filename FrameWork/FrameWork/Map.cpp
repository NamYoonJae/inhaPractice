#include "stdafx.h"
#include "Map.h"
#include "ObjectPool.h"
#include "jsonManager.h"
#pragma once

iMap::iMap()
{
	// json 받아와서 쿨타임 넣기

	// CreateSwamp();
}


iMap::~iMap()
{
}

void iMap::RenderTrigger()
{

	std::random_device rd;
	std::mt19937_64 mtRand(rd());
	std::uniform_real_distribution<float> dis(-300, 300.0);
	for (int i = 0; i < m_vecSwampList.size(); ++i)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(dis(rd), 1, dis(rd));
		m_vecSwampList[i]->SetPos(pos);
		ObjectManager->AddChild(m_vecSwampList[i]);
	}

}

void iMap::CreateSwamp(int nSize) // << 변경하기
{
	m_vecSwampList.resize(nSize);
	for (int i = 0; i < m_vecSwampList.size(); ++i)
	{
		cSwamp *pSwamp = new cSwamp;
		
		pSwamp->Setup();
		pSwamp->Tagging(Tag::Tag_SwampA);
		m_vecSwampList[i] = pSwamp;
	}
}
