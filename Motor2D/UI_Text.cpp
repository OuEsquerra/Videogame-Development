#include "j1Gui.h"


UI_Text::UI_Text(int x, int y, bool draggable , p2SString text ,SDL_Color* color, const char* path, int size) : UI(x, y,draggable), text(text),color(color)
{
	font = App->font->Load(path, size);

	texture = App->font->Print(text.GetString(),*color,font);
}

void UI_Text::Update()
{

}

void UI_Text::Draw()
{
	App->render->Blit(texture, position.x, position.y);

}