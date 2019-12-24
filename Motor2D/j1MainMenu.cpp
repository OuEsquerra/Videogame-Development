#include "j1App.h"
#include "j1MainMenu.h"
#include "j1Gui.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"
#include "j1Collisions.h"


j1MainMenu::j1MainMenu() : j1Module()
{
	name.create("mainmenu");
}

j1MainMenu::~j1MainMenu()
{

}

bool j1MainMenu::Awake()
{
	return true;
}

bool j1MainMenu::Start()
{
	button = App->gui->CreateButton(200, 200,active, false, "Pollastre", &bootleg_color, "fonts/open_sans/OpenSans-Light.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), &button_rect, 70, 10);
	return true;
}

bool j1MainMenu::PreUpdate()
{
	return true;
}

bool j1MainMenu::Update(float dt)
{
	if (button->buttonPressed())
	{
		//App->fade->FadeToBlack("maps/Dark_Map.tmx");

		App->entities->activate();
		App->scene->activate();
		App->collisions->activate();
		App->mainmenu->disactivate();
		
	}
	return true;
}

bool j1MainMenu::PostUpdate()
{
	return true;
}

bool j1MainMenu::CleanUp()
{
	return true;
}