#pragma once


class cTerrain
{
private:
	std::vector<ST_PNT_VERTEX> m_vecMapVertex;

	D3DMATERIAL9 m_stMtl;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH	m_pTerrainMesh;
	int			m_nTile;
	bool		m_IsKeyThread;

	RECT		m_CullingRect;
	std::thread *TerrainThread;
	CRITICAL_SECTION	cs;
public:
	cTerrain();
	~cTerrain();
	void Render();
	void NewTerrain(D3DXVECTOR3 vec);
	float getHeight(D3DXVECTOR3 vec);
	void Setup(std::string strFolder, std::string strTex,
		std::string strRaw, DWORD dwBytesPerPixel =1.0f);
	
	float getHeightMapEntry(int nRow, int nCol) { return m_vecMapVertex[(m_nTile) * nRow + nCol].p.y;};
	LPD3DXMESH GetTerrainMesh() { return m_pTerrainMesh; }

	void cTerrain::callThread(D3DXVECTOR3 vec);
	RECT GetCullingRect() { return m_CullingRect; };

	float LerpPosition(float, float, float);
};

