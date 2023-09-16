#include "EventOut.h"
#include "Object.h"


class Saucer : public df::Object
{

public:  
	Saucer();
	int eventHandler(const df::Event* e) override;
	void moveToStart();

private:
	void out();
};