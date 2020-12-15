#include "cObject.h"
#pragma once

class iMap : public cObject
{
public:
	iMap();
	~iMap();
	virtual float getHeight(D3DXVECTOR3 pos) = 0;
	virtual bool CheckInMap(D3DXVECTOR3 pos) = 0; 
};

