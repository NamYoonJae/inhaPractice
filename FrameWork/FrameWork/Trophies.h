#pragma once

enum TROPIES
{
	//����ǰ ����
	TROPIES_Beez,
	TROPIES_DragonFoot,
};

class cTrophies : public cPopup
{
private:
	
	int m_Trophy;
	int m_MaxGauge;
	int m_Gauge;


public:
	cTrophies();
	~cTrophies();

	void Setup();


};

