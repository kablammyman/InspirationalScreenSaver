#include <math.h>
#include "GraphicsPrimitives.h"
#include "Scene.h"
#include "button.h"
#include "SoundProxy.h"

#include <vector>

using namespace std;

class StopWatchMain : public Scene, public ButtonCallback
{
	bool done;
	bool mouseClicked;
	
	int sizeOfWav;
	int timerX, timerY;
	
	RenderObject *timer;
	RenderObject *infoImg;
	SoundProxy *sound;
	FONT *myFont;
	void buttonPressed(int id);
	vector<Button *> stopWatchButtons;

public:

	bool timeOver;//used to know when to play time over sound
	AllegroTimer workoutTimer;
	void update();
	void draw();
	StopWatchMain();
	~StopWatchMain();
	double convertSecondsToDays(double secs);

	void addMin(int x);
	void subMin(int x);
	void addSec( int x);
	void subSec( int x);
	void addMil( int x);
	void subMil( int x);
	void start();
	void reset();
	void toggleTimerType();
	 

};