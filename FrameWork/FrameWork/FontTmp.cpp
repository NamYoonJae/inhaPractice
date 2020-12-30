#include "stdafx.h"
#include "FontTmp.h"
#include "FontManager.h"
//#include "cObject.h"
#include "ObjectPool.h"
#include "BackViewCamera.h"

D3DXVECTOR3 GetScreenPos(IDirect3DDevice9* pd3dDevice, D3DXVECTOR3& pos);
D3DXVECTOR3* WorldToScreen(IDirect3DDevice9* pDevice, D3DXVECTOR3& vScreenCoord, D3DXVECTOR3 vWorldLocation);

cFontTmp::cFontTmp()
    : m_dwElapsedTime(0)
    , m_dwDurationTime(1000) // 나중에 값 바꾸기
	, m_p3DText(NULL)
	, cObject()
{
}

cFontTmp::~cFontTmp()
{
	
	SafeRelease(m_p3DText);
}

void cFontTmp::Setup(string Text, eFontType type)
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

	
	//AddFontResource(L"data/Font/Bold.ttf");
	//AddFontResourceA("data/Font/Bold.ttf");
	//wcscpy_s(lf.lfFaceName, L"Bold");
	//wcscpy_s(lf.lfFaceName, L"Algerian Regular");
	//AddFontResourceA("data/Font/Algerian Regular.ttf");
	//wcscpy_s(lf.lfFaceName, L"Algerian Regular");
	

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
}

void cFontTmp::Update()
{
    if (GetTickCount() - m_dwElapsedTime >= m_dwDurationTime)
    {
        m_isDelete = true;
    }

    m_vPos.y += 0.1f;
}


void cFontTmp::Render(D3DXMATRIXA16* pmat)
{
    RenderSprite(g_pD3DDevice,NULL);

}

void cFontTmp::RenderSprite(IDirect3DDevice9* Device, D3DXMATRIXA16* pMatrix)
{
    //3D글자가 매쉬로 이루어져 있다
	Device->SetRenderState(D3DRS_LIGHTING, true);
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