#include "Object.h"

#define STAR_CHAR '.'

class Star : public df::Object
{
public:
	Star();
	int draw(void) override;
	int eventHandler(const df::Event* e) override;

private:
	void out();
};
