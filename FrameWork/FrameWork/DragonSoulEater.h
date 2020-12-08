#pragma once
#include "cObject.h"
#include "SkinnedMesh.h"

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

public:
	cDragonSoulEater();
	~cDragonSoulEater();
	void Update() override;
	void Render(D3DXMATRIXA16* pmat) override;
	void Setup(char* szFolder, char* szFileName);
	void SetState();
	cSkinnedMesh& GetSkinnedMesh() { return *m_pSkinnedUnit; }

	void GetWorldMatrix(D3DXMATRIXA16* matWorld);

	void SetupBoundingBox();
	virtual void CollisionProcess(cObject* pObject,DWORD dwCollsionTime) override;
	//std::vector<cOBB*>* GetBouningBox() { return &m_vecBoundingBoxList; }

	void Request();
};


