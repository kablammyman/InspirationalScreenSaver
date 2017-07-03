#include <math.h>
#include "GraphicsPrimitives.h"
#include "Scene.h"
#include "Button.h"
#include "BitmapFont.h"
//#include "SoundProxy.h"

#include <vector>

using namespace std;

class StopWatchScreen : public Scene, public ButtonCallback
{
	bool done;
	bool mouseClicked;
	
	int sizeOfWav;
	int timerX, timerY;
	
	RenderObject *timer;
	RenderObject *infoImg;
	//SoundProxy *sound;
	//FONT *myFont;
	StockBitmapFont font;
	void ButtonPressed(int id);
	vector<Button *> stopWatchButtons;

public:

	bool timeOver;//used to know when to play time over sound
	//AllegroTimer workoutTimer;
	void UpdateScene();
	void DrawScene();
	StopWatchScreen();
	~StopWatchScreen();
	double convertSecondsToDays(double secs);

	void AddMin(int x);
	void SubMin(int x);
	void AddSec( int x);
	void SubSec( int x);
	void AddMil( int x);
	void SubMil( int x);
	void Start();
	void Reset();
	void ToggleTimerType();
	 

};