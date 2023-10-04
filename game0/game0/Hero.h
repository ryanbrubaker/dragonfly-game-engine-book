#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Reticle.h";


class Hero : public df::Object
{
public:
	Hero();
	int eventHandler(const df::Event* e) override;

private:

	int moveSlowdown;
	int moveCountdown;

	int fireSlowdown;
	int fireCountdown;

	Reticle* reticle;

	void kdb(const df::EventKeyboard* e);
	void move(int dy);
	void fire(df::Vector target);
	void mouse(const df::EventMouse* e);
	void step();
};