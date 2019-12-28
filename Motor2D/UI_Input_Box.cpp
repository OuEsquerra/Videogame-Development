#include "j1Gui.h"
#include "j1Input.h"

UI_Input_Box::UI_Input_Box(int x, int y, bool enabled, bool draggable, p2SString text, SDL_Color* color, _TTF_Font* font, UI_Image* border,SDL_Rect rect) : UI(x,y,enabled,draggable),border(border),rect(rect)
{
	texture = App->font->Print(text.GetString(), *color, font);
}

void UI_Input_Box::Update()
{
	rect.x = position.x;
	rect.y = position.y;

	int x, y;

	App->input->GetMousePosition(x, y);

	if (x > rect.x && x < rect.x + rect.w
		&& y > rect.y && y < rect.y + rect.h
		&& App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		App->gui->focused = this;
		SDL_StartTextInput();
	}

	if (SDL_IsTextInputActive() && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		SDL_StopTextInput();
	}

	if (enabled)
	{
		border->enabled = true;
	}
	else
	{
		border->enabled = false;
	}
}

void UI_Input_Box::Draw()
{
	App->render->Blit(texture, position.x, position.y, NULL, false, 0.f);
}

const char* UI_Input_Box::GetText()const
{
	return text.GetString();
}