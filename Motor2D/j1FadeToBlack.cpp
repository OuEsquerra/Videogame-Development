#include <math.h>

#include "j1App.h"
#include "j1Module.h"
#include "j1FadeToBlack.h"
#include "j1Window.h"
#include "p2Log.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Collisions.h"
#include "j1Map.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

j1FadeToBlack::j1FadeToBlack()
{
	name.create("fade");

}

j1FadeToBlack::~j1FadeToBlack()
{}

bool j1FadeToBlack::Awake(pugi::xml_node& conf) {

	
	uint width, height;
	App->win->GetWindowSize(width, height);
	screen.w = width;
	screen.h = height;
	screen.x = screen.y = 0;

	return true;
}

// Load assets
bool j1FadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool j1FadeToBlack::Update(float dt)
{
	
	if(current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch(current_step)
	{
		case fade_step::fade_to_black:
		{
			if(now >= total_time)
			{

				SwitchMap(map_name);
				
				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = fade_step::fade_from_black;
			}
		} break;

		case fade_step::fade_from_black:
		{
			normalized = 1.0f - normalized;

			if(now >= total_time)
				current_step = fade_step::none;
				App->player->player.freeze = false;
		} break;
	}

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1FadeToBlack::FadeToBlack(const char* mapname, bool reset_player, float time)
{
	bool ret = false;
	
	playerReset = reset_player;
	map_name = mapname;

	if(current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		ret = true;

		App->player->player.freeze = true;
	}

	return ret;
}

bool j1FadeToBlack::SwitchMap(const char* mapname) {
	bool ret = true;
	LOG("Switching Maps...");

	App->collisions->colliders.clear(); //Clear colliders
	
	//Empty all map data. 
	p2List_item<TileSet*>* item;
	item = App->map->data.tilesets.start;

	while (item != NULL)
	{
		item->data->animations.clear();
		delete item->data->Tilerect;
		delete item->data->PlayerTilerect;

		SDL_DestroyTexture(item->data->texture);
		RELEASE(item->data);
		item = item->next;
	}
	App->map->data.tilesets.clear();
	
	p2List_item<MapObjectgroup*>* item2;
	item2 = App->map->data.objectgroups.start;

	while (item2 != NULL)
	{
		delete[] item2->data->objects;

		RELEASE(item2->data);
		item2 = item2->next;
	}
	App->map->data.objectgroups.clear();

	// Remove all layers
	App->map->data.layers.clear();
	App->map->data = { 0 };

	ret = App->map->Load(mapname);		//Load specified map
	App->collisions->LoadFromMap();		//Load Collisions
	ret = App->player->StartPlayer();	//Reset Player
	
	return ret;
}