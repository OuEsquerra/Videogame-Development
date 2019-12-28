#include "j1Gui.h"
#include "j1Input.h"

UI_Console::UI_Console(int x, int y, bool enabled, bool draggable, SDL_Color* color, _TTF_Font* font, SDL_Rect rect) : UI(x,y,enabled,draggable),rect(rect)
{
	//texture = App->font->Print(text.GetString(), *color, font);
	rect.x = position.x;
	rect.y = position.y;
}

void UI_Console::Update()
{
	rect.x = position.x;
	rect.y = position.y;

	int x, y;

	App->input->GetMousePosition(x, y);

	//if ()
	//{
		
	//	SDL_StartTextInput();
	//}

	if (SDL_IsTextInputActive() && App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		SDL_StopTextInput();
	}
}

void UI_Console::Draw()
{
	//App->render->Blit(texture, position.x, position.y, NULL, false, 0.f);
	App->render->DrawQuad(rect, 0, 0, 0, 50);
}

const char* UI_Console::GetText()const
{
	return text.GetString();
}