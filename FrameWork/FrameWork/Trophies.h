#pragma once


class cTrophies : public cPopup
{
private:

	int m_MaxGauge;
	int m_Gauge;


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
		int maxGauge,
		int gauge
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

	int GetMaxGauge();
	int GetGauge();

};

