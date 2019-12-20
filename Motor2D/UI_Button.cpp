#include "j1App.h"
#include "j1Gui.h"

UI_Button::UI_Button(int x, int y, bool draggable, p2SString text, SDL_Color* color, const char* path, int size, SDL_Rect image_rect, SDL_Texture* image) : UI(x,y,draggable) , rect(image_rect) , image_texture(image),text(text),color(color)
{

	font = App->font->Load(path, size);

	text_texture = App->font->Print(text.GetString(),*color,font);

}

void UI_Button::Update()
{

}

void UI_Button::Draw()
{
	App->render->Blit(image_texture, position.x, position.y, &rect, false, 0.f);
	App->render->Blit(text_texture, position.x+rect.w/2, position.y + rect.h/2 , NULL, false, 0.f);
}