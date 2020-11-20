#include "stdafx.h"
#include "Subject.h"
#include <algorithm>
#include "Observer.h"

cSubject::cSubject()
{
}


cSubject::~cSubject()
{
}
void cSubject::Detach(cObserver& ob)
{
	using namespace std;
	m_vecObservers.erase(remove(m_vecObservers.begin(),
		m_vecObservers.end(), &ob),m_vecObservers.end());

}
