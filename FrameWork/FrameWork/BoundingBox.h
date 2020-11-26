#pragma once

class cSkinnedMesh;

class cBoundingBox
{
private:
	D3DCOLOR	m_Color;
	D3DXVECTOR3 m_vPivot;
	D3DXVECTOR3 m_vOriCenter;
	D3DXVECTOR3 m_vOriAxisDir[3];

	D3DXVECTOR3 m_vCenterPos;
	D3DXVECTOR3 m_vAxisDir[3];
	float		m_fAxisLen[3];

	float		m_fAxisHalfLen[3];

	D3DXMATRIXA16 m_matWorldTM;
public:
	cBoundingBox();
	~cBoundingBox();

	void Setup(LPD3DXMESH pMesh);
	void Setup(cSkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	void Render();
	static bool IsCollision(cBoundingBox* pOBB1, cBoundingBox* pOBB2);

	void SetPivot(D3DXVECTOR3 pivot)
	{
		m_vPivot = pivot;
		m_vCenterPos += m_vPivot;
	}

	void SetColor(D3DCOLOR color) { m_Color = color; }
};

