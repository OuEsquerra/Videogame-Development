
#include "j1Gui.h"


UI::UI(int x, float y,bool active,bool draggable) : position(x,y),active(active),draggable(draggable)
{
	debug = false;
}

void UI::Update()
{

}

void UI::Draw()
{

}

bool UI::IsEnabled()
{
	return enabled;
}

void UI::Enable()
{
	enabled = true;
}

void UI::Disable()
{
	enabled = false;
}