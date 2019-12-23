#include "j1App.h"
#include "j1Main_Menu.h"
#include "j1Gui.h"


j1Main_Menu::j1Main_Menu() : j1Module()
{
	name.create("mainmenu");
}

j1Main_Menu::~j1Main_Menu()
{

}

bool j1Main_Menu::Awake()
{
	return true;
}

bool j1Main_Menu::Start()
{
	button = App->gui->CreateButton(200, 200, false, "Pollastre", &bootleg_color, "fonts/open_sans/OpenSans-Light.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), &button_rect, 70, 10);
	return true;
}

bool j1Main_Menu::PreUpdate()
{
	return true;
}

bool j1Main_Menu::Update(float dt)
{
	
	return true;
}

bool j1Main_Menu::PostUpdate()
{
	return true;
}

bool j1Main_Menu::CleanUp()
{
	return true;
}