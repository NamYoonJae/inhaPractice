#pragma once

enum{NONE_BATTLE,IDLE,RUN,BATTLE,BASIC_ATTACK};


class SoulEaterState
{
protected:
	bool IsChangeState;
public:
	SoulEaterState();
	~SoulEaterState();
	virtual void Update() = 0;

};

