#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;
	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	background = App->tex->Load("gui/Image/login_background.png");

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	p2List_item<UI*>* it = UI_list.start;

	while (it != nullptr)
	{
		if (it->data->enabled)
		{
			it->data->Update();
		}
		it = it->next;
	}

	return true;
}

// Update all guis
bool j1Gui::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		p2List_item<UI*>* it = UI_list.start;

		while (it != nullptr)
		{
			it->data->debug = !it->data->debug;
			it = it->next;
		}
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<UI*>* it = UI_list.start;

	while (it != nullptr)
	{
		if (it->data->enabled)
		{
			it->data->Draw();
		}
		it = it->next;
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

UI_Text* j1Gui::CreateText(int x, int y, bool active, bool draggable, p2SString text, SDL_Color* color, const char* path, int size)
{
	UI_Text* ret = new UI_Text(x,y,active,draggable,text,color,path,size);

	UI_list.add(ret);

	return ret;
}

UI_Image* j1Gui::CreateImage(int x, int y, bool active,bool draggable, SDL_Rect rect,SDL_Texture* image)
{
	UI_Image* ret = new UI_Image(x,y,active,draggable,rect,image);

	UI_list.add(ret);

	return ret;
}

UI_Button* j1Gui::CreateButton(int x, int y, bool active, bool draggable, p2SString text, SDL_Color* color, const char* path, int size, SDL_Rect* default_rect, SDL_Rect* hover_rect, SDL_Rect* press_rect, SDL_Texture* image,SDL_Rect rect,int x_offset, int y_offset)
{
	UI_Button* ret = new UI_Button(x,y,active,draggable,text,color,path,size,default_rect,hover_rect,press_rect,image,rect,x_offset,y_offset);

	UI_list.add(ret);

	return ret;
}