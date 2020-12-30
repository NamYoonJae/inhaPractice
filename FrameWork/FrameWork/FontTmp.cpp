#include "stdafx.h"
#include "FontTmp.h"
#include "FontManager.h"
//#include "cObject.h"
#include "ObjectPool.h"
#include "BackViewCamera.h"
#include "TextureManager.h"
D3DXVECTOR3 GetScreenPos(IDirect3DDevice9* pd3dDevice, D3DXVECTOR3& pos);
D3DXVECTOR3* WorldToScreen(IDirect3DDevice9* pDevice, D3DXVECTOR3& vScreenCoord, D3DXVECTOR3 vWorldLocation);

cFont3D::cFont3D()
    : m_dwElapsedTime(0)
    , m_dwDurationTime(1000) // 값 바꾸기
	, m_p3DText(NULL)
	, m_pTex(NULL)
	, cObject()
	, m_fSpeed(0.1f)
{
}

cFont3D::~cFont3D()
{
	SafeRelease(m_pTex);
	SafeRelease(m_p3DText);
}

void cFont3D::Setup(string Text, eTextColortype type)
{
    m_strText = Text;

    //3D 글자
    HDC hdc = CreateCompatibleDC(0);
    LOGFONT lf;
    ZeroMemory(&lf, sizeof(LOGFONT));
    lf.lfHeight = 25;
    lf.lfWidth = 12;
    lf.lfWeight = 500;
    lf.lfItalic = false;
    lf.lfUnderline = false;
    lf.lfStrikeOut = false;
    lf.lfCharSet = DEFAULT_CHARSET;
	AddFontResourceA("data/Font/umberto.ttf");
	wcscpy_s(lf.lfFaceName, L"umberto");

	HFONT hFont;
	HFONT hFontOld;
	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);

	D3DXCreateTextA(
		g_pD3DDevice, hdc,
		m_strText.c_str(),
		0.001f,
		0.01f,
		&m_p3DText,
		0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);

	m_dwElapsedTime = GetTickCount();
	
	
	string strPath = "data/Texture/";
	switch (type)
	{
	case White:
	default:
		strPath += "white.png";
		break;
	case Red:
		strPath += "red.png";
		break;
	case Orenge:
		strPath += "orenge.png";
		m_fSpeed = 0.0f;
		break;
	}

	m_pTex = g_pTextureManager->GetTexture(strPath);
	//D3DXCreateTextureFromFileA(g_pD3DDevice, strPath.c_str(), &m_pTex);

	

	//const int Mapsize = 64;
	//D3DXCreateTexture(g_pD3DDevice, Mapsize,Mapsize, 1, 0, 
	//	D3DFMT_A8B8G8R8, 
	//	D3DPOOL_MANAGED,
	//	&m_pTex);
	//
	// switch
	// 
	//D3DLOCKED_RECT rect;
	//ZeroMemory(&rect, sizeof(D3DLOCKED_RECT));
	//D3DXVECTOR4 RGBA;
	//switch (type)
	//{
	//case White:
	//default:
	//	RGBA.w = 0;
	//	RGBA.x = 255;
	//	RGBA.y = 255;
	//	RGBA.z = 255;
	//	strPath = "White.png";
	//	break;
	//case Red:
	//	RGBA.w = 0;
	//	RGBA.x = 255;
	//	RGBA.y = 0;
	//	RGBA.z = 0;
	//	break;
	//case Orenge:
	//	RGBA.w = 0;
	//	RGBA.x = 0xf8;
	//	RGBA.y = 0x9b;
	//	RGBA.z = 0;
	//	m_fSpeed = 0.0f;
	//	break;
	//}
	//
	//if(FAILED(m_pTex->LockRect(0, &rect, 0, 0)))
	//{
	//	g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "m_pTex->LockRect(0, &rect, 0, 0) FAILED");
	//	return;
	//}
	//
	//BYTE* pByte;
	//pByte = (BYTE*)rect.pBits;
	//for(int i = 0; i < Mapsize; i++)
	//{
	//	for(int j = 0; j < Mapsize; j++)
	//	{
	//		pByte[0] = RGBA.z;	// alpha
	//		pByte[1] = RGBA.y;	// blue
	//		pByte[2] = RGBA.x;	// green
	//		pByte[3] = RGBA.w;	// red
	//		pByte += 4;
	//	}
	//}
	//m_pTex->UnlockRect(0);

}

void cFont3D::Update()
{
    if (GetTickCount() - m_dwElapsedTime >= m_dwDurationTime)
    {
        m_isDelete = true;
    }

    m_vPos.y += m_fSpeed;
}


void cFont3D::Render(D3DXMATRIXA16* pmat)
{
    RenderSprite(g_pD3DDevice,NULL);

}

void cFont3D::RenderSprite(IDirect3DDevice9* Device, D3DXMATRIXA16* pMatrix)
{
    //3D글자가 매쉬로 이루어져 있다
	Device->SetRenderState(D3DRS_LIGHTING, true);
	if (m_pTex)
		Device->SetTexture(0, m_pTex);
	else
		Device->SetTexture(0, NULL);
	D3DXMATRIXA16 matWorld, matS, matR, matT, matView;
    D3DXMatrixIdentity(&matWorld);
    D3DXMatrixIdentity(&matS);
    D3DXMatrixIdentity(&matR);
	Device->GetTransform(D3DTS_VIEW, &matView);
	matR._11 = matView._11;
	matR._31 = matView._31;
	matR._13 = matView._13;
	matR._33 = matView._33;

	D3DXMatrixInverse(&matR, NULL, &matR);
	
    D3DXMatrixIdentity(&matT);
    D3DXMatrixScaling(&matS, 5.0f, 5.0f, 1.0f);
    //D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0f);
    D3DXMatrixTranslation(&matT, m_vPos.x,m_vPos.y,m_vPos.z);
    matWorld = matS * matR * matT;
	//matWorld = matR * matT;
	
	Device->SetTransform(D3DTS_WORLD, &matWorld);
    m_p3DText->DrawSubset(0);
}