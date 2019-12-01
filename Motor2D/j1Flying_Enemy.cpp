
#include "j1App.h"



#include "j1Map.h"
#include "j1Pathfinding.h"
#include "SDL/include/SDL_rect.h"

#include "j1EntityMachine.h"


//Flying Enemy
Flying_Enemy::Flying_Enemy(float x, float y, EntityType Type) : Entity(x, y, Type)
{
	
}

bool Flying_Enemy::Awake(pugi::xml_node &)
{

	return true;
}

bool Flying_Enemy::Start()
{
	
	return true;
}

bool Flying_Enemy::Update(float dt)
{
	if (App->do_logic)
	{
		//Pathfinding -------------------------------------------
		goal = App->entities->player->position;

		//	if (App->pathfinding->IsWalkable(App->map->WorldToMap(goal.x, goal.y))) {

			//Find the closest tile to current position
		App->pathfinding->CreatePath(App->map->WorldToMap(position.x, position.y), App->map->WorldToMap(goal.x, goal.y));

		const p2DynArray<iPoint>* Path = App->pathfinding->GetLastPath();
		LOG("PATH COUNT: %d", Path->Count());
		const iPoint* tile;
		if (Path->Count() != 0) {
			if (Path->Count() > 1) {
				tile = Path->At(1);
			}
			else
			{
				tile = Path->At(0);
			}



	//Find the closest tile to current position
	App->pathfinding->CreatePath(App->map->WorldToMap(position.x, position.y), App->map->WorldToMap(goal.x, goal.y));
		
	const p2DynArray<iPoint>* Path = App->pathfinding->GetLastPath();
	
	//LOG("PATH COUNT: %d", Path->Count());
	const iPoint* tile;
	if (Path->Count() != 0) {
		if (Path->Count() > 1) {
			tile = Path->At(1);
		}
		else
		{
			tile = Path->At(0);
		}

			iPoint closest_center = App->map->MapToWorldCentered(tile->x, tile->y);

			if (closest_center.x > position.x) {
				position.x += 1;
			}
			else if (closest_center.x < position.x) {
				position.x -= 1;
			}
			if (closest_center.y > position.y) {
				position.y += 1;
			}
			else if (closest_center.y < position.y) {
				position.y -= 1;
			}
		}
	}
	
	
	
	/*
	if(Path->Pop(last_tile)) {
		iPoint closest_center = App->map->MapToWorldCentered(last_tile.x, last_tile.y);


		if (closest_center.DistanceTo(position) < 2) {
			iPoint penultima_tile;
			if (Path->Pop(penultima_tile)) {
				closest_center = App->map->MapToWorldCentered(penultima_tile.x, penultima_tile.y);
			}
		}
		
		position.x += 2 * ((position.x < closest_center.x) ? 1 : -1);
		position.y += 2 * ((position.y < closest_center.y) ? 1 : -1);
		
	}*/

//	}

	//Draw enemy
	App->map->DrawAnimation("skull_still", "Skull1", position , Ainfo, false);

	return true;
}