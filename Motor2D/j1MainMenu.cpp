#include "j1App.h"
#include "j1Gui.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"
#include "j1Collisions.h"
#include "j1MainMenu.h"
#include "j1Audio.h"

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
	//Music
	App->audio->PlayMusic("audio/music/Interstellar_msc.ogg", 0.0f);

	//Textures
	basic_button_texture = App->tex->Load("gui/UI_Button.png");

	x_button_texture = App->tex->Load("gui/UI_Button_close.png");

	//Text load
	font = App->font->Load("fonts/MajorMonoDisplay.ttf", 25); //Magic

	consoleFont = App->font->Load("fonts/Minecraftia-Regular.ttf", 20);

	//Buttons
	background =  App->gui->CreateImage(0, 0, true, false, { 0,0,1024,768 }, App->tex->Load("gui/Titlescreen.png"));
	UI_mainmenulist.add(background);

	play_button = App->gui->CreateButton(700, 250, true, false, "plAy", &bootleg_color,font, &default_rect, &hover_rect, &press_rect, basic_button_texture, button_rect, 80, 13);
	UI_mainmenulist.add(play_button);
	
	continue_button = App->gui->CreateButton(700, 350, true, false, "continue", &bootleg_color, font, &default_rect, &hover_rect, &press_rect, basic_button_texture, button_rect, 50, 13);
	UI_mainmenulist.add(continue_button);
	
	credits_button = App->gui->CreateButton(700, 450, true, false, "credits", &bootleg_color, font, &default_rect, &hover_rect, &press_rect, basic_button_texture, button_rect, 60, 13);
	UI_mainmenulist.add(credits_button);

	settings_button = App->gui->CreateButton(700, 550, true, false, "settings", &bootleg_color, font, &default_rect, &hover_rect, &press_rect, basic_button_texture, button_rect, 50, 13);
	UI_mainmenulist.add(settings_button);

	exit_button = App->gui->CreateButton(700, 650, true, false, "exit", &bootleg_color, font, &default_rect, &hover_rect, &press_rect, basic_button_texture, button_rect, 80, 13);
	UI_mainmenulist.add(exit_button);

	x_button = App->gui->CreateButton(0, 0, false, false, "", &bootleg_color, font, &x_default, &x_hover, &x_press, x_button_texture, x_rect,0,0);

	settings_window = App->gui->CreateUiWindow(200,200,false,x_button); //new UI_Window(100, 100, false);
	border = App->gui->CreateImage(0, 100, false, false, border_rect, App->tex->Load("gui/UI_Border.png"));
	settings_window->border = border;

	console = App->gui->CreateConsole(110,0,false,false,&white,consoleFont,console_rect);
	
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


	}
	
	if (settings_button->buttonPressed())
	{

		settings_window->enable();

	
		
	}

	if (exit_button->buttonPressed())
	{
		App->input->CloseGame();
	}

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (App->frame_rate == 0)
		{
			App->frame_rate = 30;
		}
		else
		{
			App->frame_rate = 0;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN && !console->IsEnabled())
	{
		console->Enable();
		SDL_StartTextInput();
	}
	else if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN && console->IsEnabled())
	{
		console->Disable();
		SDL_StopTextInput();
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