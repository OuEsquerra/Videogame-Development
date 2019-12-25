#include "j1App.h"
#include "j1Gui.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"
#include "j1Collisions.h"
#include "j1MainMenu.h"


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

	background =  App->gui->CreateImage(0, 0, true, false, { 0,0,1024,768 }, App->tex->Load("gui/Titlescreen.png"));
	UI_mainmenulist.add(background);

	play_button = App->gui->CreateButton(700, 250, true, false, "plAy", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), button_rect, 80, 13);
	UI_mainmenulist.add(play_button);
	
	continue_button = App->gui->CreateButton(700, 350, true, false, "continue", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), button_rect, 50, 13);
	UI_mainmenulist.add(continue_button);
	
	credits_button = App->gui->CreateButton(700, 450, true, false, "credits", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), button_rect, 60, 13);
	UI_mainmenulist.add(credits_button);

	settings_button = App->gui->CreateButton(700, 550, true, false, "settings", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), button_rect, 50, 13);
	UI_mainmenulist.add(settings_button);

	exit_button = App->gui->CreateButton(700, 650, true, false, "exit", &bootleg_color, "fonts/MajorMonoDisplay.ttf", 25, &default_rect, &hover_rect, &press_rect, App->tex->Load("gui/UI_Button.png"), button_rect, 80, 13);
	UI_mainmenulist.add(exit_button);

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
		App->mainmenu->disactivate();
		App->scene->activate();
		App->entities->activate();
		App->collisions->activate();

	}

	if (continue_button->buttonPressed())
	{
		App->mainmenu->disactivate();
		App->scene->activate();
		App->entities->activate();
		App->collisions->activate();

		App->LoadGame();

	}
	
	if (credits_button->buttonPressed())
	{


		App->scene->activate();
		App->entities->activate();
			
		App->collisions->activate();
		App->mainmenu->disactivate();

		

	}
	
	if (settings_button->buttonPressed())
	{


		
	}

	if (exit_button->buttonPressed())
	{
		App->input->CloseGame();

	}

	return true;
}

bool j1MainMenu::PostUpdate()
{
	return true;
}

bool j1MainMenu::CleanUp()
{
	p2List_item<UI*>* it = UI_mainmenulist.start;

	while (it != nullptr)
	{
		it->data->Disable();
		it = it->next;
	}

	return true;
}