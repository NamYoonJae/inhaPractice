#pragma once

enum eFontType;

class cFontTmp : public cObject
{
private:
	//LPD3DXFONT	m_pFont;
	//ID3DXSprite*	m_pSprite;

	ID3DXMesh*  m_p3DText;

	DWORD		m_dwElapsedTime;
	DWORD		m_dwDurationTime;

	string		m_strText;
	
public:
	cFontTmp();
	~cFontTmp();

	//void Setup();
	void Setup(string Text, eFontType type);
	//void Setup(int Number, eFontType type);
	void Update();
	void Render(D3DXMATRIXA16* pmat = 0) override;
	void RenderSprite(IDirect3DDevice9* Device, D3DXMATRIXA16* pMatrix);
};

