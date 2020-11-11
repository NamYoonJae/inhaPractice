#pragma once
#include "cObject.h"
class SkyBox :
	public cObject
{
private:
	std::vector<ST_PNT_VERTEX> m_vecFace;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3*		m_vPos;
public:
	SkyBox();
	~SkyBox();

	void Setup(string strFolder,string strFileName);
	virtual void Update() override;
	virtual void Render(D3DXMATRIXA16 * pmat = NULL) override;
	void SetPos(D3DXVECTOR3* m_vCamara) { m_vPos = m_vCamara; }
};

