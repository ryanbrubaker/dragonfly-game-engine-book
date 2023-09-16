#include "Saucer.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

#include <stdlib.h>

Saucer::Saucer()
{
	setSprite("saucer");
	setType("Sacuer");
	setVelocity(df::Vector(-0.25, 0));

	this->moveToStart();
	
	/*int worldHoriz = (int)WM.getBoundary().getHorizontal();
	int worldVert = (int)WM.getBoundary().getVertical();
	df::Vector p(worldHoriz / 2, worldVert / 2);
	setPosition(p);*/
}


int Saucer::eventHandler(const df::Event* e)
{
	if (e->getType() == df::OUT_EVENT)
	{
		out();
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