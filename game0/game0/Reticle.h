#include "Object.h"

#define RETICLE_CHAR '+'

class Reticle : public df::Object
{

public:
	Reticle();
	int draw() override;
	int eventHandler(const df::Event* e) override;
};