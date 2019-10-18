#include <math.h>

#include "j1App.h"
#include "j1Module.h"
#include "j1FadeToBlack.h"
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
	screen = {0, 0, 1000, 1000}; //Magic Numbers
}

j1FadeToBlack::~j1FadeToBlack()
{}

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

				//moduleoff->Disable();
				//moduleon->Enable();
				App->map->data = {0}; //Empty all map data. 
				App->collisions->colliders.clear();
				
				App->map->Load(map_name);
				App->collisions->LoadFromMap();
				App->player->InitPlayer();
				
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
		} break;
	}

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1FadeToBlack::FadeToBlack(const char* mapname, float time)
{
	bool ret = false;
	
	map_name = mapname;

	if(current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		ret = true;
	}

	return ret;
}