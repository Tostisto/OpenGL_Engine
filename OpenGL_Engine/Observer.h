#pragma once

#include "Subject.h"
#include "Event.h"

class Subject;
class Observer
{
public:
	virtual void Update(Subject* subject, Event event, void* data) = 0;
};