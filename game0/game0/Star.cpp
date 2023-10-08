#include "Star.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "WorldManager.h"

#include <stdlib.h>

Star::Star()
{
	this->setType("Star");
	this->setSolidness(df::SPECTRAL);

	this->setVelocity(df::Vector((float)-1.0 / (rand() % 10 + 1), 0));
	this->setAltitude(0);

	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()), 
		          (float)(rand() % (int)WM.getBoundary().getVertical()));
	this->setPosition(p);
}


int Star::draw()
{
	return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}


int Star::eventHandler(const df::Event* e)
{
	if (e->getType() == df::OUT_EVENT)
	{
		this->out();
		return 1;
	}
	return 0;
}


void Star::out()
{
	df::Vector p((float)(WM.getBoundary().getHorizontal() + rand() % 20),
		(float)(rand() % (int)WM.getBoundary().getVertical()));
	this->setPosition(p);
	this->setVelocity(df::Vector(-1.0 / (rand() % 10 + 1), 0));
}


