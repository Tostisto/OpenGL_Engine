#pragma once

#include <vector>
#include "Observer.h"
#include "Event.h"

class Observer;

class Subject
{
private:
	std::vector<Observer*>* observers = new std::vector<Observer*>();

public:
	void Attach(Observer* observer);
	void Detach(Observer* observer);
	void Notify(Event event, void* data);
};