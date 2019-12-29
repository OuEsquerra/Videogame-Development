#define _CRT_SECURE_NO_WARNINGS
#include "j1Gui.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1EntityMachine.h"
UI_Console::UI_Console(int x, int y, bool enabled, bool draggable, SDL_Color* color, _TTF_Font* font, SDL_Rect rect) : UI(x,y,enabled,draggable),rect(rect),color(color),font(font)
{
	texture = App->font->Print(text.GetString(), *color, font);
	rect.x = position.x;
	rect.y = position.y;
}

void UI_Console::Update()
{
	rect.x = position.x;
	rect.y = position.y;

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
	App->render->DrawQuad(rect, 0, 0, 0, 100);

	if (text != "" )
	{
		App->render->Blit(texture, position.x , position.y + rect.h - 20, NULL, false, 0.f);
	}

	p2List_item<UI_Text*>* textIt = logs.start;

	while (textIt != nullptr)
	{
		if (textIt->data->position.x >= rect.x
			&& textIt->data->position.x < rect.x + rect.w
			&& textIt->data->position.y > rect.y
			&& textIt->data->position.y < rect.y + rect.h)
		{
			textIt->data->Draw();
		}
		textIt = textIt->next;
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
		LOG("bruh");
	}

	//FPS check
	/*if (call[0] == "F" && call[1] == "P" && call[2] == "S")
	{
		LOG("bruh");
	}*/
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

	logs.add(new UI_Text(125, 250, true, false, string, color, font));

}

