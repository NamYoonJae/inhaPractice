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
	TagUI_InGame,
	TagUI_GameOver,
};

enum SceneType;

class cOBB;
class BoneOBB;

class cObject
{
protected:
	
	int			m_nTag;
	cOBB*		m_pOBB;

	vector<BoneOBB*> m_vBoneArray;
	
protected:
	
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vRot;
	D3DXVECTOR3 m_vScale;
public:
	cObject();
	virtual ~cObject();
	virtual void Update() = 0;
	virtual void Render(D3DXMATRIXA16 * pmat = NULL) = 0;
	void Tagging(int enumTag) { m_nTag = enumTag;}
	int GetTag() { return m_nTag; }
	cOBB* GetOBB();
	D3DXVECTOR3 GetPos() { return m_vPos; }
	void SetPos(D3DXVECTOR3 pos) { m_vPos = pos; }
	void GetScaling(D3DXVECTOR3 scale) { m_vScale = scale; }
	void BuildBoneData(DWORD *BoneNum,
		D3DXFRAME *Frame,
		D3DXMESHCONTAINER *pMesh);
};

void GetBoundingBoxSize(D3DXFRAME *pFrame,
	D3DXMESHCONTAINER *pMesh,
	D3DXVECTOR3 *vecSize,
	D3DXVECTOR3 *vecJointOffset);

struct BoneOBB
{
	string szName; // 이걸 통해서 com
	vector<ST_PC_VERTEX> vPoints;
	D3DXVECTOR3			vJointOffset;
	D3DXVECTOR3			vPosition;
};

struct BoundingBox
{
	string szName;
	cOBB*	Box;
	D3DXVECTOR3 m_vScale;

};