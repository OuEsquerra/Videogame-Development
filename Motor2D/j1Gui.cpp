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
	atlas = App->tex->Load(atlas_file_name.GetString());

	
	background = App->tex->Load("gui/Image/login_background.png");
	wow_logo = App->tex->Load("gui/Image/Glues_Logo.png");

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	p2List_item<UI*>* it = UI_list.start;

	while (it != nullptr)
	{

		it->data->Update();

		it = it->next;
	}


	return true;
}

// Update all guis
bool j1Gui::Update()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{

	p2List_item<UI*>* it = UI_list.start;

	while (it != nullptr)
	{

		it->data->Draw();

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

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}


UI_Text* j1Gui::CreateText(int x, int y, bool draggable, p2SString text, SDL_Color* color, const char* path, int size)
{
	UI_Text* ret = new UI_Text(x,y,draggable,text,color,path,size);

	UI_list.add(ret);

	return ret;
}

UI_Image* j1Gui::CreateImage(int x, int y,bool draggable, SDL_Rect rect,SDL_Texture* image)
{
	UI_Image* ret = new UI_Image(x,y,draggable,rect,image);

	UI_list.add(ret);

	return ret;
}

UI_Button* j1Gui::CreateButton(int x, int y, SDL_Rect rect, p2SString text)
{
	UI_Button* ret = nullptr;

	return ret;
}


// class Gui ---------------------------------------------------

