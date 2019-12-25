#include "p2List.h"
#include "p2Point.h"
#include "j1Gui.h"

//class UI_Button;
//class UI_Text;
//class UI_Image;

class UI_Window
{
public:

	p2List<UI*> elements;

	UI_Image* border;

	iPoint position;

	bool active;

public:

	UI_Window(int x, int y,bool activa);

	void Update();

	void addUI(UI* ui);

	void enable();

	void disable();
};