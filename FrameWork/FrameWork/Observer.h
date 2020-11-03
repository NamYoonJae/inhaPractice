#pragma once

class Subject;

class cObserver
{
public:
	virtual ~cObserver() = default;
	virtual void Update(std::string) = 0;
};

