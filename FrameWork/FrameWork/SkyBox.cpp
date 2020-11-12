#include "stdafx.h"
#include "SkyBox.h"

#define PNGSIZE 256

SkyBox::SkyBox()
	:m_pTexture(NULL)
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::Setup(string strFolder, string strFileName)
{
	/// 256 x 256
	string strFullPath = strFolder + string("/") + strFileName;
	D3DXCreateTextureFromFileA(g_pD3DDevice,strFullPath.c_str(), &m_pTexture);

	std::vector<ST_PNT_VERTEX> vecVertex;
	std::vector<DWORD> vecIndex;
	vecVertex.resize(8);

	vecVertex[0].p.x = -0.5f;	vecVertex[0].p.y = -0.5f;	vecVertex[0].p.z = -0.5f;
	vecVertex[1].p.x = -0.5f;	vecVertex[1].p.y = 0.5f;	vecVertex[1].p.z = -0.5f;
	vecVertex[2].p.x = 0.5f;	vecVertex[2].p.y = 0.5f;	vecVertex[2].p.z = -0.5f;
	vecVertex[3].p.x = 0.5f;	vecVertex[3].p.y = -0.5f;	vecVertex[3].p.z = -0.5f;

	vecVertex[4].p.x = -0.5f;	vecVertex[4].p.y = -0.5f;	vecVertex[4].p.z = 0.5f;
	vecVertex[5].p.x = -0.5f;	vecVertex[5].p.y = 0.5f;	vecVertex[5].p.z = 0.5f;
	vecVertex[6].p.x = 0.5f;	vecVertex[6].p.y = 0.5f;	vecVertex[6].p.z = 0.5f;
	vecVertex[7].p.x = 0.5f;	vecVertex[7].p.y = -0.5f;	vecVertex[7].p.z = 0.5f;

	// : front
	vecIndex.push_back(0); vecIndex.push_back(1); vecIndex.push_back(2);
	vecIndex.push_back(0); vecIndex.push_back(2); vecIndex.push_back(3);
	// : back
	vecIndex.push_back(4); vecIndex.push_back(6); vecIndex.push_back(5);
	vecIndex.push_back(4); vecIndex.push_back(7); vecIndex.push_back(6);
	// : left
	vecIndex.push_back(4); vecIndex.push_back(5); vecIndex.push_back(1);
	vecIndex.push_back(4); vecIndex.push_back(1); vecIndex.push_back(0);
	// : right
	vecIndex.push_back(3); vecIndex.push_back(2); vecIndex.push_back(6);
	vecIndex.push_back(3); vecIndex.push_back(6); vecIndex.push_back(7);
	// : top
	vecIndex.push_back(1); vecIndex.push_back(5); vecIndex.push_back(6);
	vecIndex.push_back(1); vecIndex.push_back(6); vecIndex.push_back(2);
	// : bottom
	vecIndex.push_back(4); vecIndex.push_back(0); vecIndex.push_back(3);
	vecIndex.push_back(4); vecIndex.push_back(3); vecIndex.push_back(7);

	m_vecFace.resize(36);
	for (size_t i = 0; i < vecIndex.size(); i += 3)
	{
		m_vecFace[i + 0] = vecVertex[vecIndex[i + 0]];
		m_vecFace[i + 1] = vecVertex[vecIndex[i + 1]];
		m_vecFace[i + 2] = vecVertex[vecIndex[i + 2]];

	}
	D3DXVECTOR3 u, v, n;
	
	for (int i = 0; i < 36; i += 3)
	{
		u = m_vecFace[i + 1].p - m_vecFace[i].p;
		v = m_vecFace[i + 2].p - m_vecFace[i].p;

		D3DXVec3Cross(&n, &u, &v);
		m_vecFace[i + 0].n = n;
		m_vecFace[i + 1].n = n;
		m_vecFace[i + 2].n = n;

	}
	
	int x = PNGSIZE * 4;
	int y = PNGSIZE * 3;

	
	// 0 1 2 0 2 3
	m_vecFace[0].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x,(float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[1].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[2].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);

	m_vecFace[3].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[4].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[5].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	
	// back 3 x 3  4  6 5   4 7 6
	m_vecFace[6].t = D3DXVECTOR2((float)(PNGSIZE * 3 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[7].t = D3DXVECTOR2(1.0f, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[8].t = D3DXVECTOR2((float)(PNGSIZE * 3 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);

	m_vecFace[9].t = D3DXVECTOR2((float)(PNGSIZE * 3 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[10].t = D3DXVECTOR2(1.0f, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[11].t = D3DXVECTOR2(1.0f, (float)(PNGSIZE * 1 + 1) / y);
	

	m_vecFace[12].t = D3DXVECTOR2((float)(PNGSIZE * 3 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[13].t = D3DXVECTOR2((float)(PNGSIZE * 3 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[14].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);

	m_vecFace[15].t = D3DXVECTOR2((float)(PNGSIZE * 3 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[16].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[17].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	

	m_vecFace[18].t = D3DXVECTOR2((float)(PNGSIZE + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[19].t = D3DXVECTOR2((float)(PNGSIZE + 1) / x, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[20].t = D3DXVECTOR2(0.0f, (float)(PNGSIZE * 1 + 1) / y);
	
	m_vecFace[21].t = D3DXVECTOR2((float)(PNGSIZE + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[22].t = D3DXVECTOR2(0.0f, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[23].t = D3DXVECTOR2(0.0f, (float)(PNGSIZE * 2 + 1) / y);



	//
	// : top 1 5 6 1 6 2
	m_vecFace[24].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, 0);
	m_vecFace[25].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[26].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);

	m_vecFace[27].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, 0);
	m_vecFace[28].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 1 + 1) / y);
	m_vecFace[29].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x,0);

	// bottem 4 0 3  4 3 7
	m_vecFace[30].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[31].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x,1.0f);
	m_vecFace[32].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x,1.0f);

	m_vecFace[33].t = D3DXVECTOR2((float)(PNGSIZE * 1 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);
	m_vecFace[34].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, 1.0f);
	m_vecFace[35].t = D3DXVECTOR2((float)(PNGSIZE * 2 + 1) / x, (float)(PNGSIZE * 2 + 1) / y);

	

}

void SkyBox::Update()
{
	
}

void SkyBox::Render(D3DXMATRIXA16* pmat)
{

	D3DXMATRIXA16 matWorld,matS,matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 3, 3, 3);
	D3DXMatrixTranslation(&matT, m_vPos->x,m_vPos->y,m_vPos->z);
	matWorld *= matS * matT;

		
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecFace.size() / 3,&m_vecFace[0],sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

}
