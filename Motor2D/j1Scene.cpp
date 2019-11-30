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
//#include "j1Entity.h"

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
	App->map->Load("Dark_Map.tmx");

	SDL_Rect fly_enemy = { 100,1100,62,60 };

	App->entities->skull = (Flying_Enemy*)App->entities->CreateEntity(300, 900, &fly_enemy , FLYING_ENEMY);

	App->entities->player = (j1Player*)App->entities->CreateEntity(100, 1000, &fly_enemy, PLAYER);

	//App->audio->PlayMusic("audio/music/roundabout_msc.ogg" , 0.0f);

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
		if(App->map->data.name == "Dark_Map.tmx") App->fade->FadeToBlack("Dark_Map.tmx");
		else if (App->map->data.name == "Dark_Map2.tmx") App->fade->FadeToBlack("Dark_Map2.tmx");
	}

	//LOG("Befor Draw");
	
	App->map->Draw();

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
