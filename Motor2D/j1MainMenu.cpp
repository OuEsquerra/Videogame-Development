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
	//App->gui->CreateImage(0, 0, false, false, { 0,0,1024,768 }, App->tex->Load("gui/Titlescreen.png"));
	
	play_button = App->gui->CreateButton(700, 250, active, false, "plAy", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), &button_rect, 70, 13);
	continue_button = App->gui->CreateButton(700, 350, active, false, "continue", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), &button_rect, 70, 13);
	credits_button = App->gui->CreateButton(700, 450, active, false, "credits", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), &button_rect, 70, 13);
	settings_button = App->gui->CreateButton(700, 550, active, false, "settings", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), &button_rect, 70, 13);
	exit_button = App->gui->CreateButton(700, 650, active, false, "exit", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), &button_rect, 70, 13);
	
	return true;
}

bool j1MainMenu::PreUpdate()
{
	return true;
}

bool j1MainMenu::Update(float dt)
{
	//BUTTONS
	if (play_button->buttonPressed())
	{
		App->scene->activate();
		App->entities->activate();
		App->collisions->activate();
		App->mainmenu->disactivate();
	}

	if (continue_button->buttonPressed())
	{
		App->scene->activate();
		App->entities->activate();
		App->collisions->activate();
		App->mainmenu->disactivate();
	}
	
	if (credits_button->buttonPressed())
	{
		


	}
	
	if (exit_button->buttonPressed())
	{
		

	
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