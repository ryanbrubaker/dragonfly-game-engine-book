#include "Hero.h"
#include "Bullet.h"
#include "EventNuke.h"
#include "EventStep.h"
#include "EventView.h"
#include "Explosion.h"
#include "GameManager.h"
#include "GameOver.h"
#include "Particle.h"
#include "ResourceManager.h"
#include "Saucer.h"
#include "Sound.h"
#include "utility.h"
#include "WorldManager.h"

Hero::Hero()
{
	this->setSprite("ship");
	this->setType("Hero");
	this->registerInterest(df::KEYBOARD_EVENT);
	this->registerInterest(df::STEP_EVENT);
	this->registerInterest(df::MSE_EVENT);

	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	this->setPosition(p);

	this->moveSlowdown = 2;
	this->moveCountdown = this->moveSlowdown;

	this->fireSlowdown = 15;
	this->fireCountdown = this->fireSlowdown;

	this->nukeCount = 1;

	this->reticle = new Reticle();
	this->reticle->draw();
}

Hero::~Hero()
{
	new GameOver;
	WM.markForDelete(this->reticle);

	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
}


int Hero::eventHandler(const df::Event* e)
{
	if (e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard* kbdE = dynamic_cast <const df::EventKeyboard*>(e);
		this->kdb(kbdE);
		return 1;
	}
	else if (e->getType() == df::STEP_EVENT)
	{
		this->step();
		return 1;
	}
	else if (e->getType() == df::MSE_EVENT)
	{
		const df::EventMouse* mouseE = dynamic_cast <const df::EventMouse*>(e);
		this->mouse(mouseE);
		return 1;
	}
	return 0;
}



void Hero::kdb(const df::EventKeyboard* e)
{
	switch (e->getKey())
	{
		case df::Keyboard::W:
		{
			if (e->getKeyboardAction() == df::KEY_DOWN)
			{
				this->move(-1);
			}
			break;
		}

		case df::Keyboard::S:
		{
			if (e->getKeyboardAction() == df::KEY_DOWN)
			{
				this->move(1);
			}
			break;
		}

		case df::Keyboard::Q:
		{
			if (e->getKeyboardAction() == df::KEY_PRESSED)
			{
				WM.markForDelete(this);
			}
			break;
		}

		case df::Keyboard::SPACE:
		{
			if (e->getKeyboardAction() == df::KEY_PRESSED)
			{
				this->nuke();
			}
			break;
		}
	}
}


void Hero::move(int dy)
{
	if (this->moveCountdown > 0)
		return;

	df::Vector newPos(this->getPosition().getX(), this->getPosition().getY() + dy);
	if (newPos.getY() > 3 &&
		newPos.getY() < WM.getBoundary().getVertical() - 1)
	{
		WM.moveObject(this, newPos);
	}
}


void Hero::fire(df::Vector target)
{
	if (this->fireCountdown > 0)
		return;

	this->fireCountdown = this->fireSlowdown;

	df::Vector v = target - this->getPosition();
	v.normalize();
	v.scale(1);
	Bullet* b = new Bullet(this->getPosition());
	b->setVelocity(v);

	df::Sound* pSound = RM.getSound("fire");
	if (pSound)
	{
		pSound->play();
	}
}


void Hero::step()
{
	this->moveCountdown -= 1;
	if (this->moveCountdown < 0)
	{
		this->moveCountdown = 0;
	}

	this->fireCountdown -= 1;
	if (this->fireCountdown < 0)
	{
		this->fireCountdown = 0;
	}
}


void Hero::mouse(const df::EventMouse* e)
{
	if (e->getMouseAction() == df::CLICKED &&
		e->getMouseAction() == df::Mouse::LEFT)
	{
		this->fire(e->getMousePosition());
	}
}


void Hero::nuke()
{
	if (nukeCount <= 0)
	{
		return;
	}
	nukeCount -= 1;

	EventNuke nuke;
	WM.onEvent(&nuke);

	df::EventView nukeCount("Nukes", -1, true);
	WM.onEvent(&nukeCount);

	df::Sound* pSound = RM.getSound("nuke");
	if (pSound)
	{
		pSound->play();
	}
}