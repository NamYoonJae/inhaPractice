#pragma once
class cObject
{
public:
	cObject();
	~cObject();
	virtual void Update() = 0;
	virtual void Render(D3DXMATRIXA16 * pmat = NULL) = 0;
};

