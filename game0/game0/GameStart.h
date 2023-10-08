#include "ViewObject.h"

class GameStart : public df::ViewObject
{
public:
	GameStart();
	int eventHandler(const df::Event* p_e) override;
	int draw() override;

private:
	void start();
};
