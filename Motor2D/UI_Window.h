#include "p2List.h"
#include "p2Point.h"
#include "j1Gui.h"

//class UI_Button;
//class UI_Text;
//class UI_Image;

class UI_Window
{
public:

	p2List<UI_Button*> buttons;
	p2List<UI_Text*> text;
	p2List<UI_Image*> images;

	UI_Image* border;

	iPoint position;

	bool active;

public:

	UI_Window(int x, int y,bool activa);

	void Update();

	void activate();

	void disactivate();
};