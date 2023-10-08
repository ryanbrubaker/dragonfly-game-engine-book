#include "Object.h"
#include "EventCollision.h"


class Saucer : public df::Object
{

public:  
	Saucer();
	~Saucer();

	int eventHandler(const df::Event* e) override;
	void moveToStart();

private:
	void out();
	void hit(const df::EventCollision* e);
};