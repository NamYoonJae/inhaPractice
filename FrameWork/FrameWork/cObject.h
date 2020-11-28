#pragma once


const enum Tag
{
	Tag_Camera,
	Tag_SkyBox,
	Tag_Map,
	Tag_Player,
	Tag_Boss,
	Tag_NormalEnemy,
	Tag_cObj
};

enum TAG_UI
{
	TagUI_Title,
	TagUI_InGame
};

class cOBB;

class cObject
{
protected:
	
	int			Tag;
	cOBB*		m_pOBB;

protected:
	
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vRot;

public:
	cObject();
	virtual ~cObject();
	virtual void Update() = 0;
	virtual void Render(D3DXMATRIXA16 * pmat = NULL) = 0;
	void Tagging(int enumTag) { Tag = enumTag;}
	int GetTag() { return Tag; }
	cOBB* GetOBB();
	D3DXVECTOR3 GetPos() { return m_vPos; }
	void SetPos(D3DXVECTOR3 pos) { m_vPos = pos; }
};
