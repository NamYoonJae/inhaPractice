#pragma once
#include "Map.h"
#include "ObjLoader.h"

class cArenaMap :
	public iMap
{
private:
	vector<cGroup*>				m_vecMapGroup;
	
	vector<cGroup*>				m_vecDoorGroup;
	vector<cGroup*>				m_vecFlagGroup;
	vector<cGroup*>				m_vecHornGroup;
	vector<cGroup*>				m_vecPillarGroup;
	vector<cGroup*>				m_vecPollGroup;
	vector<cGroup*>				m_vecWoodSpikeGroup;

	vector<cGroup*>				m_vecArenaGroup;
public:
	cArenaMap();
	~cArenaMap();
	virtual float getHeight(D3DXVECTOR3 pos) override;
	virtual void Render(D3DXMATRIXA16 *pmat = NULL) override;
	virtual void Update() override;
	virtual bool CheckInMap(D3DXVECTOR3 pos) override;

	// >> Temp For Shadow Shader
	vector<LPDIRECT3DTEXTURE9> m_vecShadowMap;
	void AddShadowMap(LPDIRECT3DTEXTURE9 pShadowTexture);
	void ReplaceShadowMap(LPDIRECT3DTEXTURE9 pShadowTexture);

	void ShaderSetup();
	void ShaderRender();
	void DefaultRender();
	// << Temp For Shadow Shader 
};

