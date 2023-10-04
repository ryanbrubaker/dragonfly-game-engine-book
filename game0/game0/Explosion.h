#include "Object.h"

class Explosion : public df::Object
{
public:
	Explosion();
	int eventHandler(const df::Event* e) override;

private:
	int timeToLive;
	
	void step();
};