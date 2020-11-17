#pragma once
#include "cObject.h"

struct ST_BONE;

class cSkinnedMesh : public cObject
{
protected:
	LPD3DXFRAME m_pRoot;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;

	bool m_isAnimBlend;
	float m_fBlendTime;
	float m_fPassedBlendTime;
	
	DWORD m_dAnimStartTime;
public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Setup(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void Render(D3DXMATRIXA16 * pmat = NULL) override;
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);

	// >> : obb
private:
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);
public:
	cSkinnedMesh(char* szFolder, char* szFileName);
	void Load(char* szFolder, char* szFileName);
	void Destroy();
	void UpdateAndRender();
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void SetRandomTrackPosition();

	D3DXMATRIXA16 m_matWorldTM;
	void SetTransform(D3DXMATRIXA16* pmat);
	// <<
};

