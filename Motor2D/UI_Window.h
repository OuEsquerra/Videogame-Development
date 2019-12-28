#include "p2List.h"
#include "p2Point.h"

//#include "j1Gui.h"

//class UI_Button;
//class UI_Text;
//class UI_Image;

//class UI;

class UI_Window
{
public:

	p2List<UI*> elements;

	UI_Image* border;

	iPoint position;

	bool enabled;

	UI_Button* x_button;

public:

	UI_Window(int x, int y,bool enabled,UI_Button* x_button);

	void Update();

	void Draw();

	void addUI(UI* ui,int x, int y);

	void enable();

	void disable();
};