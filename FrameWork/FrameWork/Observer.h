#pragma once

class Subject;

class cObserver
{
public:
	virtual ~cObserver() = default;
	virtual void Update(string) = 0;
};

