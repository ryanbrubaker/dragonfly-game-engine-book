#include "Points.h"
#include "EventStep.h"


Points::Points()
{
	this->setLocation(df::TOP_RIGHT);
	this->setViewString("Points");
	this->setColor(df::YELLOW);

	this->registerInterest(df::STEP_EVENT);
}


int Points::eventHandler(const df::Event* e) 
{
	if (df::ViewObject::eventHandler(e))
	{
		return 1;
	}

	if (e->getType() == df::STEP_EVENT)
	{
		if (dynamic_cast <const df::EventStep*>(e)->getStepCount() % 30 == 0)
		{
			this->setValue(this->getValue() + 1);
			return 1;
		}
	}
	return 0;
}