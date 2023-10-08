#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject
{
public:
	GameStart();
	int eventHandler(const df::Event* p_e) override;
	int draw() override;
	void playMusic();

private:
	df::Music* pMusic;

	void start();
};
