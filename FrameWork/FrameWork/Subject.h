#pragma once
#include <iostream>
#include <vector>

class cObserver;

class cSubject
{
protected:
	std::vector<cObserver*> m_vecObservers;
public:
	cSubject();
	virtual ~cSubject();
	virtual void Notify() = 0;
	void Attach(cObserver* ob) { m_vecObservers.push_back(ob); }
	void Detach(cObserver& ob);
};

