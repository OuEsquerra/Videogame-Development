#define _CRT_SECURE_NO_WARNINGS
#include "j1Gui.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1EntityMachine.h"
UI_Console::UI_Console(int x, int y, bool enabled, bool draggable, SDL_Color* color, _TTF_Font* font, SDL_Rect rect) : UI(x,y,enabled,draggable), base_rect(rect),color(color),font(font)
{
	texture = App->font->Print(text.GetString(), *color, font);
	base_rect.x = position.x;
	base_rect.y = position.y;
	bruh = App->audio->LoadFx("audio/fx/bruh.wav");
	input_rect = {0,275,700,25};
	input_rect.x = position.x;
	
}

void UI_Console::Update()
{
	base_rect.x = position.x;
	base_rect.y = position.y;

	int x, y;

	App->input->GetMousePosition(x, y);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		Execute((char*)text.GetString());
		AddText((char*)text.GetString());
		text.Clear();
	}

	//Scroll funcionallity
	//if (App->input->getScrollDown() && logs.start->data->position.y > 250)
	//{
	//	p2List_item<UI_Text*>* textIt = logs.start;

	//	while (textIt != nullptr)
	//	{
	//		textIt->data->position.y -= 25;

	//		textIt = textIt->next;
	//	}
	//}
	//else if (App->input->getScrollUp()  )
	//{
	//	p2List_item<UI_Text*>* textIt = logs.start;

	//	while (textIt != nullptr)
	//	{
	//		textIt->data->position.y += 25;

	//		textIt = textIt->next;
	//	}
	//}


	p2List_item<UI_Text*>* textIt = logs.start;

	while (textIt != nullptr)
	{
		textIt->data->Update();

		textIt = textIt->next;
	}


}

void UI_Console::Draw()
{
	App->render->DrawQuad(base_rect, 75, 75, 75, 255,true,false);
	App->render->DrawQuad(input_rect, 0, 0, 0, 255,true,false);

	p2List_item<UI_Text*>* textIt = logs.start;

	while (textIt != nullptr)
	{
		if (textIt->data->position.x >= base_rect.x
			&& textIt->data->position.x < base_rect.x + base_rect.w
			&& textIt->data->position.y > base_rect.y
			&& textIt->data->position.y < base_rect.y + base_rect.h)
		{
			textIt->data->Draw();
		}
		textIt = textIt->next;
	}

	if (text != "")
	{
		App->render->Blit(texture, position.x , position.y + base_rect.h - 25, NULL, false, 0.f);
	}
}

void UI_Console::UpdateText()
{
	//SDL_DestroyTexture(texture);

	texture = App->font->Print(text.GetString(), *color, font);
}

const char* UI_Console::GetText()const
{
	return text.GetString();
}

void UI_Console::ConcatNewText(char* newText)
{
	//oldText = text;
	strcat((char*)text.GetString(), newText);
	UpdateText();
}

void UI_Console::Execute(char* call)
{
	if (strcmp("quit", call) == 0)
	{
		App->input->CloseGame();
	}

	if (strcmp("god_mode", call) == 0)
	{
		if (App->entities->player != nullptr)
		{
			App->entities->player->GodMode();
		}
	}

	if (strcmp("bruh", call) == 0)
	{
		App->audio->PlayFx(bruh);
	}

	//FPS check

}

void UI_Console::AddText(char* string)
{
	//logs.del(logs.start);

	p2List_item<UI_Text*>* textIt = logs.start;

	while (textIt != nullptr)
	{
		textIt->data->position.y -= 25;

		textIt = textIt->next;
	}

	logs.add(new UI_Text(position.x + 5, 250, true, false, string, color, font));

}

