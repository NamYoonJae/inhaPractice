#pragma once
#include "basic.h"
#include "Observer.h"
#include "cObject.h"
#include <functional>

class cButton;
class cPopup;
class cPaladin;
class cTrophies;

//�ڽ� �Ӹ� �ƴ϶� ��ư �̺�Ʈ ��������� ����ϱ� ������ �������� ����
enum
{
	enum_Off = 1000,
	enum_On = 1001,
	enum_Hover = 1002,
};


class cPopup : public cObserver , public cObject
{
protected:
	bool m_Fixed;
	//Power OnOff ����� �ִ��� ������ �����̸� true ���� �ƴϸ� false
	bool m_Power;
	//bool m_EventPower;

	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	float m_ImageInfoWidth;
	float m_ImageInfoHeight;
	LPDIRECT3DTEXTURE9 m_pTextureUI;
	float m_Percentage;	//�����ϸ� �� ��

	int m_State;//MouseOn MouseOff Hover
	D3DXVECTOR3 m_Position;
	RECT m_Rect;

	vector<cPopup*> m_vecPopupBtnList;

	cPopup * pParent;

	string str_filename;

	cPaladin * m_pPaladin; //�ٸ� Ŭ������ ���� �������� ���� ���(ex> �ȶ�� ü��/���׹̳�)
	cTrophies* m_pTrophies;

public:
	
	cPopup();
	~cPopup();

	virtual void Setup(
		char* root, 
		char* fileName, 
		D3DXVECTOR3 position, 
		float percent, 
		bool powerOnOff, 
		bool fixed
	);
	
	virtual void Setup(
		char* root,
		char* fileName,
		D3DXVECTOR3 position,
		float x,
		float y,
		float z,
		float percent,
		bool powerOnOff,
		bool fixed
	);



	//�±ױ��� �߰��� Setup //2020-12-01

	virtual void Setup(
		char* root,
		char* fileName,
		D3DXVECTOR3 position,
		float percent,
		bool powerOnOff,
		bool fixed,
		int tag
	);


	virtual void Setup(
		char* root,
		char* fileName,
		D3DXVECTOR3 position,
		float x,
		float y,
		float z,
		float percent,
		bool powerOnOff,
		bool fixed,
		int tag
	);

	void Update() override;
	virtual void Update(EventType message);
	virtual void Render(D3DXMATRIXA16 * pmat = NULL);
	void cButtonPushBack(cPopup*);
	virtual int GetState();
	virtual void SetStateChange(int state); // TODO !! SetState �� �̸������Ұ�
	virtual D3DXVECTOR3 GetPosition();
	function<void(EventType&, cPopup*)> EventProcess;

	virtual float GetImageInfoWidth();
	virtual float GetImageInfoHeight();

	virtual void LoadTexture(char* szFullPath);
	virtual void ChangeSprite(char* szFullPath);
	
	virtual float GetPercent();

	virtual void PowerOnOff();
	virtual void PowerOnOff(bool power);
	virtual void PowerOnOff_List();
	virtual void PowerOnOff_List(bool power);
	virtual void PowerOnOff_OnlySelf();
	virtual void PowerOnOff_OnlySelf(bool power);
	virtual void PowerOnOff_List_OnlySelf();
	virtual void PowerOnOff_List_OnlySelf(bool power);
	
	//void SetFix(bool Fixed);
	
	virtual void Destroy();

	virtual cPopup* GetTopPopUp();
	virtual cPopup* GetUpPopUp();
	
	virtual cPopup* GetPopupBtn();
	virtual cPopup* GetPopupBtn(int index);

	void MovePosition(D3DXVECTOR2 distance);
	void SetPosition(D3DXVECTOR2 position);
	
	int GetPopUpListSize();
	bool GetPowerState();

	void SetPaladinReference(cPaladin*);
	cPaladin* GetPaladinReference();
	void SetImageInfoWidth(float percent);

	virtual void SetTrophiesReference(cTrophies*);
	virtual cTrophies* GetTrophiesReference();
};

