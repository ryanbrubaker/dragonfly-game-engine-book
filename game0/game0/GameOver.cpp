#include "GameOver.h"
#include "EventStep.h"
#include "GameManager.h"
#include "GameStart.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "WorldManager.h"

GameOver::GameOver()
{
	this->setType("GameOver");

	if (this->setSprite("gameover") == 0)
	{
		timeToLive = this->getAnimation().getSprite()->getFrameCount() *
			this->getAnimation().getSprite()->getSlowdown();
	}
	else
	{
		timeToLive = 0;
	}

	this->setLocation(df::CENTER_CENTER);
	this->registerInterest(df::STEP_EVENT);

	df::Sound* pSound = RM.getSound("gameover");
	if (pSound)
	{
		pSound->play();
	}
}


GameOver ::~GameOver() 
{
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) 
	{
		df::Object* p = i.currentObject();
		if (p->getType() == "Saucer" || p->getType() == "ViewObject")
		{
			WM.markForDelete(p);
		}
		else if (p->getType() == "GameStart")
		{
			p->setActive(true);
			dynamic_cast<GameStart*>(p)->playMusic();
		}
	}
}



int GameOver::eventHandler(const df::Event* e)
{
	if (e->getType() == df::STEP_EVENT)
	{
		this->step();
		return 1;
	}
	return 0;
}


void GameOver::step()
{
	timeToLive -= 1;
	if (timeToLive <= 0)
	{
		WM.markForDelete(this);
	}
}


int GameOver::draw()
{
	return df::Object::draw();
}