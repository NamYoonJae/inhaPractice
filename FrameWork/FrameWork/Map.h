#include "cObject.h"
#include "Swamp.h"
#pragma once

class iMap : public cObject
{
private:
	vector<cSwamp*> m_vecSwampList;
public:
	iMap();
	~iMap();
	virtual float getHeight(D3DXVECTOR3 pos) = 0;
	virtual bool CheckInMap(D3DXVECTOR3 pos) = 0; 
	void RenderTrigger();
	void CreateSwamp(int nSize = 5);
};

