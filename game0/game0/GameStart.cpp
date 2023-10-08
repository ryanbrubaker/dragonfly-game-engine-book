#include "GameStart.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "Hero.h"
#include "Points.h"
#include "Saucer.h"

GameStart::GameStart()
{
	this->setType("GameStart");
	this->setSprite("gamestart");
	
	this->registerInterest(df::KEYBOARD_EVENT);
}


int GameStart::eventHandler(const df::Event* e)
{
	if (e->getType() == df::KEYBOARD_EVENT)
	{
		df::EventKeyboard* kEvent = (df::EventKeyboard*)e;
		switch (kEvent->getKey())
		{
			case df::Keyboard::P:
			{
				this->start();
				break;
			}

			case df::Keyboard::Q:
			{
				GM.setGameOver();
				break;
			}

			default:
			{
				break;
			}
		}
		return 1;
	}
	return 0;
}


int GameStart::draw()
{
	return df::Object::draw();
}


void GameStart::start()
{
	for (int i = 0; i < 16; i++)
	{
		new Saucer;
	}

	new Hero;

	new Points;

	df::ViewObject* nukesView = new df::ViewObject;
	nukesView->setLocation(df::TOP_LEFT);
	nukesView->setViewString("Nukes");
	nukesView->setValue(1);
	nukesView->setColor(df::YELLOW);

	setActive(false);
}