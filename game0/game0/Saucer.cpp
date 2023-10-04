#include "Saucer.h"
#include "EventOut.h"
#include "Explosion.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"


Saucer::Saucer()
{
	this->setSprite("saucer");
	this->setType("Saucer");
	this->setVelocity(df::Vector(-0.25, 0));

	this->registerInterest(df::OUT_EVENT);
	this->registerInterest(df::COLLISION_EVENT);


	this->moveToStart();
}


int Saucer::eventHandler(const df::Event* e)
{
	if (e->getType() == df::OUT_EVENT)
	{
		this->out();
		return 1;
	}
	else if (e->getType() == df::COLLISION_EVENT)
	{
		const df::EventCollision* collisionE = dynamic_cast<const df::EventCollision*>(e);
		hit(collisionE);
		return 1;
	}
	return 0;
}


void Saucer::out()
{
	if (getPosition().getX() >= 0)
		return;

	this->moveToStart();
	new Saucer;
}


void Saucer::moveToStart()
{
	df::Vector tempPos;

	float worldHoriz = WM.getBoundary().getHorizontal();
	float worldVert = WM.getBoundary().getVertical();

	tempPos.setX(worldHoriz + rand() % (int)worldHoriz + 3.0f);
	tempPos.setY(rand() % (int)(worldVert - 1) + 1.0f);

	df::ObjectList collisionList = WM.getCollisions(this, tempPos);
	while (!collisionList.isEmpty()) 
	{
		tempPos.setX(tempPos.getX() + 1);
		collisionList = WM.getCollisions(this, tempPos);
	}

	WM.moveObject(this, tempPos);
}

void Saucer::hit(const df::EventCollision* e) 
{
	if (e->getObject1()->getType() == "Saucer" && e->getObject2()->getType() == "Saucer")
	{
		return;
	}

	if (e->getObject1()->getType() == "Bullet" || e->getObject2()->getType() == "Bullet")
	{
		Explosion* explosion = new Explosion();
		explosion->setPosition(this->getPosition());

		new Saucer;
	}
}
