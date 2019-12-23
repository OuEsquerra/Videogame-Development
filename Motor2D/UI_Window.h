#include "p2List.h"

class UI_Button;
class UI_Text;
class UI_Image;

class UI_Window
{
public:

	p2List<UI_Button*> buttons;
	p2List<UI_Text*> text;
	p2List<UI_Image*> images;

	UI_Image* border;

public:
	UI_Window();

	
	void Update();


};