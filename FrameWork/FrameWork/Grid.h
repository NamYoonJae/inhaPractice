#pragma once
#include "cObject.h"
class cPyramidGizmo;

class cGrid : public cObject
{
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<ST_PN_VERTEX>    m_vecBoardVertex;
	vector<cPyramidGizmo>   m_vecGizmo;
public:
	cGrid();
	~cGrid();

	void Setup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void Render(D3DXMATRIXA16* pmat = 0) override;
	void Update() override{};
};

class cPyramidGizmo
{
private:
	vector<ST_PC_VERTEX> m_vecVertex;

	D3DXMATRIXA16 ScaleMat, RotateMat, WorldMat;
public:
	cPyramidGizmo() = default;
	~cPyramidGizmo() = default;

	void Setup(D3DCOLOR color, D3DXMATRIXA16 & rotatemat);
	void Render();
};

