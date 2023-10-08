#include "ViewObject.h"
#include "Event.h"

class GameOver : public df::ViewObject
{
public:
	GameOver();
	~GameOver();

	int eventHandler(const df::Event* e);
	int draw() override;

private:
	int timeToLive;

	void step();

};