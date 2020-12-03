#pragma once
#include "cObject.h"

struct ST_BONE;

class cSkinnedMesh
{
protected:
	LPD3DXFRAME		m_pRoot;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;

	bool			m_isAnimBlend;
	float			m_fPassedBlendTime;
	DWORD			m_dAnimStartTime;
	
	Synthesize(float, m_fBlendTime, BlendTime);
	Synthesize(bool, m_isDefaultAnim, DefaultAnimState);
	Synthesize(unsigned int, m_uiDefaultIndex, DefaultAnimIndex);
public:
	
	cSkinnedMesh();
	virtual ~cSkinnedMesh();

	virtual void Setup(char* szFolder, char* szFile);
	virtual void Update();
	virtual void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	virtual void Render(LPD3DXFRAME pFrame);
	virtual void Render(D3DXMATRIXA16 * pmat = NULL);
	virtual void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	virtual void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	virtual void SetAnimationIndex(int nIndex);
	virtual void SetAnimationIndexBlend(int nIndex);
	virtual LPD3DXANIMATIONCONTROLLER GetAnimationController();
	
	// >> : obb
private:
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);
public:
	cSkinnedMesh(char* szFolder, char* szFileName);
	void Load(char* szFolder, char* szFileName);
	virtual void Destroy();
	void UpdateAndRender();
	virtual void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void SetRandomTrackPosition();

	D3DXMATRIXA16 m_matWorldTM;
	void SetTransform(D3DXMATRIXA16* pmat);
	D3DXMATRIXA16* GetCombineMatrix();
	bool GetIsBlend() { return m_isAnimBlend; }
	void SetIsBlend(bool b) { m_isAnimBlend = b; }
	// <<

	D3DXMATRIX* m_pTransformationMatrix;
	D3DXMATRIX* m_pCurrentBoneMatrices;
	//
	std::vector<D3DXMATRIXA16*> SetUpBoneMatrix();
	D3DXFRAME* GetFrame() { return m_pRoot; }

	float	GetPassedBlendTime(){ return m_fPassedBlendTime; }
	void	SetPassedBlendTime(float time) { m_fPassedBlendTime = time; }
	DWORD	GetAnimStartTime() { return m_dAnimStartTime; }
	void	SetAnimStartTime(DWORD time) { m_dAnimStartTime = time; }
};

