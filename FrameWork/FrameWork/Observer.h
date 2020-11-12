#pragma once

class Subject;
enum class EventType;

class cObserver
{
public:
	virtual ~cObserver() = default;
	virtual void Update(EventType) = 0;
};

