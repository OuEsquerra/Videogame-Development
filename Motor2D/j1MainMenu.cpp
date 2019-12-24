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
	App->gui->CreateImage(0, 0, false, false, { 0,0,1024,768 }, App->tex->Load("gui/Titlescreen.png"));
	
	new_button = App->gui->CreateButton(700, 250, active, false, "new Game", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), button_rect, 70, 10);
	
	button2 = App->gui->CreateButton(700, 350, active, false, "pollastre", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), button_rect, 70, 10);

	return true;
}

bool j1MainMenu::PreUpdate()
{
	return true;
}

bool j1MainMenu::Update(float dt)
{
	if (new_button->buttonPressed())
	{
		//App->fade->FadeToBlack("maps/Dark_Map.tmx");
		if(App->entities->active == false){
			App->scene->activate();
			App->entities->activate();
			
			App->collisions->activate();
			App->mainmenu->disactivate();
		}
		else if (App->entities->active == true) {
			App->mainmenu->activate();
			App->entities->disactivate();
			App->scene->disactivate();
			App->collisions->disactivate();
		
		}
		
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