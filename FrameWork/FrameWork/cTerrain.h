#pragma once
#include "Map.h"

#define CullingSize 90

class cTerrain :public iMap
{
private:
	std::vector<ST_PNT_VERTEX> m_vecMapVertex;

	D3DMATERIAL9 m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH	m_pTerrainMesh;
	LPD3DXMESH	m_pNewTerrainMesh;
	int			m_nTile;
	

	RECT		m_CullingRect;
	std::thread *TerrainThread;
	CRITICAL_SECTION	cs;

	std::vector<DWORD> vecIndex;
	std::vector<ST_PNT_VERTEX> vecVertex;
	bool	IsSwapMesh;

	D3DXVECTOR3 *m_pvTarget;
	D3DXVECTOR3	 m_vOldPos;
public:
	cTerrain();
	~cTerrain();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;
	void NewTerrain(D3DXVECTOR3 vec);
	float getHeight(D3DXVECTOR3 vec);
	void Setup(std::string strFolder, std::string strTex,
		std::string strRaw, DWORD dwBytesPerPixel =1.0f,float MaxHegiht = 100.0f);
	
	float getHeightMapEntry(int nRow, int nCol) { return m_vecMapVertex[(m_nTile + 1) * nRow + nCol].p.y;};
	LPD3DXMESH GetTerrainMesh() { return m_pTerrainMesh; }
	bool SwapMesh();
	
	void cTerrain::callThread();
	RECT GetCullingRect();

	float LerpPosition(float, float, float);
	void GetTarget(D3DXVECTOR3* pvTarget) { m_pvTarget = pvTarget; }

	//
	void CreateMaxSizeMeshMap(std::string strFolder, std::string strTex,
		std::string strRaw, DWORD dwBytesPerPixel, float MaxHeight);
	
};

