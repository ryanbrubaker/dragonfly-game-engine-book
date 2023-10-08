#include "ViewObject.h"
#include "Event.h"


class Points : public df::ViewObject
{
public:
	Points();

	int eventHandler(const df::Event* e) override;

};
