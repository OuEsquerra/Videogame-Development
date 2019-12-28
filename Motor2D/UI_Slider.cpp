#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"

UI_Slider::UI_Slider(int x, int y, bool active, bool draggable) : UI(x, y, active, draggable)
{
	//thumb_rect = { x + 46, y + 10, 28, 36};
	clickable_rect = { x + 46, y + 4, 188, 40 };

	thumb_offset = 46;

	sliderpos = 76;

	texture = App->tex->Load("gui/UI_Slider.png");

	bar = { 0, 0, 280, 48 };
	thumb = { 0, 48, 36, 28 };
	thumb_hovered = { 38, 48, 36, 28 };
}

void UI_Slider::Update()
{
	clickable_rect = { position.x + 46, position.y + 4, 188, 40 };
	hovered = false;
	int x, y;//Mouse coords

	App->input->GetMousePosition(x, y);

	if (x > clickable_rect.x && x < clickable_rect.x + clickable_rect.w
		&& y > clickable_rect.y && y < clickable_rect.y + clickable_rect.h)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			hovered = true;
			sliderpos = x - position.x - thumb_offset;
			if (sliderpos < 0)	sliderpos = 0;
			else if (sliderpos > 152) sliderpos = 152;
		}
	}
}

void UI_Slider::Draw() {
	
	App->render->Blit(texture, position.x, position.y, &bar);
	
	if (hovered) {
		App->render->Blit(texture, position.x + thumb_offset + sliderpos, position.y + 10, &thumb_hovered);
	}
	else App->render->Blit(texture, position.x + thumb_offset + sliderpos, position.y + 10, &thumb);
	
	if (!debug)
	{
		App->render->DrawQuad(clickable_rect, 0, 255, 255, 50);
	}
}

float UI_Slider::SliderValue() {

	return ((float)sliderpos / 152.0f);
}