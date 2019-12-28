#include "j1App.h"
#include "j1Gui.h"

UI_Slider::UI_Slider(int x, int y, bool active, bool draggable, SDL_Rect rect, SDL_Texture* image) : UI(x, y, active, draggable), rect(rect)
{

}

void UI_Slider::Update()
{

}

void UI_Slider::Draw()
{
	//App->render->Blit(image, position.x, position.y, &rect, false, 0.f);
}