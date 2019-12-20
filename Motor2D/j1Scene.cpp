#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1FadeToBlack.h"
#include "j1EntityMachine.h"
#include "j1Pathfinding.h"
#include "j1Gui.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	if (App->map->Load("Dark_Map.tmx") == true)

	//App->audio->PlayMusic("audio/music/roundabout_msc.ogg" , 0.0f);

	debug_tex = App->tex->Load("maps/path.png");



	button = App->gui->CreateButton(200, 200, false, "pollastre", &bootleg_color, "fonts/open_sans/OpenSans-Light.ttf", 50, { 80, 0, 350, 150 }, App->tex->Load("gui/Image/Glues-Logo.png"));
	
	wowLogo = App->gui->CreateImage(0, 0, false, { 80, 0, 350, 150 }, App->tex->Load("gui/Image/Glues-Logo.png"));

	Bootleg = App->gui->CreateText(100, 100, false, "pollastre", &bootleg_color, "fonts/open_sans/OpenSans-Light.ttf", 100);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->fade->FadeToBlack("Dark_Map.tmx");

	if(App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->fade->FadeToBlack("Dark_Map2.tmx");

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) 
	{
		if(strcmp(App->map->data.name, "Dark_Map2.tmx") == 0) App->fade->FadeToBlack("Dark_Map.tmx");
		else if (strcmp(App->map->data.name, "Dark_Map.tmx") == 0) App->fade->FadeToBlack("Dark_Map2.tmx");
	}

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_UP) App->map->debug = !App->map->debug;
	
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

	//LOG("Befor Draw");
	
	App->map->Draw();

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
	if (App->map->debug) {
		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			App->render->Blit(debug_tex, pos.x, pos.y);
		}
	}
	//LOG("After Draw");


	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
