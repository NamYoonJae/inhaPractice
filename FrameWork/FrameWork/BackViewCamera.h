#pragma once
#include "Observer.h"
#include "cObject.h"
class cCharater;

class cBackViewCamera :public cObject , public cObserver
{
private:
	D3DXVECTOR3 m_vOffset;
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR2 m_ptPrevMouse;  // ���콺�� ������ġ�� ���� �ٲ�⶧�����ʿ�
	D3DXVECTOR3 m_vCamRotAngle; 
	D3DXVECTOR3 m_vDir;
	D3DXMATRIXA16 m_matParent; // �÷����� ��Ʈ����
	cCharater *m_pPlayer;

	float	m_fScrollY;
	
	Synthesize(float, m_fVibrationValue, VibrationValue);
	Synthesize(bool, m_IsVibration, Vibration);
	Synthesize(bool, m_IsUpdate, Update);

public:
	cBackViewCamera();
	~cBackViewCamera();
	void Update();
	void Setup(cCharater* = NULL);
	void GetTarget(cCharater*);
	void GetParentMatrix(D3DXMATRIXA16* pmat) { m_matParent = *pmat; }
	void GetLookAt(D3DXVECTOR3 pos) { m_vLookAt = pos; }
	void DirectionCalculation();
	D3DXVECTOR3*	GetEye() { return &m_vEye; }
	//
	
	void Render(D3DXMATRIXA16* pmat) override{};
	void Update(EventType) override;

};

