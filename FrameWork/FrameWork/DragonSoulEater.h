#pragma once
#include "cObject.h"
#include "SkinnedMesh.h"


//
class cSoulEaterState;
class cOBB;
class cDragonSoulEater :
	public cObject
{
private:
	cSkinnedMesh*		m_pSkinnedUnit;
	D3DMATERIAL9		m_Mstl;

	
	cSoulEaterState*	m_pCurState;
	DWORD				m_dwDelayState;

	float				m_fCurHeathpoint;
	float				m_fMaxHeathPoint;

	D3DXMATRIXA16		m_matWorld;
	LPDIRECT3DTEXTURE9	m_pTexture;

	vector<BoundingBox> m_vecBoundingBoxList;
	
	// >> new
	D3DXVECTOR3*			m_pvTarget;
	int						m_nPrevStateIndex;
	D3DXMATRIXA16			m_matRotation;

	//

public:
	cDragonSoulEater();
	~cDragonSoulEater();
	void Update() override;
	void Render(D3DXMATRIXA16* pmat) override;
	void Setup(char* szFolder, char* szFileName);
	cSkinnedMesh& GetSkinnedMesh() { return *m_pSkinnedUnit; }

	void GetWorldMatrix(D3DXMATRIXA16* matWorld);

	void SetupBoundingBox();
	virtual void CollisionProcess(cObject* pObject) override;
	//std::vector<cOBB*>* GetBouningBox() { return &m_vecBoundingBoxList; }

	//new
	void Request();
	D3DXVECTOR3* GetTarget();
	D3DXMATRIXA16* GetRotation() { return &m_matRotation; }
	void SetRotation(D3DXMATRIXA16* mat) { m_matRotation = *mat; }
};


