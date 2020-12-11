#pragma once
#include "SkinnedMesh.h"
#include "Arthur.h"
class cLavaFlood
	
{
private:
	D3DXVECTOR3 m_vPos;
	LPD3DXEFFECT m_pEffect;
	LPDIRECT3DTEXTURE9 m_pFlameTex;

	DWORD	m_dwElapseTime;
	DWORD	m_dwStartTime;
	DWORD	m_dwPrevTime;
	// ���� ��Ų�� �Ž��� �ʿ���
public:
	cLavaFlood();
	~cLavaFlood();
	void Setup();
	void Update();
	void Render(D3DXMATRIXA16* pmat);
};

