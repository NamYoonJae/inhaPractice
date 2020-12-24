#pragma once
#include "Map.h"
#include "ObjLoader.h"

class cArenaMap :
	public iMap
{
private:
	vector<cGroup*>				m_vecMapGroup;
	vector<cGroup*>				m_vecArenaGroup;


	DWORD		m_dwCoolTime;
	DWORD		m_dwElapseTime;
	bool		m_IsSwampCreate;
	Synthesize(RECT, m_RCArea, AREA);
public:
	cArenaMap();
	~cArenaMap();
	virtual float getHeight(D3DXVECTOR3 pos) override;
	virtual void Render(D3DXMATRIXA16 *pmat = NULL) override;
	virtual void Update() override;
	virtual bool CheckInMap(D3DXVECTOR3 pos) override;
	void	CreateSwamp();
};

