#pragma once

#include "Subject.h"

class Subject;
class Observer
{
public:
	virtual void Update(Subject* subject) = 0;
};