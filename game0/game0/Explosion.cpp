#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"



Explosion::Explosion()
{

	if (this->setSprite("explosion") == 0)
	{
		this->timeToLive = this->getAnimation().getSprite()->getFrameCount();
	}
	else
	{
		this->timeToLive = 0;
	}
	
	this->setType("Explosion");
	this->setSolidness(df::SPECTRAL);

	this->registerInterest(df::STEP_EVENT);
}


int Explosion::eventHandler(const df::Event* e)
{
	if (e->getType() == df::STEP_EVENT)
	{
		this->step();
		return 1;
	}
	return 0;
}


void Explosion::step()
{
	timeToLive -= 1;
	if (timeToLive <= 0)
	{
		WM.markForDelete(this);
	}
}