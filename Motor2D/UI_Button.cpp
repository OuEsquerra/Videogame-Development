
#include "j1App.h"
#include "j1Gui.h"

UI_Button::UI_Button(int x, int y,bool draggable, SDL_Rect rect) : UI(x,y,draggable) , rect(rect)
{
	//button_idle = App->tex->Load("gui/Button/Glue-Panel-Button-Up.png");
	//button_press = App->tex->Load("gui/Button/Glue-Panel-Button-Down.png");
}

void UI_Button::Update()
{

}

void UI_Button::Draw()
{

}