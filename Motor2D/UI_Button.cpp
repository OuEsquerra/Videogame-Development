
#include "j1App.h"
#include "j1Gui.h"


UI_Button::UI_Button(int x, int y, bool draggable, p2SString text, SDL_Color* color, const char* path, int size, SDL_Rect rect, SDL_Texture* image) : UI(x,y,draggable) , rect(rect)
{
	ui_text = new UI_Text(x + rect.w / 2, y + rect.h / 2, draggable, text, color, path, size);

	//button_idle = App->tex->Load("gui/Button/Glue-Panel-Button-Up.png");
	//button_press = App->tex->Load("gui/Button/Glue-Panel-Button-Down.png");

}

void UI_Button::Update()
{

}

void UI_Button::Draw()
{

}