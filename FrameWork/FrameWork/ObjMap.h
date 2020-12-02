#pragma once
#include "Map.h"
#include "ObjLoader.h"
class cObjMap :
	public iMap
{
private:
	std::vector<ST_PNT_VERTEX>  m_vecPNT;
	vector<cMtlTex*>			m_vecMtlTex;
	vector<cGroup*>				m_vecGroup;
public:
	cObjMap(string folder,string file);
	~cObjMap();
	virtual float getHeight(D3DXVECTOR3 pos) override;
	virtual void Render(D3DXMATRIXA16 *pmat = NULL) override;
	virtual void Update() override;
};

