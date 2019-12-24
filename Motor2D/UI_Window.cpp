
#include "UI_Window.h"
//#include "UI_Button.h"

UI_Window::UI_Window(int x, int y, bool active) : position(x,y) , active(active)
{

}

void UI_Window::Update()
{
	p2List_item<UI_Button*>* buttonIt = buttons.start;

	while (buttonIt != NULL)
	{
		buttonIt->data->position += position;
	}


}

void activate()
{

}

void disactivate()
{
	
}