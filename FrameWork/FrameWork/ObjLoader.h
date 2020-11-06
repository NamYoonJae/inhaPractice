#pragma once


class cMtlTex
{
private:
	D3DMATERIAL9 m_pMlt;
	LPDIRECT3DTEXTURE9 m_Texture;
public:
	cMtlTex();
	~cMtlTex();

	D3DMATERIAL9 & GetMaterial() { return m_pMlt; }
	void SetMaterial(D3DMATERIAL9 & mtl) { m_pMlt = mtl; }

	LPDIRECT3DTEXTURE9 GetTexture() { return m_Texture; }
	void SetTexture(LPDIRECT3DTEXTURE9 texture) { m_Texture = texture; }
};

class cGroup
{
private:
	vector<ST_PNT_VERTEX> m_vecVertex;
	cMtlTex* m_pMtlTex;
public:
	cGroup();
	~cGroup();

	void Render();

	void SetVertices(OUT vector<ST_PNT_VERTEX> & vertices) { m_vecVertex = vertices; }
	vector<ST_PNT_VERTEX> & GetVertices() { return m_vecVertex; }

	void SetMaterialTexture(cMtlTex* mtltex) { m_pMtlTex = mtltex; }
	cMtlTex* GetMaterialTexture() { return m_pMtlTex; }

	vector<ST_PNT_VERTEX> & GetVertex() { return m_vecVertex; }
};


class cObjLoader
{
private:
	map<string, cMtlTex*> m_mapMtlTex;
public:
	cObjLoader();
	~cObjLoader();

	void LoadOBJ(OUT vector<cGroup*> & vecGroup, IN char * folder, IN char * file);
	void LoadMtlLib(char * folder, char * file);
};

