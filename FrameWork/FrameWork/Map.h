#include "cObject.h"
#include "Swamp.h"
#pragma once

class iMap : public cObject
{
private:
	vector<cSwamp*> m_vecSwampList;

protected:
	float m_fCooltime;
	Synthesize(bool, m_bIsPhase_2, Phase_2);

public:
	iMap();
	~iMap();
	virtual float getHeight(D3DXVECTOR3 pos) = 0;
	virtual bool CheckInMap(D3DXVECTOR3 pos) = 0; 
	void RenderTrigger();
	void CreateSwamp(int nSize = 5);
};

