#pragma once


const enum Tag {
	Tag_Player,
	Tag_Camera,
	Tag_SkyBox,
	Tag_Map,
	Tag_Boss,
	Tag_NormalEnemy,
	Tag_cObj };




class cObject
{
protected:
	int Tag;
public:
	cObject();
	~cObject();
	virtual void Update() = 0;
	virtual void Render(D3DXMATRIXA16 * pmat = NULL) = 0;
	void Tagging(int enumTag) { Tag = enumTag;}
	int GetTag() { return Tag; }
};
