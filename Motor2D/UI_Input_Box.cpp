
#include "j1Gui.h"
#include "j1Input.h"

UI_Input_Box::UI_Input_Box(int x, int y,bool enabled, bool draggable) : UI(x,y,enabled,draggable)
{

}

void UI_Input_Box::Update()
{
	int x, y;

	App->input->GetMousePosition(x, y);

	if (x > rect.x && x < rect.x + rect.w
		&& y > rect.y && y < rect.y + rect.h
		&& App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		SDL_StartTextInput();
	}

	if (SDL_IsTextInputActive() && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		SDL_StopTextInput();
	}
}

void UI_Input_Box::Draw()
{

}