#include "Saucer.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

#include <stdlib.h>

Saucer::Saucer()
{
	this->setSprite("saucer");
	this->setType("Sacuer");
	this->setVelocity(df::Vector(-0.25, 0));

	this->moveToStart();
}


int Saucer::eventHandler(const df::Event* e)
{
	if (e->getType() == df::OUT_EVENT)
	{
		this->out();
		return 1;
	}

	return 0;
}


void Saucer::out()
{
	if (getPosition().getX() >= 0)
		return;

	this->moveToStart();
}


void Saucer::moveToStart()
{
	df::Vector tempPos;

	float worldHoriz = WM.getBoundary().getHorizontal();
	float worldVert = WM.getBoundary().getVertical();

	tempPos.setX(worldHoriz + rand() % (int)worldHoriz + 3.0f);
	tempPos.setY(rand() % (int)(worldVert - 1) + 1.0f);

	WM.moveObject(this, tempPos);
}