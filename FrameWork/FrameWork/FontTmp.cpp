#include "stdafx.h"
#include "FontTmp.h"
#include "FontManager.h"
//#include "cObject.h"
#include "ObjectPool.h"
#include "BackViewCamera.h"

D3DXVECTOR3 GetScreenPos(IDirect3DDevice9* pd3dDevice, D3DXVECTOR3& pos);
D3DXVECTOR3* WorldToScreen(IDirect3DDevice9* pDevice, D3DXVECTOR3& vScreenCoord, D3DXVECTOR3 vWorldLocation);

cFontTmp::cFontTmp()
    : m_pFont(NULL)
    , m_pSprite(NULL)
    , m_dwElapsedTime(0)
    , m_dwDurationTime(5000) // 나중에 값 바꾸기
	, cObject()
{
}

cFontTmp::~cFontTmp()
{
    SafeRelease(m_pFont);
    SafeRelease(m_pSprite);
}

//void cFontTmp::Setup()
//{
//    D3DXCreateFont(g_pD3DDevice, 20, 0, FW_BOLD, 0,
//        FALSE, DEFAULT_CHARSET,
//        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
//        DEFAULT_PITCH | FF_DONTCARE, TEXT("궁서"),
//        &m_pFont);
//
//    D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
//}

void cFontTmp::Setup(string Text, eFontType type)
{
    m_strText = Text;
    m_pFont = g_pFontManager->GetFont(type);
    D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

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
	//AddFontResource(L"data/Font/Bold.ttf");
	//AddFontResourceA("data/Font/Bold.ttf");
	wcscpy_s(lf.lfFaceName, L"Bold");
	// wcscpy_s(lf.lfFaceName, L"Algerian Regular");
	//AddFontResourceA("data/Font/Algerian Regular.ttf");
	//wcscpy_s(lf.lfFaceName, L"Algerian Regular");
	//AddFontResourceA("data/Font/umberto.ttf");
	//wcscpy_s(lf.lfFaceName, L"umberto");
	
	

    HFONT hFont;
    HFONT hFontOld;

    hFont = CreateFontIndirect(&lf);
    hFontOld = (HFONT)SelectObject(hdc, hFont);
    D3DXCreateTextA(g_pD3DDevice, hdc,
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

//void cFontTmp::Setup(int Number, eFontType type)
//{
//    m_strText = Number;
//    m_pFont = g_pFontManager->GetFont(type);
//    D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
//
//    m_dwElapsedTime = GetTickCount();
//}

void cFontTmp::Update()
{
    // 시간지나면 사라지게
    if (GetTickCount() - m_dwElapsedTime >= m_dwDurationTime)
    {
        m_isDelete = true;
    }


}


void cFontTmp::Render(D3DXMATRIXA16* pmat)
{
    RenderSprite(g_pD3DDevice,NULL);


    //if (m_pSprite == NULL)
    //    Setup("텍스트 없음", eFontType::FONT_DEFAULT);
    //    //Setup(g_pD3DDevice);

    //wstring wstrResult = wstring(m_strText.begin(), m_strText.end());
    //const wchar_t* wcharResult = wstrResult.c_str();

    //D3DXMATRIX world;
    //D3DXMatrixTranslation(&world, 100, 100, 0);
    //m_pSprite->SetTransform(&world);
    //m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE); //2D

    //RECT rectTemp = { 100, 100, 500, 500 };
    ////m_pFont->DrawText(m_pSprite, L"Hello World!", -1, &rectTemp, 0,
    //m_pFont->DrawText(m_pSprite, wcharResult, -1, &rectTemp, 0,
    //    D3DCOLOR_COLORVALUE(1, 0, 0, 1)); //0xFFFF0000);
    //m_pSprite->End();
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
    //matWorld = matS * matR * matT;
	//matWorld = matR * matT;

	//D3DXMatrixInverse(&matWorld, NULL, &matWorld);
	
	Device->SetTransform(D3DTS_WORLD, &matWorld);
    m_p3DText->DrawSubset(0);
}




D3DXVECTOR3 GetScreenPos(IDirect3DDevice9* pd3dDevice, D3DXVECTOR3& pos)
{
    D3DXMATRIX matView;
    D3DXMATRIX matProj;

    g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
    g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

    D3DXMATRIX mat = matView * matProj;

    D3DXVECTOR3 point;
    D3DXVec3TransformCoord(&point, &pos, &mat);

    RECT rc;
    GetClientRect(g_hWnd,&rc);

    //x, y를 스크린 좌표로 변환
    point.x = (point.x + 1) * (rc.right - rc.left)/ 2;
    point.y = (point.y + 1) * (rc.bottom - rc.top) / 2;

    return point;
}

D3DXVECTOR3 * WorldToScreen(IDirect3DDevice9 * pDevice, D3DXVECTOR3 & vScreenCoord, D3DXVECTOR3 vWorldLocation)
{
    //D3DVIEWPORT9 viewPort;
    //D3DXMATRIX matProj, matView, identity;
    //pDevice->GetViewport(&viewPort);
    //D3DXMatrixIdentity(&identity);

    ////뷰, 프로젝트, 뷰포트 설정
    //matView = *g_VCamera.GetViewMatrix();
    //matProj = *g_VCamera.GetProjMatrix();

    //// 뷰포트 설정
    //viewPort.Width = ;
    //viewPort.Height = ;

    //D3DXVec3Project(&vScreenCoord, &vWorldLocation, &viewPort, &matProj, &matView, &identity);

    //if (vScreenCoord.z >= 0 && vScreenCoord.z <= 1)
    //    return &vScreenCoord;
        return NULL;
}