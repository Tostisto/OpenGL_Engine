#pragma once

#include <vector>
#include "Observer.h"

class Observer;

class Subject
{
private:
	std::vector<Observer*>* observers = new std::vector<Observer*>();

public:
	const char* type;

	void Attach(Observer* observer);
	void Detach(Observer* observer);
	void Notify();
};