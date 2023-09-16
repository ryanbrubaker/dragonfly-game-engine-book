#include "EventKeyboard.h"
#include "Object.h"

class Hero : public df::Object
{
public:
	Hero();
	int eventHandler(const df::Event* e) override;

private:

	int moveSlowdown;
	int moveCountdown;


	void kdb(const df::EventKeyboard* e);
	void move(int dy);
	void step();
};