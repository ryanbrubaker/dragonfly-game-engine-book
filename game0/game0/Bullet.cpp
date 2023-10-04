#include "Bullet.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "WorldManager.h"


Bullet::Bullet(df::Vector heroPos)
{
	this->setSprite("bullet");
	this->setType("Bullet");
	
	df::Vector p(heroPos.getX() + 3, heroPos.getY());
	this->setPosition(p);

	this->setSpeed(1);
	this->setSolidness(df::SOFT);

	this->registerInterest(df::COLLISION_EVENT);

}


int Bullet::eventHandler(const df::Event* e)
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


void Bullet::out()
{
	WM.markForDelete(this);
}


void Bullet::hit(const df::EventCollision* e)
{
	if (e->getObject1()->getType() == "Saucer" ||
		(e->getObject2()->getType() == "Saucer"))
	{
		WM.markForDelete(e->getObject1());
		WM.markForDelete(e->getObject2());
	}
}