
#include "Reticle.h"
#include "DisplayManager.h"
#include "EventMouse.h"
#include "WorldManager.h"


Reticle::Reticle()
{
	this->setType("Reticle");
	this->setSolidness(df::SPECTRAL);
	this->setAltitude(df::MAX_ALTITUDE);

	this->registerInterest(df::MSE_EVENT);

	int hPos = (int)WM.getBoundary().getHorizontal();
	int vPos = (int)WM.getBoundary().getVertical();
	df::Vector p(hPos / 2, vPos / 2);
	this->setPosition(p);
}


int Reticle::eventHandler(const df::Event* e) 
{
	if (e->getType() == df::MSE_EVENT) 
	{
		const df::EventMouse * mouseE = dynamic_cast <const df::EventMouse*>(e);
		if (mouseE->getMouseAction() == df::MOVED) 
		{
			this->setPosition(mouseE->getMousePosition());
			return 1;
		}
	}
	return 0;
}


int Reticle::draw() 
{
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}