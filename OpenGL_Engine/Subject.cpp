#include "Subject.h"

void Subject::Attach(Observer* observer)
{
	this->observers->push_back(observer);

	// Notify the observer about the current state
	observer->Update(this, "attach", nullptr);
}

void Subject::Detach(Observer* observer)
{
	this->observers->erase(std::remove(this->observers->begin(), this->observers->end(), observer), this->observers->end());
}

void Subject::Notify(const char* type, void* data)
{
	for (auto observer : *observers)
	{
		observer->Update(this, type, data);
	}
}