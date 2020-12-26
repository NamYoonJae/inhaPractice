#pragma once


class cTrophies : public cPopup
{
private:

	float m_MaxGauge;
	float m_Gauge;
	bool m_IsTrophiesState;

	DWORD m_dwPreparationTime;
	DWORD m_dwStateStartTime;


public:
	cTrophies();
	~cTrophies();

	void Setup(char* root,
		char* fileName,
		D3DXVECTOR3 position,
		float percent,
		bool powerOnOff,
		bool fixed,
		int tag,
		float maxGauge,
		float gauge
	);

	void Update() override;
	void Update(EventType message);
	void Render(D3DXMATRIXA16* pmat = NULL);

	int GetState();
	void SetStateChange(int state);
	D3DXVECTOR3 GetPosition();

	float GetImageInfoWidth();
	float GetImageInfoHeight();

	void LoadTexture(char* szFullPath);
	void ChangeSprite(char* szFullPath);

	float GetPercent();

	void PowerOnOff();

	/*
	void PowerOnOff(bool power);
	void PowerOnOff_List();
	void PowerOnOff_List(bool power);
	void PowerOnOff_OnlySelf();
	void PowerOnOff_OnlySelf(bool power);
	void PowerOnOff_List_OnlySelf();
	void PowerOnOff_List_OnlySelf(bool power);


	void Destroy();
	
	cPopup* GetTopPopUp();
	cPopup* GetUpPopUp();

	cPopup* GetPopupBtn();
	cPopup* GetPopupBtn(int index);
	*/

	float GetMaxGauge();
	float GetGauge();

};

