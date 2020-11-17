#pragma once
#include "Observer.h"
#include "cObject.h"
class cCamera : public cObserver, public cObject
{
private:
	D3DXVECTOR3 m_vOriginEye;
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 *m_pvTarget;

	D3DXVECTOR2 m_ptPrevMouse;
	D3DXVECTOR3 m_vCamRotAngle;
	bool m_isLccButtonDown;
	float m_fCameraDistance;

public:
	cCamera();
	~cCamera();

	void Setup(D3DXVECTOR3* pvTarget);
	void Update();
	void Update(EventType event);
	virtual void Render(D3DXMATRIXA16 * pmat = NULL){};
	D3DXVECTOR3*	GetEye() { return &m_vEye; }
};
