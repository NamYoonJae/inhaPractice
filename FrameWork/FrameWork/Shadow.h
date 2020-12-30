#pragma once

class cShadow : public cObject
{

private:

	LPD3DXMESH		m_pMesh;
	std::vector<D3DMATERIAL9> m_vecMtl;
	LPDIRECT3DTEXTURE9  m_pTexcoord;
	//D3DXVECTOR3 m_Scale;

public:
	cShadow();
	~cShadow();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16* pmat = NULL);

};