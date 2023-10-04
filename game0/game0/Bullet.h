#include "Object.h"
#include "EventCollision.h"


class Bullet : public df::Object
{
public:
	Bullet(df::Vector heroPos);
	int eventHandler(const df::Event* e) override;


private:
	void out();
	void hit(const df::EventCollision* e);

};
