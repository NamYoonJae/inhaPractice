#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	ST_BONE*					m_pRootFrame;			
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXMATRIXA16				m_matWorldTM;

	/// >> : OBB -
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);

	bool m_isAnimBlend;
	float m_fBlendTime;
	float m_fPassedBlendTime;

	DWORD m_dAnimStartTime;
public:
	cSkinnedMesh(char* szFolder, char* szFilename);	 
	~cSkinnedMesh(void);
	
	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);

	void SetRandomTrackPosition();
	void SetTransform(D3DXMATRIXA16* pmat)
	{
		m_matWorldTM = *pmat;
	}
private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render_UsingShader(ST_BONE* pBone = NULL);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void SetAnimationIndexBlend(int nIndex);
	void Destroy();
};

